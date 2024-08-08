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

#include "./model.h"

bool can_move_down(Game_t *s);
bool can_move_left(Game_t *s);
bool can_move_right(Game_t *s);
bool can_rotate(Game_t *s);
bool is_inside_figure(Game_t *s, int y, int x);
void check_full_lines(Game_t *s);
bool can_put_new_line(Game_t *s);

#endif  // MODULES_CHECKS_H