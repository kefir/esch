/**
 * @file esch.c
 * @author Sergey Tkachenko (sergey.iray@yandex.ru)
 * @brief 
 * @version 0.0.1
 * @date 2021-05-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "esch.h"

#include <string.h>

static esch_task_t task_pool[ESCH_TASK_NUM + 1];

static uint32_t tick = 0;
static uint8_t tick_flag = 0;

static uint8_t esch_tick_flag_get();

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

    esch_port_init();
}

esch_task_t* esch_task_create(const char* name, uint32_t interval, uint16_t prio, esch_task_fn func, void* arg)
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
            task_pool[prio].elapsed = 0;
            task_pool[prio].priority = prio;
            task_pool[prio].interval = interval;
            task_pool[prio].function = func;
            if (arg) {
                task_pool[prio].arg = arg;
            }
        }
    }
    return &task_pool[prio];
}

void esch_task_delete(esch_task_t* task_handler)
{
    if (task_handler) {
        for (uint16_t i = 0; i < ESCH_TASK_NUM; i++) {
            if (task_handler == &task_pool[i]) {
                task_pool[i].function = NULL;
                task_pool[i].interval = 0;
                break;
            }
        }
    }
}

esch_task_t* esch_idle_task_register_callback(esch_task_fn func)
{
    task_pool[ESCH_TASK_NUM].function = func;
    task_pool[ESCH_TASK_NUM].interval = 0;
    return &task_pool[ESCH_TASK_NUM];
}

void esch_tick_advance()
{
    if (tick_flag) {
        // TODO: diagnostics for timing violations
    } else {
        tick_flag = 1;
    }

    tick++;
}

uint32_t esch_tick_get()
{
    return tick;
}

void esch_run()
{
    tick = 0;

    for (;;) {
        for (uint16_t i = 0; i < (ESCH_TASK_NUM + 1); i++) {
            esch_task_t* active_task = &task_pool[i];

            if (active_task->function) {
                if (active_task->elapsed >= active_task->interval) {
                    active_task->function(active_task->arg);
                    active_task->elapsed = 0;
                }
                active_task->elapsed++;
            }
        }

        tick_flag = 0;
        while (!esch_tick_flag_get()) { }
    }
}

inline uint32_t esch_ms_to_ticks(uint32_t msec)
{
    return msec * ESCH_TICK_FREQ / 1000U;
}

static uint8_t esch_tick_flag_get()
{
    return tick_flag;
}
