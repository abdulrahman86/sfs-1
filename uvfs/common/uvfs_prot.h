/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _UVFS_PROT_H_RPCGEN
#define _UVFS_PROT_H_RPCGEN

#include "arpc.h"

#include "nfs3exp_prot.h"

typedef u_int32_t uvfs_fh;
RPC_EXTERN bool_t xdr_uvfs_fh(XDR *, uvfs_fh *);

typedef ex_fattr3 uvfs_fattr;
RPC_EXTERN bool_t xdr_uvfs_fattr(XDR *, uvfs_fattr *);

typedef ex_getattr3res uvfs_attrres;
RPC_EXTERN bool_t xdr_uvfs_attrres(XDR *, uvfs_attrres *);

typedef ex_wccstat3 uvfs_wccstat;
RPC_EXTERN bool_t xdr_uvfs_wccstat(XDR *, uvfs_wccstat *);

typedef ex_access3res uvfs_accessres;
RPC_EXTERN bool_t xdr_uvfs_accessres(XDR *, uvfs_accessres *);

typedef ex_readlink3res uvfs_readlinkres;
RPC_EXTERN bool_t xdr_uvfs_readlinkres(XDR *, uvfs_readlinkres *);

typedef ex_read3res uvfs_readres;
RPC_EXTERN bool_t xdr_uvfs_readres(XDR *, uvfs_readres *);

typedef ex_write3res uvfs_writeres;
RPC_EXTERN bool_t xdr_uvfs_writeres(XDR *, uvfs_writeres *);

typedef ex_rename3res uvfs_renameres;
RPC_EXTERN bool_t xdr_uvfs_renameres(XDR *, uvfs_renameres *);

typedef ex_link3res uvfs_linkres;
RPC_EXTERN bool_t xdr_uvfs_linkres(XDR *, uvfs_linkres *);

typedef ex_fsstat3res uvfs_statfsres;
RPC_EXTERN bool_t xdr_uvfs_statfsres(XDR *, uvfs_statfsres *);

typedef ex_commit3res uvfs_commitres;
RPC_EXTERN bool_t xdr_uvfs_commitres(XDR *, uvfs_commitres *);

typedef filename3 uvfs_filename;
RPC_EXTERN bool_t xdr_uvfs_filename(XDR *, uvfs_filename *);

typedef nfspath3 uvfs_pathname;
RPC_EXTERN bool_t xdr_uvfs_pathname(XDR *, uvfs_pathname *);

typedef nfstime3 uvfs_time;
RPC_EXTERN bool_t xdr_uvfs_time(XDR *, uvfs_time *);

typedef sattr3 uvfs_sattr;
RPC_EXTERN bool_t xdr_uvfs_sattr(XDR *, uvfs_sattr *);

typedef sattrguard3 uvfs_guard;
RPC_EXTERN bool_t xdr_uvfs_guard(XDR *, uvfs_guard *);

typedef int uvfsstat;
RPC_EXTERN bool_t xdr_uvfsstat(XDR *, uvfsstat *);

typedef struct uvfs_readdirargs {
	uvfs_fh dir;
	u_int64_t cookie;
	u_int32_t count;
} uvfs_readdirargs;
RPC_EXTERN bool_t xdr_uvfs_readdirargs(XDR *, uvfs_readdirargs *);
RPC_CONSTRUCT (Uvfs_readdirargs, uvfs_readdirargs)

typedef struct uvfs_direntry {
	u_int64_t fileid;
	u_int64_t cookie;
	u_int32_t type;
	uvfs_filename name;
} uvfs_direntry;
RPC_EXTERN bool_t xdr_uvfs_direntry(XDR *, uvfs_direntry *);
RPC_CONSTRUCT (Uvfs_direntry, uvfs_direntry)

typedef struct uvfs_dirlist {
	struct {
		u_int len;
		uvfs_direntry *val;
	} entries;
	bool_t eof;
} uvfs_dirlist;
RPC_EXTERN bool_t xdr_uvfs_dirlist(XDR *, uvfs_dirlist *);
RPC_CONSTRUCT (Uvfs_dirlist, uvfs_dirlist)

typedef struct uvfs_readdirres {
	uvfsstat status;
	union {
		uvfs_dirlist reply;
	} RPC_UNION_NAME(uvfs_readdirres);
} uvfs_readdirres;
RPC_EXTERN bool_t xdr_uvfs_readdirres(XDR *, uvfs_readdirres *);
RPC_CONSTRUCT (Uvfs_readdirres, uvfs_readdirres)

