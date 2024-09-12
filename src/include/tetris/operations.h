/**
 * @file operations.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-09-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_INCLUDE_TETRIS_OPERATIONS_H_
#define SRC_INCLUDE_TETRIS_OPERATIONS_H_

#include "./types.h"

void put_figure(Model_t *model, GameInfo_t *game_info);
void move_down(Model_t *model, GameInfo_t *game_info);
void remove_figure(Model_t *model, GameInfo_t *game_info);
void move_left(Model_t *model, GameInfo_t *game_info);
void move_right(Model_t *model, GameInfo_t *game_info);
void rotate_figure(Model_t *model, GameInfo_t *game_info);
void get_rotated_figure(Model_t *model);
void reset_field(GameInfo_t *game_info);
bool is_inside_figure(Model_t *model, int y, int x);
bool can_move_down(Model_t *model, GameInfo_t *game_info);
bool can_move_left(Model_t *model, GameInfo_t *game_info);
bool can_move_right(Model_t *model, GameInfo_t *game_info);
bool can_rotate(Model_t *model, GameInfo_t *game_info);
void check_full_lines(GameInfo_t *game_info);
bool can_put_new_line(Model_t *model, GameInfo_t *game_info);
bool is_out_of_bounds(int new_x, int new_y);
bool is_collision(Model_t *model, GameInfo_t *game_info, int new_x, int new_y);
bool can_move(Model_t *model, GameInfo_t *game_info, int dx, int dy);

#endif  // SRC_INCLUDE_TETRIS_OPERATIONS_H_
