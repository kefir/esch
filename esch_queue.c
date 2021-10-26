#include "esch_queue.h"
#include <string.h>

esch_err esch_queue_create(esch_queue_t* queue)
{
    esch_err err = ESCH_FAIL;

    if (queue) {
        if (queue->buffer) {
            queue->item_top = queue->buffer;
            queue->item_current = NULL;
            queue->item_end = (uint32_t*)queue->item_top + (queue->item_count) * queue->item_size;

            if (queue->item_count > 0) {
                queue->count = 0;
                memset(queue->buffer, 0, queue->item_size * queue->item_count);
                err = ESCH_OK;
            }
        }
    }

    return err;
}

esch_err esch_queue_add(esch_queue_t* queue, void* item)
{
    esch_err err = ESCH_FAIL;

    if (queue) {
        if (queue->buffer) {
            if (queue->count <= queue->item_count - 1) {
                if (queue->item_current) {
                    queue->item_current = (((uint32_t*)queue->item_current + queue->item_size) == queue->item_end)
                        ? queue->buffer
                        : ((uint32_t*)queue->item_current + queue->item_size);
                } else {
                    queue->item_current = queue->buffer;
                }
                memcpy(queue->item_current, item, queue->item_size);
                queue->count++;
                err = ESCH_OK;
            } else {
                err = ESCH_QUEUE_FULL;
            }
        }
    }

    return err;
}

esch_err esch_queue_get(esch_queue_t* queue, void* item)
{
    esch_err err = ESCH_FAIL;
    if (queue) {
        if (queue->buffer) {
            if (queue->count > 0) {
                memcpy(item, queue->item_top, queue->item_size);
                queue->item_top = (((uint32_t*)queue->item_top + queue->item_size) == queue->item_end)
                    ? queue->buffer
                    : ((uint32_t*)queue->item_top + queue->item_size);
                queue->count--;
                err = ESCH_OK;
            } else {
                err = ESCH_QUEUE_EMPTY;
            }
        }
    }
    return err;
}