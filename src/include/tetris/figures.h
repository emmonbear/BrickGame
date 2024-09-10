/**
 * @file figures.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-09-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_INCLUDE_TETRIS_FIGURES_H_
#define SRC_INCLUDE_TETRIS_FIGURES_H_

#include "./types.h"

type_t generate_random(type_t current_type);
void generate_new_figure(Model_t *model, GameInfo_t *game_info);
void set_start_position(figure_t *figure);
void copy_next_to_current(Model_t *model, GameInfo_t *game_info);

#endif  // SRC_INCLUDE_TETRIS_FIGURES_H_
