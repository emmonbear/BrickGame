/**
 * @file operations_test.c
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-05-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../main_test.h"

static Game_t s;

START_TEST(put_figure_test) {
  init_game(&s);

  reset_game_info(&s);
  generate_new_figure(&s);

  copy_next_to_current(&s);
  put_figure(&s);

  destroy_game(&s);
}

START_TEST(move_left_test) {
  init_game(&s);

  reset_game_info(&s);
  generate_new_figure(&s);

  copy_next_to_current(&s);
  put_figure(&s);
  move_left(&s);

  destroy_game(&s);
}

START_TEST(move_down_test) {
  init_game(&s);

  reset_game_info(&s);
  generate_new_figure(&s);

  copy_next_to_current(&s);
  put_figure(&s);
  move_down(&s);

  destroy_game(&s);
}

START_TEST(move_right_test) {
  init_game(&s);

  reset_game_info(&s);
  generate_new_figure(&s);

  copy_next_to_current(&s);
  put_figure(&s);
  move_down(&s);
  move_right(&s);

  destroy_game(&s);
}

START_TEST(rotate_figure_test) {
  init_game(&s);

  reset_game_info(&s);
  generate_new_figure(&s);

  copy_next_to_current(&s);
  put_figure(&s);
  move_down(&s);
  move_down(&s);
  move_down(&s);
  move_down(&s);
  move_down(&s);
  move_down(&s);
  rotate_figure(&s);

  destroy_game(&s);
}

START_TEST(get_rotated_figure_test) {
  init_game(&s);

  reset_game_info(&s);
  generate_new_figure(&s);

  copy_next_to_current(&s);
  get_rotated_figure(&s);

  destroy_game(&s);
}

START_TEST(get_rotated_figure_test_1) {
  init_game(&s);
  s.figure.current_figure[0][0] = 1;
  s.figure.current_figure[0][1] = 1;
  s.figure.current_figure[1][0] = 1;
  s.figure.current_figure[2][0] = 1;

  get_rotated_figure(&s);

  destroy_game(&s);
}

START_TEST(reset_field_test) {
  init_game(&s);

  reset_field(&s);

  destroy_game(&s);
}

Suite *operations_test() {
  Suite *tetris = suite_create("operations tests:");

  TCase *tc_operations_test = tcase_create("operations test");
  tcase_add_test(tc_operations_test, put_figure_test);
  tcase_add_test(tc_operations_test, move_left_test);
  tcase_add_test(tc_operations_test, move_down_test);
  tcase_add_test(tc_operations_test, move_right_test);
  tcase_add_test(tc_operations_test, rotate_figure_test);
  tcase_add_test(tc_operations_test, get_rotated_figure_test);
  tcase_add_test(tc_operations_test, get_rotated_figure_test_1);
  tcase_add_test(tc_operations_test, reset_field_test);

  suite_add_tcase(tetris, tc_operations_test);

  return tetris;
}