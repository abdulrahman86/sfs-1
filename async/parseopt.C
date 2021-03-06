/* $Id: parseopt.C,v 1.17 2004/06/18 20:06:55 dm Exp $ */

/*
 *
 * Copyright (C) 1998 David Mazieres (dm@uun.org)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA
 *
 */

#include "amisc.h"
#include "parseopt.h"

char *parseargs::errorbuf = "";

static inline int
isspc (char c)
{
  return c == ' ' || c == '\t' || c == '\n';
}
static inline int
isspcnnl (char c)
{
  return c == ' ' || c == '\t';
}

void
parseargs::skipblanks ()
{
  bool bol = true;
  while (p < lim) {
    if (bol && *p == '#') {
      while (p < lim && *p != '\n')
	p++;
      if (p < lim) {
	lineno++;
	p++;
      }
      continue;
    }
    if (isspcnnl (*p)) {
      bol = false;
      p++;
    }
    else if (*p == '\n') {
      lineno++;
      p++;
      bol = true;
    }
    else if (p[0] == '\\' && p[1] == '\n') {
      p += 2;
      lineno++;
      bol = false;
    }
    else
      return;
  }
}
void
parseargs::skiplwsp ()
{
  for (;;) {
    if (isspcnnl (*p))
      p++;
    else if (p[0] == '\\' && p[1] == '\n') {
      p += 2;
      lineno++;
    }
    else
      return;
  }
}

str
parseargs::getarg ()
{
  skiplwsp ();
  if (p >= lim || *p == '\n')
    return NULL;

  bool q = false;
  vec<char> arg;
  for (;;) {
    if (*p == '\\') {
      if (p + 1 >= lim) {
	error ("invalid '\\' before end of file");
	return NULL;
      }
      else if (p[1] == '\n')
	skiplwsp ();
      else {
	arg.push_back (p[1]);
	p += 2;
      }
      continue;
    }
    if (p >= lim) {
      if (q)
	error ("closing '\"' missing");
      return str (arg.base (), arg.size ());
    }
    if (*p == '\"')
      q = !q;
    else if (q || !isspc (*p))
      arg.push_back (*p);
    else
      return str (arg.base (), arg.size ());
    p++;
  }
  return NULL;			// XXX - egcs bug
}

bool
parseargs::getline (vec<str> *args, int *linep)
{
  args->setsize (0);
  skipblanks ();
  if (linep)
    *linep = lineno;

  while (str s = getarg ())
    args->push_back (s);
  return args->size ();
}

void
parseargs::error (str msg)
{
  strbuf pref;
  if (filename)
    pref << filename << ":";
  if (lineno)
    pref << lineno << ": ";
  else
    pref << " ";

  fatal << pref << msg << "\n";
}

parseargs::parseargs (str file, int fd)
  : buf (errorbuf), lim (buf), p (buf), filename (file), lineno (0)
{
  if (fd == -1 && (fd = open (file, O_RDONLY, 0)) < 0)
    error (strbuf ("%m"));

  // XXX - should fstat fd for initial size, to optimize for common case
  // when fd is for a regular file.
  size_t pos = 0;
  size_t size = 128;
  buf = static_cast<char *> (xmalloc (size));

  for (;;) {
    ssize_t n = read (fd, buf + pos, size - pos);
    if (n < 0) {
      error (strbuf ("%m"));
      close (fd);
      return;
    }
    if (!n) {
      p = buf;
      lim = buf + pos;
      lineno = 1;
      close (fd);
      return;
    }
    pos += n;
    if (pos == size)
      size <<= 1;
    buf = static_cast<char *> (xrealloc (buf, size));
  }
}

parseargs::~parseargs ()
{
  if (buf != errorbuf)
    xfree (buf);
}


void
mytolower (char *dest, const char *src)
{
  while (*src) 
    *dest++ = tolower (*src++);
  *dest = 0;
}

str
mytolower (const str &in)
{
  const char *src = in.cstr ();
  char *dest = New char[in.len () + 1];
  mytolower (dest, src);
  str r (dest);
  delete [] dest;
  return r;
}

bool
conftab_str::convert (const vec<str> &v, const str &l, bool *e)
{
  if (dest) {
    if (!count_args (v, 2))
      return false;
    else 
      tmp_s = v[1];
  }
  else if (scb) {
    tmp_s = v[1];
  }
  else {
    tmp = v;
  }
  loc = l;
  errp = e;
  return true;
}

void
conftab_str::set ()
{
  if (dest) { 
    if (check) {
      if (dest->len ()) {
	warn << loc << ": " << name << ": variable already defined\n";
	*errp = true;
      }
      else {
	*dest = tmp_s;
      }
    }
    else
      *dest = tmp_s; 
  }
  else if (cnfcb) { 
    (*cnfcb) (tmp, loc, errp); 
  }
  else { 
    (*scb) (tmp_s); 
  }
}

bool
conftab_bool::convert (const vec<str> &v, const str &l, bool *e)
{
  if (!count_args (v, 2))
    return false;

  if (v[1] == "1") 
    tmp = true;
  else if (v[1] == "0")
    tmp = false;
  else 
    err = true;

  return (!err);
}

bool
conftab::match (const vec<str> &av, const str &cf, int ln, bool *err)
{
  if (av.size () < 1)
    return false;

  str k = mytolower (av[0]);
  conftab_el *el = tab[k];

  str loc = strbuf (cf) << ":" << ln;

  if (!el)
    return false;
  if (!el->convert (av, loc, err)) {
    warn << cf << ":" << ln << ": usage: " << el->name << " <value>\n";
    *err = true;
  }
  else if (!el->inbounds ()) {
    warn << cf << ":" << ln << ": " << el->name << " out of range\n";
    *err = true;
  }
  else 
    el->set ();
    
  return true;
}
