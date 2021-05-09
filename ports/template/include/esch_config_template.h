/**
 * @file esch_config_template.h
 * @author Sergey Tkachenko (sergey.iray@yandex.ru)
 * @brief 
 * @version 0.0.1
 * @date 2021-05-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

/**
 * @brief User-defined includes.
 * 
 */

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
