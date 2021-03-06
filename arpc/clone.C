/* $Id: clone.C,v 1.6 2002/02/24 03:48:24 dm Exp $ */

/*
 *
 * Copyright (C) 1999 David Mazieres (dm@uun.org)
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

#include "arpc.h"

int
axprt_clone::takefd ()
{
  int ret = fd;
  if (fd >= 0) {
    fdcb (fd, selread, NULL);
    fdcb (fd, selwrite, NULL);
    wcbset = false;
  }
  fd = -1;
  cb = NULL;
  return ret;
}

ssize_t
axprt_clone::doread (void *buf, size_t maxlen)
{
  if (pktlen < 4)
    return read (fd, buf, maxlen);
  u_int32_t psize = getint (pktbuf) & 0x7fffffffU;
  return read (fd, pktbuf + pktlen,
	       min<size_t> (maxlen, psize + 4 - pktlen));
}

void
axprt_clone::extract (int *fdp, str *datap)
{
  *datap = str (pktbuf, pktlen);
  *fdp = takefd ();
}

void
cloneserv_accept (ptr<axprt_unix> x, cloneserv_cb cb,
		  const char *pkt, ssize_t len, const sockaddr *)
{
  int fd = -1;
  if (pkt)
    fd = x->recvfd ();
  if (fd < 0) {
    x->setrcb (NULL);
    (*cb) (-1);
    return;
  }
  if (ptr<axprt_stream> cx = (*cb) (fd))
    cx->ungetpkt (pkt, len);
}

bool
cloneserv (int fd, cloneserv_cb cb, size_t ps)
{
  if (!isunixsocket (fd))
    return false;
  ref<axprt_unix> x = axprt_unix::alloc (fd, ps);
  x->setrcb (wrap (cloneserv_accept, x, cb));
  return true;
}
