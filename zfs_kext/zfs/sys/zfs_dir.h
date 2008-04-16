/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */
/*
 * Copyright 2007 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 *
 * Portions Copyright 2007-2008 Apple Inc. All rights reserved.
 * Use is subject to license terms.
 */

#ifndef	_SYS_FS_ZFS_DIR_H
#define	_SYS_FS_ZFS_DIR_H

#pragma ident	"%Z%%M%	%I%	%E% SMI"

#include <sys/dmu.h>
#include <sys/zfs_znode.h>

#ifdef	__cplusplus
extern "C" {
#endif

/* zfs_dirent_lock() flags */
#define	ZNEW		0x0001		/* entry should not exist */
#define	ZEXISTS		0x0002		/* entry should exist */
#define	ZSHARED		0x0004		/* shared access (zfs_dirlook()) */
#define	ZXATTR		0x0008		/* we want the xattr dir */
#define	ZRENAMING	0x0010		/* znode is being renamed */

/* mknode flags */
#define	IS_ROOT_NODE	0x01		/* create a root node */
#define	IS_XATTR	0x02		/* create an extended attribute node */
#define	IS_REPLAY	0x04		/* we are replaying intent log */

#ifdef __APPLE__
extern int zfs_dirent_lock(zfs_dirlock_t **, znode_t *, struct componentname *,
                           znode_t **, int);
#else
extern int zfs_dirent_lock(zfs_dirlock_t **, znode_t *, char *, znode_t **,
    int);
#endif
extern void zfs_dirent_unlock(zfs_dirlock_t *);
extern int zfs_link_create(zfs_dirlock_t *, znode_t *, dmu_tx_t *, int);
extern int zfs_link_destroy(zfs_dirlock_t *, znode_t *, dmu_tx_t *, int,
    boolean_t *);

#ifdef __APPLE__
extern int zfs_dirlook(znode_t *, char *, u_long, struct vnode **);
#else
extern int zfs_dirlook(znode_t *, char *, vnode_t **);
#endif

extern void zfs_mknode(znode_t *, vattr_t *, uint64_t *,
    dmu_tx_t *, cred_t *, uint_t, znode_t **, int);
extern void zfs_rmnode(znode_t *);
extern boolean_t zfs_dirempty(znode_t *);
extern void zfs_unlinked_add(znode_t *, dmu_tx_t *);
extern void zfs_unlinked_drain(zfsvfs_t *zfsvfs);
extern int zfs_sticky_remove_access(znode_t *, znode_t *, cred_t *cr);

#ifdef __APPLE__
extern int zfs_get_xattrdir(znode_t *, struct vnode **, cred_t *, int);
extern int zfs_make_xattrdir(znode_t *, vattr_t *, struct vnode **, cred_t *);
#else
extern int zfs_get_xattrdir(znode_t *, vnode_t **, cred_t *, int);
extern int zfs_make_xattrdir(znode_t *, vattr_t *, vnode_t **, cred_t *);
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_FS_ZFS_DIR_H */