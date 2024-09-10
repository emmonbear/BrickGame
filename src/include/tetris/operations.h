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

// bool can_move(Model_t *model, int dx, int dy) {
//     for (int i = 0; i < TETROMINO_SIZE; i++) {
//         for (int j = 0; j < TETROMINO_SIZE; j++) {
//             if (model->figure.current_figure[i][j]) {
//                 int new_x = model->figure.x + j + dx;
//                 int new_y = model->figure.y + i + dy;
//                 if (new_x < 0 || new_x >= WIDTH || new_y >= HEIGHT ||
//                     model->game_info.field[new_y][new_x] &&
//                     !is_inside_figure(model, new_y, new_x)) {
//                     return false;
//                 }
//             }
//         }
//     }
//     return true;
// }

// bool can_move_left(Model_t *model) {
//     return can_move(model, -1, 0);
// }

// bool can_move_right(Model_t *model) {
//     return can_move(model, 1, 0);
// }

// bool can_move_down(Model_t *model) {
//     return can_move(model, 0, 1);
// }

#endif  // SRC_INCLUDE_TETRIS_OPERATIONS_H_