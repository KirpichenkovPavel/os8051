#include "dispatcher.h"
#include "../workers/workers.h"
#include <8052.h>
#define PROCESS_AMOUNT 10
#define STACK_SIZE 128
#define REGISTER_BANK_SIZE 8

__xdata volatile static struct List processQueue;
__xdata volatile static struct Process processes[PROCESS_AMOUNT];
__xdata volatile static struct Node nodes[PROCESS_AMOUNT];
__xdata volatile static unsigned char returnAddress[2];
__xdata static void (*routines[PROCESS_AMOUNT])(void) = {
        worker1, worker2, worker3, worker4, worker5,
        worker6, worker7, worker8, worker9, worker10
};

void initList(struct List *list) {
    list->length = 0;
    list->head = 0;
}

struct Node* getLast(struct List *list) {
    if (list->length == 0)
        return 0;
    else
        return list->head->prev;
}

void addProcess(struct List *list, struct Node *node) {
    struct Node *last, *head;

    last = getLast(list);
    head = list->head;
    if (list->length > 0) {
        node->prev = last;
        node->next = head;
        last->next = node;
        head->prev = node;
    } else {
        node->prev = node;
        node->next = node;
        list->head = node;
    }
    list->length += 1;
}

void shiftList(struct List *list) {
    if (list->length == 0)
        return;
    list->head = list->head->next;
}

void queueStatus() {
    P0 = processQueue.head->process->id;
    P1 = processQueue.head->next->process->id;
    P2 = processQueue.head->next->next->process->id;
    P3 = processQueue.head->next->next->next->process->id;
}

void initProcesses() {
    unsigned char i, j;
    unsigned int fooPointer;

    initList(&processQueue);
    for (i = 0; i < PROCESS_AMOUNT; i++) {
        processes[i].id = i;
        processes[i].routine = routines[i];
        for (j = 0; j < 8; j++)
        processes[i].screen[j] = 0xF0;
        nodes[i].process = &processes[i];
        addProcess(&processQueue, &nodes[i]);
        fooPointer = (unsigned int) processes[i].routine;
        processes[i].sp = SP;
        processes[i].stack[SP] = fooPointer >> 8;
        processes[i].stack[SP - 1] = fooPointer & 0x00FF;
        processes[i].sp += 13;
    }
}

void initTimer() {
    TMOD = 0x1;     // Timer mode.
    TL0 = 0;        // Clear
    TH0 = 0;        // Reg's.
    TR0 = 1;        // Set timer to run.
    ET0 = 1;        // Set interrupt.
    EA = 1;
}

void saveStack(unsigned char index) {
    __idata unsigned char *stack_pointer = 0;
    while (stack_pointer < (__idata unsigned char *)STACK_SIZE) {
        processes[index].stack[(unsigned char) stack_pointer] = *stack_pointer;
        stack_pointer++;
    }
}

void loadStack(unsigned char index) {
    __idata unsigned char *stack_pointer = (__idata unsigned char *)REGISTER_BANK_SIZE;

    returnAddress[0] = *(__idata unsigned char *)SP;
    returnAddress[1] = *(__idata unsigned char *)(SP - 1);
    while (stack_pointer < (__idata unsigned char *)STACK_SIZE) {
        *stack_pointer = processes[index].stack[(unsigned char) stack_pointer];
        stack_pointer++;
    }
    SP += 2;
    *(__idata unsigned char *)SP = returnAddress[0];
    *(__idata unsigned char *)(SP - 1) = returnAddress[1];
}

void timer0Interrupt(void) __interrupt(1) __naked {
    __asm
    push acc
    push b
    push dpl
    push dph
    push (0+7)
    push (0+6)
    push (0+5)
    push (0+4)
    push (0+3)
    push (0+2)
    push (0+1)
    push (0+0)
    push psw
    __endasm;
    processQueue.head->process->sp = SP;
    saveStack(processQueue.head->process->id);
    shiftList(&processQueue);
    loadStack(processQueue.head->process->id);
    SP = processQueue.head->process->sp;
    __asm
    pop	psw
    pop	(0+0)
    pop	(0+1)
    pop	(0+2)
    pop	(0+3)
    pop	(0+4)
    pop	(0+5)
    pop	(0+6)
    pop	(0+7)
    pop	dph
    pop	dpl
    pop	b
    pop	acc
    reti
    __endasm;
}
