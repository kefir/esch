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

/**
 * @brief Queue handle/descriptor
 * 
 */
typedef struct {
    const uint32_t item_size; /** User-defined item size */
    const uint32_t item_count; /** User-defined item count / queue length */
    void* buffer; /** User-defined pointer to queue memory. Should be (item_size * item_count) in size */
    void* item_top; /** Top item pointer. Should not be accessed by user */
    void* item_current; /** Current item pointer. Should not be accessed by user */
    void* item_end; /** Address of last item. Should not be accessed by user */
    uint32_t count; /** Quantity of items in queue. Should not be accessed by user */
} esch_queue_t;

/**
 * @brief Initializes the queue
 * 
 * ```c
 * #define BUFF_SIZE 5
 * static uint32_t buff[BUFF_SIZE];
 * 
 * esch_queue_t queue = {
 *      .item_size = sizeof(uint32_t),
 *      .item_count = BUFF_SIZE,
 *      .buffer = buff
 *  };
 * 
 * esch_queue_create(&queue);
 * ```
 * 
 * @note Must be called before using esch_queue_add or esch_queue_get
 * 
 * @param queue Pointer to queue object
 * @return esch_err 
 */
esch_err esch_queue_create(esch_queue_t* queue);

/**
 * @brief Adds item to the queue
 * 
 * @note item is copied into user-provided buffer
 * 
 * @param queue Pointer to queue object
 * @param item Item pointer
 * @return esch_err
 */
esch_err esch_queue_add(esch_queue_t* queue, void* item);

/**
 * @brief Copies item and removes it from queue 
 * 
 * @param queue Pointer to queue object
 * @param item Item pointer
 * @return esch_err 
 */
esch_err esch_queue_get(esch_queue_t* queue, void* item);

#ifdef __cplusplus
}
#endif
