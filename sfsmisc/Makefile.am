## Process this file with automake to produce Makefile.in
# $Id: Makefile.am,v 1.53 2004/06/03 06:35:34 dm Exp $

sfslib_LTLIBRARIES = libsfsmisc.la
LIBSFSMISC = libsfsmisc.la

libsfsmisc_la_SOURCES = afsdir.C afsnode.C agentconn.C agentmisc.C	\
attrcache.C closesim.C findfs.C getfh3.C nfs3_err.C nfsserv.C		\
nfstrans.C nfs3attr.C nfsxattr.C pathexpand.C rexchan.C rexcommon.C	\
sfs_err.C sfsaid.C sfsauthorizer.C sfsclient.C sfsclientauth.C		\
sfsclientcredmap.C sfsconnect.C sfsconst.C sfskeyfetch.C sfskeymisc.C	\
sfspath.C sfsserv.C sfssesskey.C sfssrpconnect.C sfstty.C suidgetfd.C	\
unixserv.C uvfstrans.C sfscrypt.C sfsschnorr.C validshell.C		\
sfskeymgr.C sfsgroupmgr.C sfsusermgr.C sfshostalias.C

sfsinclude_HEADERS = afsnode.h agentconn.h agentmisc.h getfh3.h		\
nfs3_nonnul.h nfsserv.h nfstrans.h rex.h rexcommon.h sfsclient.h	\
sfsconnect.h sfskeymisc.h sfsmisc.h sfsserv.h sfssesscrypt.h sfstty.h	\
uvfstrans.h sfscrypt.h sfsschnorr.h sfskeymgr.h sfsgroupmgr.h		\
sfsusermgr.h

noinst_LIBRARIES = libmallock.a	# hack for automake to build mallock.o
libmallock_a_SOURCES = mallock.C

sfslib_DATA = mallock.o

DEPEND_ON_MAKEFILE = sfsconst.o sfsconst.lo
$(DEPEND_ON_MAKEFILE): Makefile

if REPO
sfsmisc_repo_OBJECTS = $(libsfsmisc_la_OBJECTS) \
	$(LIBSVC) $(LIBSFSCRYPT) $(LIBARPC) $(LIBASYNC)
stamp-sfsmisc-repo: $(sfsmisc_repo_OBJECTS)
	-$(CXXLINK) $(sfsmisc_repo_OBJECTS)
	@rm -f a.out
	touch $@
libsfsmisc_la_DEPENDENCIES = stamp-sfsmisc-repo
endif

EXTRA_DIST = .cvsignore
CLEANFILES = core *.core *~ *.rpo stamp-sfsmisc-repo
MAINTAINERCLEANFILES = Makefile.in
