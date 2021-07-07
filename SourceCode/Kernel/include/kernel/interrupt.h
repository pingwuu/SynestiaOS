#ifndef __KERNEL_INTERRUPT_H__
#define __KERNEL_INTERRUPT_H__

#include "libc/stdint.h"
#include "libc/stdbool.h"
#include "kernel/list.h"

typedef void (*TickHandler)(void);

typedef struct Tick {
    char name[NAME_LENGTH];
    TickHandler handler;
    ListNode node;
} Tick;

Tick *tick_init(Tick *tick, TickHandler handler, const char *name);

typedef void (*InterruptHandler)(void);

typedef void (*InterruptClearHandler)(void);

typedef void (*InterruptEnableHandler)(void);

typedef void (*InterruptDisableHandler)(void);

typedef void (*InterruptPendingHandler)(void);

typedef struct Interrupt {
    uint32_t interruptNumber;
    InterruptHandler handler;
    InterruptPendingHandler pendingHandler;
    InterruptClearHandler clearHandler;
    InterruptEnableHandler enableHandler;
    InterruptDisableHandler disableHandler;
    char name[NAME_LENGTH];
} Interrupt;

typedef void (*InterruptManagerOperationRegisterTick)(struct InterruptManager *manager, Tick *tick);

typedef void (*InterruptManagerOperationUnRegisterTick)(struct InterruptManager *manager, Tick *tick);

typedef void (*InterruptManagerOperationRegister)(struct InterruptManager *manager, Interrupt interrupt);

typedef void (*InterruptManagerOperationUnRegister)(struct InterruptManager *manager, Interrupt interrupt);

typedef void (*InterruptManagerOperationEnableInterrupt)(struct InterruptManager *manager);

typedef void (*InterruptManagerOperationDisableInterrupt)(struct InterruptManager *manager);

typedef void (*InterruptManagerOperationInit)(struct InterruptManager *manager);

typedef void (*InterruptManagerOperationTick)(struct InterruptManager *manager);

typedef void (*InterruptManagerOperationInterrupt)(struct InterruptManager *manager);

typedef void (*InterruptManagerPhysicalInit)();

typedef void (*InterruptManagerOperationRegisterPhysicalInit)(struct InterruptManager *manager, InterruptManagerPhysicalInit init);

typedef struct InterruptManagerOperation {
    InterruptManagerOperationInit init;
    InterruptManagerOperationRegisterPhysicalInit registerPhysicalInit;
    InterruptManagerOperationRegister registerInterrupt;
    InterruptManagerOperationUnRegister unRegisterInterrupt;
    InterruptManagerOperationRegisterTick registerTick;
    InterruptManagerOperationUnRegisterTick unRegisterTick;
    InterruptManagerOperationEnableInterrupt enableInterrupt;
    InterruptManagerOperationDisableInterrupt disableInterrupt;
    InterruptManagerOperationTick tick;
    InterruptManagerOperationInterrupt interrupt;
} InterruptManagerOperation;

#define IRQ_NUMS 96
typedef struct InterruptManager {
    Interrupt interrupts[IRQ_NUMS];
    uint32_t registed[IRQ_NUMS];
    Tick *ticks;
    InterruptManagerOperation operation;
    InterruptManagerPhysicalInit physicalInit;
} InterruptManager;

InterruptManager *interrupt_manager_create(InterruptManager *manger);

#endif// __KERNEL_INTERRUPT_H__
