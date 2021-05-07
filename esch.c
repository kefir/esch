#include "esch.h"

#include <stdio.h>
#include <string.h>

static esch_task_t task_pool[ESCH_TASK_NUM + 1];

static uint8_t tick_flag = 0;

void esch_init()
{
    memset(task_pool, 0, sizeof(task_pool));

    for (uint16_t task_prio = 0; task_prio < (ESCH_TASK_NUM + 1); task_prio++) {
        task_pool[task_prio].priority = task_prio;
        task_pool[task_prio].function = NULL;

        if (task_prio == ESCH_TASK_NUM) {
            strcpy(task_pool[task_prio].name, "ESCH_IDLE");
            task_pool[ESCH_TASK_NUM].interval = -1;
        }
    }
}

esch_task_t* esch_task_create(const char* name, uint32_t interval, uint16_t prio, esch_task_fn func)
{
    // check if desired priority is out of bounds
    if (prio >= ESCH_TASK_NUM) {
        return NULL;
    } else {
        // check if function with same priority was already defined in the pool
        if (task_pool[prio].function) {
            return NULL;
        } else {
            strcpy(task_pool[prio].name, name);
            task_pool[prio].priority = prio;
            task_pool[prio].interval = interval;
            task_pool[prio].function = func;
        }
    }
    return &task_pool[prio];
}

esch_task_t* esch_idle_task_register_callback(esch_task_fn func)
{
    task_pool[ESCH_TASK_NUM].function = func;
    task_pool[ESCH_TASK_NUM].interval = -1;
    return &task_pool[ESCH_TASK_NUM];
}

void esch_tick_advance()
{
    tick_flag = 1;
}

void esch_run()
{
    printf("Starting scheduler...\r\n");
    for (;;) {
        for (uint16_t i = 0; i < (ESCH_TASK_NUM + 1); i++) {
            esch_task_t* active_task = &task_pool[i];

            if (active_task->function) {
                if (active_task->elapsed >= active_task->interval || active_task->interval < 0) {
                    active_task->function(NULL);
                    active_task->elapsed = 0;
                }
                active_task->elapsed++;
            }
        }

        int msec = 0, trigger = 1; /* ms */

        clock_t before = esch_get_time();

        do {
            clock_t difference = esch_get_time() - before;
            msec = difference * ESCH_TICK_FREQ / CLOCKS_PER_SEC;

        } while (msec < trigger);
    }
}
