/**
 * @file fsm_test.c
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

START_TEST(start_stage_test_1) {
  init_game(&s);
  s.stage = START;
  s.action = Start;
  reset_game_info(&s);
  generate_new_figure(&s);
  run_state(&s);
  destroy_game(&s);
}

START_TEST(start_stage_test_2) {
  init_game(&s);
  s.stage = START;
  s.action = Terminate;
  reset_game_info(&s);
  generate_new_figure(&s);
  run_state(&s);
  destroy_game(&s);
}

START_TEST(start_stage_test_3) {
  init_game(&s);
  s.stage = START;
  s.action = Left;
  reset_game_info(&s);
  generate_new_figure(&s);
  run_state(&s);
  destroy_game(&s);
}

START_TEST(game_over_stage_test_1) {
  init_game(&s);
  s.stage = GAME_OVER;
  s.action = Start;
  reset_game_info(&s);
  run_state(&s);
  destroy_game(&s);
}

START_TEST(game_over_stage_test_2) {
  init_game(&s);
  s.stage = GAME_OVER;
  s.action = Terminate;
  reset_game_info(&s);
  run_state(&s);
  destroy_game(&s);
}

START_TEST(game_over_stage_test_3) {
  init_game(&s);
  s.stage = GAME_OVER;
  s.action = Left;
  reset_game_info(&s);
  run_state(&s);
  destroy_game(&s);
}

START_TEST(shifting_stage_test_1) {
  init_game(&s);
  s.stage = SHIFTING;
  s.action = Left;
  reset_game_info(&s);
  run_state(&s);
  destroy_game(&s);
}

START_TEST(shifting_stage_test_2) {
  init_game(&s);
  s.stage = SHIFTING;
  s.action = Right;
  reset_game_info(&s);
  run_state(&s);
  destroy_game(&s);
}

START_TEST(shifting_stage_test_3) {
  init_game(&s);
  reset_game_info(&s);
  generate_new_figure(&s);
  spawn_stage(&s);
  s.stage = SHIFTING;
  s.action = Down;
  reset_game_info(&s);
  run_state(&s);
  destroy_game(&s);
}

START_TEST(shifting_stage_test_4) {
  init_game(&s);
  s.stage = SHIFTING;
  s.action = Action;
  reset_game_info(&s);
  run_state(&s);
  destroy_game(&s);
}

START_TEST(shifting_stage_test_5) {
  init_game(&s);
  s.stage = SHIFTING;
  s.action = Pause;
  reset_game_info(&s);
  run_state(&s);
  destroy_game(&s);
}

START_TEST(shifting_stage_test_6) {
  init_game(&s);
  s.stage = SHIFTING;
  s.action = Terminate;
  reset_game_info(&s);
  run_state(&s);
  destroy_game(&s);
}

START_TEST(shifting_stage_test_7) {
  init_game(&s);
  s.stage = SHIFTING;
  s.action = Start;
  reset_game_info(&s);
  run_state(&s);
  destroy_game(&s);
}

START_TEST(pause_stage_test_1) {
  init_game(&s);
  reset_game_info(&s);
  generate_new_figure(&s);
  spawn_stage(&s);
  s.stage = SHIFTING;
  s.action = Down;
  shifting_stage(&s);
  s.action = Pause;
  pause_stage(&s);
  destroy_game(&s);
}

START_TEST(pause_stage_test_2) {
  init_game(&s);
  reset_game_info(&s);
  generate_new_figure(&s);
  spawn_stage(&s);
  s.stage = SHIFTING;
  s.action = Down;
  shifting_stage(&s);
  s.action = Terminate;
  pause_stage(&s);
  destroy_game(&s);
}

START_TEST(pause_stage_test_3) {
  init_game(&s);
  reset_game_info(&s);
  generate_new_figure(&s);
  spawn_stage(&s);
  s.stage = SHIFTING;
  s.action = Down;
  shifting_stage(&s);
  attaching_stage(&s);
  destroy_game(&s);
}

START_TEST(attaching_stage_test_1) {
  init_game(&s);
  reset_game_info(&s);
  generate_new_figure(&s);
  spawn_stage(&s);
  s.stage = SHIFTING;
  s.action = Down;
  shifting_stage(&s);
  s.action = Start;
  pause_stage(&s);
  destroy_game(&s);
}

Suite *fsm_test() {
  Suite *tetris = suite_create("fsm tests:");

  TCase *tc_fsm_test = tcase_create("fsm test");
  tcase_add_test(tc_fsm_test, start_stage_test_1);
  tcase_add_test(tc_fsm_test, start_stage_test_2);
  tcase_add_test(tc_fsm_test, start_stage_test_3);
  tcase_add_test(tc_fsm_test, game_over_stage_test_1);
  tcase_add_test(tc_fsm_test, game_over_stage_test_2);
  tcase_add_test(tc_fsm_test, game_over_stage_test_3);
  tcase_add_test(tc_fsm_test, shifting_stage_test_1);
  tcase_add_test(tc_fsm_test, shifting_stage_test_2);
  tcase_add_test(tc_fsm_test, shifting_stage_test_3);
  tcase_add_test(tc_fsm_test, shifting_stage_test_4);
  tcase_add_test(tc_fsm_test, shifting_stage_test_5);
  tcase_add_test(tc_fsm_test, shifting_stage_test_6);
  tcase_add_test(tc_fsm_test, shifting_stage_test_7);
  tcase_add_test(tc_fsm_test, pause_stage_test_1);
  tcase_add_test(tc_fsm_test, pause_stage_test_2);
  tcase_add_test(tc_fsm_test, pause_stage_test_3);
  tcase_add_test(tc_fsm_test, attaching_stage_test_1);

  suite_add_tcase(tetris, tc_fsm_test);

  return tetris;
}