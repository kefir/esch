#pragma once

#include "esch_config.h"

#include <stddef.h>
#include <stdint.h>

/**
 * @brief Task function callback.
 * Should be something like "void task_callback_name(void *arg)".
 * Should not be using for loops. 
 * 
 * Can accept argument(s) as a pointer.
 * 
 */
typedef void (*esch_task_fn)(void* args);

/**
 * @brief Task handle/descriptor.
 * 
 */
typedef struct {
    uint16_t priority;
    int interval;
    int elapsed;
    char name[ESCH_TASK_NAME_SIZE];
    esch_task_fn function;
    void* arg;
} esch_task_t;

/**
 * @brief Initializes the task pool with number of tasks defined by ESCH_TASK_NUM.
 * 
 */
void esch_init();

/**
 * @brief Initializes system-dependant peripherals. Implemented by user in esch_port.c.
 * TODO: details for esch_port_template.c
 * 
 */
void esch_port_init();

/**
 * @brief Creates a task and adds it to the pool.
 * 
 * @param name User-readable task name.
 * @param interval Interval in scheduler task ticks. Should be >= 1 of system ticks.
 * Can be 0 for one-time executed tasks that are expected to be deleted on completion.
 * @param prio Task prority. Highest priority is 0, lowest is (ESCH_TASK_NUM - 1).
 * Setting value outside this scope will result in an error.
 * @param func Pointer to task function.
 * @param arg Optional argument for the task. May be NULL.
 * @return esch_task_t* Returns pointer to task handle or NULL in case of an error.
 */
esch_task_t* esch_task_create(const char* name, uint32_t interval, uint16_t prio, esch_task_fn func, void* arg);

/**
 * @brief Deletes task from the pool 
 * and frees asscociated priority/id to be used for another user-defined task.
 * Invalid for idle task
 * 
 * @param task_handle Pointer to task handle
 */
void esch_task_delete(esch_task_t* task_handle);

/**
 * @brief Registers idle task callback.
 * If no idle task required this fucntion can accept NULL but not required
 * as esch_init function does this by default.
 * 
 * @param func 
 * @return esch_task_t* Returns pointer to idle task handle or NULL in case of an error.
 */
esch_task_t* esch_idle_task_register_callback(esch_task_fn func);

/**
 * @brief Advances system tick.
 * Should be called from system tick source, 
 * implemented by user in esch_port.c.
 * 
 */
void esch_tick_advance();

/**
 * @brief Get current ESCH system timer tick value. 
 * Counted from first esch_run call
 * 
 * @return uint32_t Returns system timer tick value.
 */
uint32_t esch_tick_get();

/**
 * @brief Runs scheduler
 * 
 */
void esch_run();
