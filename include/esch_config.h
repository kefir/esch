#pragma once

/**
 * @brief User devined includes
 * 
 */
#include <time.h>

/**
 * @brief Number of user-defined tasks.
 * 
 */
#define ESCH_TASK_NUM 2

/**
 * @brief Size of task name. Should be lower for memory constrained systems.
 * 
 */
#define ESCH_TASK_NAME_SIZE 10

/**
 * @brief Timebase for the scheduler in Hz.
 * 
 */
#define ESCH_TICK_FREQ 1000

#define esch_get_time() clock()