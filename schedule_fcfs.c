#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "task.h"
#include "list.h"
#include "schedulers.h"
#include "cpu.h"

struct node *g_head = NULL;

// add a task to the list
void add(char *name, int priority, int burst) {
    Task *task = malloc(sizeof(Task));
    task->name = strdup(name);
    task->priority = priority;
    task->burst = burst;
    // Append to end of the list for FCFS order
    struct node *new_node = malloc(sizeof(struct node));
    new_node->task = task;
    new_node->next = NULL;
    if (g_head == NULL) {
        g_head = new_node;
    } else {
        struct node *cur = g_head;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = new_node;
    }
}

// FCFS: always run the task at the head of the list
Task *pickNextTask() {
    if (g_head == NULL) {
        return NULL;
    }
    Task *task = g_head->task;
    // remove the head node
    struct node *old_head = g_head;
    g_head = g_head->next;
    free(old_head);
    return task;
}

// run the scheduler
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