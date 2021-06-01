#include "esch_semaphore.h"

#include <string.h>

static esch_semaphore_t semaphore_poll[ESCH_SEMAPHORE_NUM];
static uint32_t semaphore_count = 0;
static uint32_t semaphore_id_count = 0;

/**
 * @brief Initializes semaphore poll on first `esch_semaphore_create` call
 * 
 */
static void init();

esch_semaphore_t* esch_semaphore_create()
{
    esch_semaphore_t* return_ptr = NULL;
    if (semaphore_count < ESCH_SEMAPHORE_NUM) {
        if (semaphore_count == 0) {
            init();
        }

        esch_semaphore_t* semaphore_ptr = &semaphore_poll[0];

        for (uint32_t i = 0; i < ESCH_SEMAPHORE_NUM; i++, semaphore_ptr++) {
            if (semaphore_ptr->id == ESCH_SEMAPHORE_ID_FREE) {
                semaphore_ptr->id = ++semaphore_id_count;
                semaphore_ptr->state = ESCH_SEMAPHORE_FREE;
                semaphore_count++;
                return_ptr = semaphore_ptr;
                break;
            }
        }
    }
    return return_ptr;
}

esch_err esch_semaphore_take(esch_semaphore_t* semaphore)
{
    esch_err err = ESCH_FAIL;
    esch_semaphore_t* semaphore_ptr = &semaphore_poll[0];

    for (uint32_t i = 0; i < ESCH_SEMAPHORE_NUM; i++, semaphore_ptr++) {
        if (semaphore_ptr->id == semaphore->id && semaphore->id != ESCH_SEMAPHORE_ID_FREE) {
            if (semaphore->state == ESCH_SEMAPHORE_FREE) {
                semaphore->state = ESCH_SEMAPHORE_TAKEN;
                err = ESCH_OK;
            } else {
                err = ESCH_LOCK;
            }
            break;
        }
    }

    return err;
}

esch_err esch_semaphore_give(esch_semaphore_t* semaphore)
{
    esch_err err = ESCH_FAIL;
    esch_semaphore_t* semaphore_ptr = &semaphore_poll[0];

    for (uint32_t i = 0; i < ESCH_SEMAPHORE_NUM; i++, semaphore_ptr++) {
        if (semaphore_ptr->id == semaphore->id && semaphore->id != ESCH_SEMAPHORE_ID_FREE) {
            semaphore->state = ESCH_SEMAPHORE_FREE;
            err = ESCH_OK;
            break;
        }
    }
    return err;
}

esch_err esch_semaphore_delete(esch_semaphore_t* semaphore)
{
    esch_err err = ESCH_FAIL;
    esch_semaphore_t* semaphore_ptr = &semaphore_poll[0];

    for (uint32_t i = 0; i < ESCH_SEMAPHORE_NUM; i++, semaphore_ptr++) {
        if (semaphore_ptr->id == semaphore->id) {
            semaphore_ptr->id = ESCH_SEMAPHORE_ID_FREE;
            semaphore_ptr->state = ESCH_SEMAPHORE_FREE;
            semaphore_count--;
            err = ESCH_OK;
            break;
        }
    }

    return err;
}

static void init()
{
    memset(semaphore_poll, 0, sizeof(semaphore_poll));
}