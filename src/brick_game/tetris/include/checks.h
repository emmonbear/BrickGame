/**
 * @file checks.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-05-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef MODULES_CHECKS_H
#define MODULES_CHECKS_H

#include <stdbool.h>

#include "./common_module.h"

bool can_move_down(singleton *s);
bool can_move_left(singleton *s);
bool can_move_right(singleton *s);
bool can_rotate(singleton *s);
bool is_inside_figure(singleton *s, int y, int x);
void check_full_lines(singleton *s);

#endif  // MODULES_CHECKS_H