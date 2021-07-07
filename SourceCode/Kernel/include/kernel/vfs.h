//
// Created by XingfengYang on 2020/7/30.
//

#ifndef __KERNEL_VFS_H__
#define __KERNEL_VFS_H__

#include "kernel/atomic.h"
#include "kernel/kvector.h"
#include "kernel/list.h"
#include "kernel/mutex.h"
#include "kernel/spinlock.h"
#include "kernel/vfs_super_block.h"

typedef SuperBlock *(*VFSOperationMount)(struct VFS *vfs, const char *name, FileSystemType type, void *data);

typedef uint32_t (*VFSOperationOpen)(struct VFS *vfs, const char *name, uint32_t mode);

typedef uint32_t (*VFSOperationClose)(struct VFS *vfs, uint32_t fd);

typedef DirectoryEntry *(*VFSOperationLookUp)(struct VFS *vfs, const char *name);

typedef uint32_t (*VFSOperationRead)(struct VFS *vfs, uint32_t fd, char *buffer, uint32_t pos, uint32_t count);

typedef uint32_t (*VFSOperationWrite)(struct VFS *vfs, uint32_t fd, char *buffer, uint32_t pos, uint32_t count);

typedef struct VFSOperations {
    VFSOperationMount mount;
    VFSOperationOpen open;
    VFSOperationClose close;
    VFSOperationRead read;
    VFSOperationWrite write;
    VFSOperationLookUp lookup;
} VFSOperations;

typedef struct VFS {
    struct SuperBlock *fileSystems;
    VFSOperations operations;
} VFS;

VFS *vfs_create(VFS *vfs);

uint32_t vfs_kernel_read(VFS *vfs, const char *name, char *buf, uint32_t count);

#endif// __KERNEL_VFS_H__
