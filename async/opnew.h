// -*-c++-*-
/* $Id: opnew.h,v 1.10 2002/05/28 06:43:38 dm Exp $ */

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

#ifndef _NEW_H_INCLUDED_
#define _NEW_H_INCLUDED_ 1

#include <new>
#include "sysconf.h"

using std::nothrow;

#ifdef DMALLOC
using std::nothrow_t;
static class dmalloc_init {
  static bool initialized;
  static void init ();
public:
  bool ok () { return initialized; }
  dmalloc_init () { if (!initialized) init (); }
} __dmalloc_init_obj;
struct dmalloc_t {};
extern struct dmalloc_t dmalloc;
void *operator new (size_t, dmalloc_t, const char *, int);
void *operator new[] (size_t, dmalloc_t, const char *, int);
void *operator new (size_t, nothrow_t, const char *, int) throw ();
void *operator new[] (size_t, nothrow_t, const char *, int) throw ();
#define ntNew new (nothrow, __FILE__, __LINE__)
#define New new (dmalloc, __FILE__, __LINE__)
#define opnew(size) operator new (size, dmalloc, __FILE__, __LINE__)
#if __GNUC__ >= 2
#define DSPRINTF_DEBUG 1
#endif /* GCC2 */
#else /* !DMALLOC */
#define ntNew new (nothrow)
#define New new
#define opnew(size) operator new(size)
#endif /* !DMALLOC */

#define vNew (void) New

template<class T> inline T
destroy_return (T &t)
{
  T ret = t;
  t.~T ();
  return ret;
}

// XXX - work around egcs 1.1.2 bug:
template<class T> inline T *
destroy_return (T *&tp)
{
  return tp;
}

#endif /* !_NEW_H_INCLUDED_ */
