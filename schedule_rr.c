#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "task.h"
#include "list.h"
#include "schedulers.h"
#include "cpu.h"

#define QUANTUM 10

struct node *g_head = NULL;

void add(char *name, int priority, int burst) {
    Task *task = malloc(sizeof(Task));
    task->name = strdup(name);
    task->priority = priority;
    task->burst = burst;
    insert(&g_head, task);
}

void schedule() {
    // move tasks to an array for round-robin
    Task *tasks[100];
    int n = 0;
    struct node *cur = g_head;
    while (cur) {
        tasks[n++] = cur->task;
        struct node *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    g_head = NULL;

    int currentTime = 0;
    int remaining = n;
    while (remaining > 0) {
        for (int i = 0; i < n; i++) {
            if (tasks[i] && tasks[i]->burst > 0) {
                int slice = tasks[i]->burst > QUANTUM ? QUANTUM : tasks[i]->burst;
                run(tasks[i], slice);
                tasks[i]->burst -= slice;
                currentTime += slice;
                printf("\tTime is now: %d\n", currentTime);
                if (tasks[i]->burst == 0) {
                    free(tasks[i]->name);
                    free(tasks[i]);
                    tasks[i] = NULL;
                    remaining--;
                }
            }
        }
    }
}