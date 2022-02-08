/**
 * @file esch_profiler.h
 * @author Sergey Tkachenko (saergey.iray@yandex.ru)
 * @brief
 * @version 0.1
 * @date 2022-02-02
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esch_config.h"
#include "esch_err.h"

typedef struct {
    void (*timer_clear)(void);
    void (*timer_enable)(bool);
    uint32_t (*timer_count_get)(void);
} esch_profiler_t;

// TODO: add errors

void esch_profiler_init(esch_profiler_t* config);

/**
 * @brief Enables or disables task profiler runtime.
 *
 * @param enable
 */
void esch_profiler_enable(bool enable);

void esch_profiler_clear(void);

uint32_t esch_profiler_count_get(void);

#ifdef __cplusplus
}
#endif