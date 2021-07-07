//
// Created by XingfengYang on 2020/6/30.
//

#ifndef __KERNEL_RBTREE_H__
#define __KERNEL_RBTREE_H__

#include "kernel/kvector.h"
#include "kernel/list.h"
#include "kernel/type.h"
#include "libc/stdint.h"

typedef enum NodeColor {
    NODE_RED,
    NODE_BLACK,
} NodeColor;

typedef struct RBNode {
    struct RBNode *parent;
    struct RBNode *left;
    struct RBNode *right;
    NodeColor color;
} RBNode;

typedef RBNode *(*RBTreeInsertNode)(struct RBTree *tree, RBNode *node);

typedef RBNode *(*RbTreeGetMinNode)(struct RBTree *tree);

typedef RBNode *(*RbTreeGetMaxNode)(struct RBTree *tree);

typedef RBNode *(*RbTreeRemoveNode)(struct RBTree *tree, RBNode *node);

typedef struct RBTreeOperations {
    RBTreeInsertNode insert;
    RbTreeGetMinNode getMin;
    RbTreeGetMaxNode getMax;
    RbTreeRemoveNode remove;
} RBTreeOperations;

typedef struct RBTree {
    RBNode *root;
    RBTreeOperations operations;
} RBTree;

RBTree *rb_tree_init(RBTree *tree);

#endif//__KERNEL_RBTREE_H__
