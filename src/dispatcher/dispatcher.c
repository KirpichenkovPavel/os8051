#include "dispatcher.h"

void initList(struct List *list) {
    list->length = 0;
    list->head = 0;
}

struct Process* getLast(struct List *list) {
    if (list->length == 0)
        return 0;
    else
        return list->head->prev;
}

void addProcess(struct List *list, struct Process *process) {
    struct Process *last = getLast(list);
    struct Node node;
    node.prev = last;
    node.next = list->head->process;
    node.process = process;
    list->length += 1;
}