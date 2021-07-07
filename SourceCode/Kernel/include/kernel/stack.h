//
// Created by XingfengYang on 2020/6/26.
//

#ifndef __KERNEL_STACK_H__
#define __KERNEL_STACK_H__

#include "kernel/type.h"
#include "libc/stdbool.h"
#include "libc/stdint.h"
#include "kernel/kheap.h"

#define DEFAULT_KERNEL_STACK_SIZE 32 * KB

typedef uint32_t VirtualAddress;

typedef KernelStatus (*StackOperationFree)(struct KernelStack *stack);

typedef KernelStatus (*StackOperationPush)(struct KernelStack *stack, uint32_t data);

typedef uint32_t (*StackOperationPop)(struct KernelStack *stack);

typedef uint32_t (*StackOperationPeek)(struct KernelStack *stack);

typedef bool (*StackOperationIsFull)(struct KernelStack *stack);

typedef bool (*StackOperationIsEmpty)(struct KernelStack *stack);

typedef KernelStatus (*StackOperationClear)(struct KernelStack *stack);

typedef struct StackOperations {
    StackOperationFree free;
    StackOperationPush push;
    StackOperationPop pop;
    StackOperationPeek peek;
    StackOperationIsFull isFull;
    StackOperationIsEmpty isEmpty;
    StackOperationClear clear;
} StackOperations;

typedef struct KernelStack {
    Heap *heap;
    uint32_t size;
    VirtualAddress base;
    VirtualAddress top;
    VirtualAddress *virtualMemoryAddress;
    StackOperations operations;
} KernelStack;

KernelStack *stack_allocate(Heap *heap, struct KernelStack *kernelStack);

#endif//__KERNEL_STACK_H__
