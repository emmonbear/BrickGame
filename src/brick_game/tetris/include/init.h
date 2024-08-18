/**
 * @file init.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-05-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef MODULES_INIT_H
#define MODULES_INIT_H

#include <stdio.h>
#include <stdlib.h>

#include "../../../common/include/common.h"
#include "./figures.h"
#include "./model.h"

void init_model(Model_t *model);
void destroy_model(Model_t *model);
void reset_game_info(Model_t *model);

#endif  // MODULES_INIT_H
