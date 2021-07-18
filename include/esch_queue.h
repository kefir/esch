/**
 * @file esch_queue.h
 * @author Sergey Tkachenko (saergey.iray@yandex.ru)
 * @brief 
 * @version 0.1
 * @date 2021-07-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esch_config.h"
#include "esch_err.h"

typedef struct {
    const uint32_t item_size;
    void* buffer;
    const uint32_t item_count;
    void* item_top;
    void* item_current;
    void* item_end;
    uint32_t count;
} esch_queue_t;

esch_err esch_queue_create(esch_queue_t* queue);
esch_err esch_queue_add(esch_queue_t* queue, void* item);
esch_err esch_queue_get(esch_queue_t* queue, void* item);

#ifdef __cplusplus
}
#endif
