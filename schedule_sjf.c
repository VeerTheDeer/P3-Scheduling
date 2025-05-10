#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "task.h"
#include "list.h"
#include "schedulers.h"
#include "cpu.h"

struct node *g_head = NULL;

void add(char *name, int priority, int burst) {
    Task *task = malloc(sizeof(Task));
    task->name = strdup(name);
    task->priority = priority;
    task->burst = burst;
    insert(&g_head, task);
}

bool comesBefore(char *a, char *b) {
    return strcmp(a, b) < 0;
}

Task *pickNextTask() {
    if (!g_head) return NULL;

    struct node *temp = g_head;
    Task *best = temp->task;
    while (temp) {
        if (temp->task->burst < best->burst ||
           (temp->task->burst == best->burst && comesBefore(temp->task->name, best->name))) {
            best = temp->task;
        }
        temp = temp->next;
    }
    delete(&g_head, best);
    return best;
}

void schedule() {
    Task *task;
    int currentTime = 0;
    while ((task = pickNextTask()) != NULL) {
        run(task, task->burst);
        currentTime += task->burst;
        printf("\tTime is now: %d\n", currentTime);
        free(task->name);
        free(task);
    }
}