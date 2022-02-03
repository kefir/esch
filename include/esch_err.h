/**
 * @file esch_err.h
 * @author Sergey Tkachenko (sergey.iray@yandex.ru)
 * @brief
 * @version 0.1
 * @date 2021-06-01
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * @brief ESCH error types
 *
 */
typedef enum {
    ESCH_OK = 0U, /** No error */
    ESCH_FAIL, /** Generic error */
    ESCH_LOCK, /** Unable to access locked resource */
    ESCH_QUEUE_EMPTY, /** Queue is empty */
    ESCH_QUEUE_FULL, /** Queue is full */
} esch_err;

#ifdef __cplusplus
}
#endif