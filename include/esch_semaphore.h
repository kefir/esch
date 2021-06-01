/**
 * @file esch_semaphore.h
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

#include "esch_config.h"
#include "esch_err.h"

/**
 * @brief Free semaphore identifier
 * 
 */
#define ESCH_SEMAPHORE_ID_FREE 0

/**
 * @brief Semaphore states
 * 
 */
typedef enum {
    ESCH_SEMAPHORE_FREE = 0U, /**< Semaphore is free*/
    ESCH_SEMAPHORE_TAKEN = 1U /**< Semaphore is taken*/
} esch_semaphore_state_e;

/**
 * @brief Semaphore handle/descriptor
 * 
 */
typedef struct {
    uint32_t id; /**< Unique identifier**/
    volatile esch_semaphore_state_e state; /**< Semaphore state of type esch_semaphore_state_e*/
} esch_semaphore_t;

/**
 * @brief Creates semaphore
 * 
 * @return esch_semaphore_t* Returns pointer to created semaphore or NULL in case of an error.
 */
esch_semaphore_t* esch_semaphore_create();

/**
 * @brief Requests semaphore lock
 * 
 * @param semaphore Semaphore handle pointer
 * 
 * @return esch_err Returns ESCH_OK on success or ESCH_LOCK if semaphore is already taken.
 */
esch_err esch_semaphore_take(esch_semaphore_t* semaphore);

/**
 * @brief Releases semaphore lock. Overrides current semaphore state.
 * 
 * @param semaphore Semaphore handle pointer
 * @return esch_err Returns ESCH_OK on success or ESCH_FAIL if operation failed for some reason.
 */
esch_err esch_semaphore_give(esch_semaphore_t* semaphore);

/**
 * @brief Deletes semaphore
 * 
 * @param semaphore Semaphore handle pointer
 * @return esch_err Returns ESCH_OK on success or ESCH_FAIL if operation failed for some reason.
 */
esch_err esch_semaphore_delete(esch_semaphore_t* semaphore);

#ifdef __cplusplus
}
#endif