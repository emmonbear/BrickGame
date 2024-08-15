/**
 * @file fsm.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-08-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef FSM_H
#define FSM_H

#include <time.h>

#include "./checks.h"
#include "./figures.h"
#include "./init.h"
#include "./model.h"
#include "./operations.h"

typedef void (*func_ptr)(Model_t *model);

void run_state(Model_t *model);

#endif  // FSM_H
