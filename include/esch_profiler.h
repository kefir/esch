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

#if ESCH_USE_PROFILER == 1
/**
 * @brief Enables or disables task profiler runtime.
 *
 * @param enable
 */
void esch_profiler_enable(bool enable);
#endif

#ifdef __cplusplus
}
#endif