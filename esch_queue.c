#include "esch_queue.h"
#include <stdint.h>
#include <string.h>

esch_err esch_queue_create(esch_queue_t* queue)
{
    esch_err err = ESCH_FAIL;

    if (queue) {
        if (queue->buffer) {
            queue->_private._head = 0;
            queue->_private._tail = 0;
            queue->_private._count = 0;

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
            if (queue->_private._head != ((queue->_private._tail + 1) % queue->item_count)) {
                uintptr_t ptr = queue->_private._tail * queue->item_size + (uintptr_t)queue->buffer;
                memcpy((void*)ptr, item, queue->item_size);
                queue->_private._tail = (queue->_private._tail + 1) % queue->item_count;
                queue->_private._count++;
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
            if (queue->_private._head != queue->_private._tail) {
                uintptr_t ptr = queue->_private._head * queue->item_size + (uintptr_t)queue->buffer;
                memcpy(item, (void*)ptr, queue->item_size);
                queue->_private._head = (queue->_private._head + 1) % queue->item_count;
                queue->_private._count--;
                err = ESCH_OK;
            } else {
                err = ESCH_QUEUE_EMPTY;
            }
        }
    }
    return err;
}
