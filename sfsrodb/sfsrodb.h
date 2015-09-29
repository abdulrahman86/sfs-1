/* $Id: sfsrodb.h,v 1.8 2004/08/22 23:36:06 fubob Exp $ */

/*
 *
 * Copyright (C) 1999 Kevin Fu (fubob@mit.edu)
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

#ifndef _SFSRODB_H_
#define _SFSRODB_H_

#include "str.h"
#include "sfsro_prot.h"
#include "sfsrodb_core.h"
#include "sfsmisc.h"


#define SFSROSD_DB_FILE "/etc/sfsro.sdb"

#include "dbfe.h"
extern dbfe *sfsrodb;
extern dbfe *sfsrofhdb;

#if 0
#ifdef SLEEPYCAT
extern DB *sfsrodb;
extern DB *sfsrofhdb;
#else
extern btreeSync *sfsrodb;
extern btreeSync *sfsrofhdb;
#define NODE_SIZE 2048
#define DATA_MULT 1
#define CACHE_SIZE 2000000
#endif
#endif

/* Statistics */
extern u_int32_t reginode_cnt;
extern u_int32_t lnkinode_cnt;
extern u_int32_t filedatablk_cnt;
extern u_int32_t sindir_cnt;
extern u_int32_t dindir_cnt;
extern u_int32_t tindir_cnt;
extern u_int32_t directory_cnt;
extern u_int32_t fhdb_cnt;
extern u_int32_t fh_cnt;

extern u_int32_t identical_block;
extern u_int32_t identical_sindir;
extern u_int32_t identical_dindir;
extern u_int32_t identical_tindir;
extern u_int32_t identical_dir;
extern u_int32_t identical_inode;
extern u_int32_t identical_sym;
extern u_int32_t identical_fhdb;
extern u_int32_t identical_fh;

/* sfsrodb.C prototypes */
int recurse_directory (const str path, sfs_hash *fh);


/* fhdb.C prototypes */
int create_fhdb (sfs_hash *fhdb, const char *dbfile, char *iv);

template<class T> 
bool
store (T &data, sfs_hash *fh, sfs_hash *oldfh, bool propagate_change,
	size_t &bytes_written, sfsro_lockboxtype lt);


#endif /* _SFSRODB_H_ */