typedef struct uvfs_setattrargs {
	uvfs_fh file;
	uvfs_sattr attributes;
	uvfs_guard guard;
} uvfs_setattrargs;
RPC_EXTERN bool_t xdr_uvfs_setattrargs(XDR *, uvfs_setattrargs *);
RPC_CONSTRUCT (Uvfs_setattrargs, uvfs_setattrargs)

typedef struct post_op_uvfs_fh {
	bool_t present;
	union {
		uvfs_fh handle;
	} RPC_UNION_NAME(post_op_uvfs_fh);
} post_op_uvfs_fh;
RPC_EXTERN bool_t xdr_post_op_uvfs_fh(XDR *, post_op_uvfs_fh *);
RPC_CONSTRUCT (Post_op_uvfs_fh, post_op_uvfs_fh)

typedef struct uvfs_diropargs {
	uvfs_fh dir;
	uvfs_filename name;
} uvfs_diropargs;
RPC_EXTERN bool_t xdr_uvfs_diropargs(XDR *, uvfs_diropargs *);
RPC_CONSTRUCT (Uvfs_diropargs, uvfs_diropargs)

typedef struct uvfs_diropresok {
	post_op_uvfs_fh file;
	ex_post_op_attr attributes;
	ex_wcc_data dir_wcc;
} uvfs_diropresok;
RPC_EXTERN bool_t xdr_uvfs_diropresok(XDR *, uvfs_diropresok *);
RPC_CONSTRUCT (Uvfs_diropresok, uvfs_diropresok)

typedef struct uvfs_diropres {
	uvfsstat status;
	union {
		uvfs_diropresok resok;
		wcc_data resfail;
	} RPC_UNION_NAME(uvfs_diropres);
} uvfs_diropres;
RPC_EXTERN bool_t xdr_uvfs_diropres(XDR *, uvfs_diropres *);
RPC_CONSTRUCT (Uvfs_diropres, uvfs_diropres)

typedef struct uvfs_readargs {
	uvfs_fh file;
	u_int64_t offset;
	u_int32_t count;
} uvfs_readargs;
RPC_EXTERN bool_t xdr_uvfs_readargs(XDR *, uvfs_readargs *);
RPC_CONSTRUCT (Uvfs_readargs, uvfs_readargs)

typedef struct uvfs_writeargs {
	uvfs_fh file;
	u_int64_t offset;
	u_int32_t count;
	stable_how stable;
	struct {
		u_int len;
		char *val;
	} data;
} uvfs_writeargs;
RPC_EXTERN bool_t xdr_uvfs_writeargs(XDR *, uvfs_writeargs *);
RPC_CONSTRUCT (Uvfs_writeargs, uvfs_writeargs)

typedef struct uvfs_createargs {
	uvfs_diropargs where;
	createhow3 how;
} uvfs_createargs;
RPC_EXTERN bool_t xdr_uvfs_createargs(XDR *, uvfs_createargs *);
RPC_CONSTRUCT (Uvfs_createargs, uvfs_createargs)

typedef struct uvfs_mkdirargs {
	uvfs_diropargs where;
	uvfs_sattr attributes;
} uvfs_mkdirargs;
RPC_EXTERN bool_t xdr_uvfs_mkdirargs(XDR *, uvfs_mkdirargs *);
RPC_CONSTRUCT (Uvfs_mkdirargs, uvfs_mkdirargs)

typedef struct uvfs_renameargs {
	uvfs_diropargs from;
	uvfs_diropargs to;
} uvfs_renameargs;
RPC_EXTERN bool_t xdr_uvfs_renameargs(XDR *, uvfs_renameargs *);
RPC_CONSTRUCT (Uvfs_renameargs, uvfs_renameargs)

typedef struct uvfs_commitargs {
	uvfs_fh file;
	u_int64_t offset;
	u_int32_t count;
} uvfs_commitargs;
RPC_EXTERN bool_t xdr_uvfs_commitargs(XDR *, uvfs_commitargs *);
RPC_CONSTRUCT (Uvfs_commitargs, uvfs_commitargs)

typedef struct uvfs_linkargs {
	uvfs_fh from;
	uvfs_diropargs to;
} uvfs_linkargs;
RPC_EXTERN bool_t xdr_uvfs_linkargs(XDR *, uvfs_linkargs *);
RPC_CONSTRUCT (Uvfs_linkargs, uvfs_linkargs)

