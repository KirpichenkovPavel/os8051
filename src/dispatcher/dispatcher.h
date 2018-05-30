#ifndef OS8051_DISPATCHER_H_H
#define OS8051_DISPATCHER_H_H

struct Process {
    int id;
};

struct Node {
    struct Process *next;
    struct Process *prev;
    struct Process *process;
};

struct List {
    struct Node *head;
    int length;
};

void initList(struct List *list);
void addProcess(struct List *list, struct Process *process);

#endif //OS8051_DISPATCHER_H_H
