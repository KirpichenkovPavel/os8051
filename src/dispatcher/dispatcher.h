#ifndef OS8051_DISPATCHER_H_H
#define OS8051_DISPATCHER_H_H

extern volatile int var;

struct Process {
    int id;
};

struct Node {
    struct Node *next;
    struct Node *prev;
    struct Process *process;
};

struct List {
    struct Node *head;
    int length;
};

void initList(struct List *list);
void addProcess(struct List *list, struct Node *node);
void initProcesses();
void timer0Interrupt(void) __interrupt(1);
void initTimer();

#endif //OS8051_DISPATCHER_H_H