typedef struct uvfs_symlinkargs {
	uvfs_diropargs where;
	symlinkdata3 symlink;
} uvfs_symlinkargs;
RPC_EXTERN bool_t xdr_uvfs_symlinkargs(XDR *, uvfs_symlinkargs *);
RPC_CONSTRUCT (Uvfs_symlinkargs, uvfs_symlinkargs)

typedef struct uvfs_accessargs {
	uvfs_fh object;
	u_int32_t access;
} uvfs_accessargs;
RPC_EXTERN bool_t xdr_uvfs_accessargs(XDR *, uvfs_accessargs *);
RPC_CONSTRUCT (Uvfs_accessargs, uvfs_accessargs)

typedef struct uvfs_lookupresok {
	uvfs_fh object;
	ex_post_op_attr obj_attributes;
	ex_post_op_attr dir_attributes;
} uvfs_lookupresok;
RPC_EXTERN bool_t xdr_uvfs_lookupresok(XDR *, uvfs_lookupresok *);
RPC_CONSTRUCT (Uvfs_lookupresok, uvfs_lookupresok)

typedef struct uvfs_lookupres {
	uvfsstat status;
	union {
		uvfs_lookupresok resok;
		ex_post_op_attr resfail;
	} RPC_UNION_NAME(uvfs_lookupres);
} uvfs_lookupres;
RPC_EXTERN bool_t xdr_uvfs_lookupres(XDR *, uvfs_lookupres *);
RPC_CONSTRUCT (Uvfs_lookupres, uvfs_lookupres)

typedef struct uvfs_invalidateargs {
	uvfs_fh handle;
	ex_post_op_attr attributes;
} uvfs_invalidateargs;
RPC_EXTERN bool_t xdr_uvfs_invalidateargs(XDR *, uvfs_invalidateargs *);
RPC_CONSTRUCT (Uvfs_invalidateargs, uvfs_invalidateargs)

#define UVFSPROG ((u_long)0x20000001)
RPC_EXTERN const struct rpcgen_table uvfsprog_1_table[];
RPC_EXTERN const int uvfsprog_1_nproc;
RPC_EXTERN const struct rpc_program  uvfsprog_1;
#define UVFSVER ((u_long)1)
#define UVFSPROC_NULL ((u_long)0)
#define UVFSPROC_GETATTR ((u_long)1)
#define UVFSPROC_SETATTR ((u_long)2)
#define UVFSPROC_LOOKUP ((u_long)3)
#define UVFSPROC_ACCESS ((u_long)4)
#define UVFSPROC_READLINK ((u_long)5)
#define UVFSPROC_READ ((u_long)6)
#define UVFSPROC_WRITE ((u_long)7)
#define UVFSPROC_CREATE ((u_long)8)
#define UVFSPROC_MKDIR ((u_long)9)
#define UVFSPROC_SYMLINK ((u_long)10)
#define UVFSPROC_MKNOD ((u_long)11)
#define UVFSPROC_REMOVE ((u_long)12)
#define UVFSPROC_RMDIR ((u_long)13)
#define UVFSPROC_RENAME ((u_long)14)
#define UVFSPROC_LINK ((u_long)15)
#define UVFSPROC_READDIR ((u_long)16)
#define UVFSPROC_READDIRPLUS ((u_long)17)
#define UVFSPROC_STATFS ((u_long)18)
#define UVFSPROC_FSINFO ((u_long)19)
#define UVFSPROC_PATHCONF ((u_long)20)
#define UVFSPROC_COMMIT ((u_long)21)
#define UVFSPROC_OPEN ((u_long)22)
#define UVFSPROC_CLOSE ((u_long)23)
#define UVFSPROC_INACTIVE ((u_long)24)
#define UVFSPROC_RECLAIM ((u_long)25)

#define UVFSCBPROG ((u_long)0x20000002)
RPC_EXTERN const struct rpcgen_table uvfscbprog_1_table[];
RPC_EXTERN const int uvfscbprog_1_nproc;
RPC_EXTERN const struct rpc_program  uvfscbprog_1;
#define UVFSCBVER ((u_long)1)
#define UVFSCBPROC_NULL ((u_long)0)
#define UVFSCBPROC_INVALIDATE ((u_long)1)


#endif /* !_UVFS_PROT_H_RPCGEN */