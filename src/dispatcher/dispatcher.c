#include "dispatcher.h"
#include <8052.h>
#define PROCESS_AMOUNT 10

volatile struct List processQueue;
volatile int var;


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
    int i;
    struct Process processes[PROCESS_AMOUNT];
    struct Node nodes[PROCESS_AMOUNT];

    initList(&processQueue);
    for (i = 0; i < PROCESS_AMOUNT; i++) {
        processes[i].id = i;
        nodes[i].process = &processes[i];
        addProcess(&processQueue, &nodes[i]);
        queueStatus();
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

void timer0Interrupt(void) __interrupt(1) {
    shiftList(&processQueue);
    queueStatus();
}