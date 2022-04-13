#include "esch_queue.h"
#include <string.h>

esch_err esch_queue_create(esch_queue_t* queue)
{
    esch_err err = ESCH_FAIL;

    if (queue) {
        if (queue->buffer) {
            queue->private._head = 0;
            queue->private._tail = 0;
            queue->private._count = 0;

            if (queue->item_count > 0 && queue->item_size) {
                memset(queue->buffer, 0, (queue->item_size * queue->item_count));
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
            if (queue->private._head != ((queue->private._tail + 1) % queue->item_count)) {
                uint32_t ptr = queue->private._tail * queue->item_size + (uint32_t)queue->buffer;
                memcpy((void*)ptr, item, queue->item_size);
                queue->private._tail = (queue->private._tail + 1) % queue->item_count;
                queue->private._count++;
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
            if (queue->private._head != queue->private._tail) {
                uint32_t ptr = queue->private._head * queue->item_size + (uint32_t)queue->buffer;
                memcpy(item, (void*)ptr, queue->item_size);
                queue->private._head = (queue->private._head + 1) % queue->item_count;
                queue->private._count--;
                err = ESCH_OK;
            } else {
                err = ESCH_QUEUE_EMPTY;
            }
        }
    }
    return err;
}