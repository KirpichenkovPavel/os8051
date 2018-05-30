#include "dispatcher.h"
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

void addProcess(struct List *list, struct Process *process) {
    struct Node *last;
    struct Node node;
    node.process = process;
    if (list->length > 0) {
        last = getLast(list);
        node.prev = last;
        node.next = list->head;
    } else {
        node.prev = &node;
        node.next = &node;
    }
    list->length += 1;
}

void shiftList(struct List *list) {
    if (list->length == 0)
        return;
    list->head = list->head->next;
}

void initProcesses() {
    volatile struct Process process1, process2;

    initList(&processQueue);
    process1.id = 1;
    process2.id = 2;
    addProcess(&processQueue, &process1);
    addProcess(&processQueue, &process2);
}

//void timerSwitch(void) __interrupt (1) {
//
//}


void timer0Interrupt(void) __interrupt(1) {
    if (var == 0)
        var = 7;
    else
        var = 0;
}