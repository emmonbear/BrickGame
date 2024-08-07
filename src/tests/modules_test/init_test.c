/**
 * @file init_test.c
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-05-16
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../main_test.h"

static Game_t s;

START_TEST(init_game_test) {
  init_game(&s);
  destroy_game(&s);
}

START_TEST(double_destroy_game_test) {
  init_game(&s);
  destroy_game(&s);
  destroy_game(&s);
}

START_TEST(reset_game_info_test) {
  init_game(&s);
  reset_game_info(&s);
  destroy_game(&s);
}

START_TEST(write_high_score_test) {
  init_game(&s);
  reset_game_info(&s);
  write_high_score(&s);
  destroy_game(&s);
}

Suite *init_test() {
  Suite *tetris = suite_create("init tests:");

  TCase *tc_init_test = tcase_create("init test");
  tcase_add_test(tc_init_test, init_game_test);
  tcase_add_test(tc_init_test, double_destroy_game_test);
  tcase_add_test(tc_init_test, reset_game_info_test);
  tcase_add_test(tc_init_test, write_high_score_test);
  suite_add_tcase(tetris, tc_init_test);

  return tetris;
}