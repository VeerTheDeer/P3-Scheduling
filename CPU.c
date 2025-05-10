/**
 * "Virtual" CPU that also maintains track of system time.
 */

#include <stdio.h>


#include "task.h"

// Bonus: counters for CPU utilization
int total_cpu_time = 0;
int total_dispatch_time = 0;
static int run_count = 0;

// run this task for the specified time slice
void run(Task *task, int slice) {
    // dispatch cost (1 unit) before each run after the first
    if (run_count > 0) {
        total_dispatch_time += 1;
    }
    total_cpu_time += slice;
    run_count++;
    printf("Running task = [%s] [%d] [%d] for %d units.\n",
           task->name, task->priority, task->burst, slice);
}
