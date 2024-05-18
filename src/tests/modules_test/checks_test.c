/**
 * @file checks_test.c
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief 
 * @version 1.0
 * @date 2024-05-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "../main_test.h"


START_TEST(can_not_move_right_test_1) {
  singleton *s = get_instance();
  init_game(s);
  reset_game_info(s);
  generate_new_figure(s);
  spawn_stage(s);
  while(can_move_right(s)) {
    move_right(s);
  }
  destroy_game(s);
}

START_TEST(can_not_move_right_test_2) {
  singleton *s = get_instance();
  init_game(s);
  s->game_info->field[0][WIDTH - 1] = 1;
  s->game_info->field[1][WIDTH - 1] = 1;
  s->game_info->field[2][WIDTH - 1] = 1;
  s->game_info->field[3][WIDTH - 1] = 1;
  s->game_info->field[4][WIDTH - 1] = 1;
  reset_game_info(s);
  generate_new_figure(s);
  spawn_stage(s);
  while(can_move_right(s)) {
    move_right(s);
  }
  destroy_game(s);
}

START_TEST(can_not_move_left_test_1) {
  singleton *s = get_instance();
  init_game(s);
  reset_game_info(s);
  generate_new_figure(s);
  spawn_stage(s);
  while(can_move_left(s)) {
    move_left(s);
  }
  destroy_game(s);
}

START_TEST(can_not_move_left_test_2) {
  singleton *s = get_instance();
  init_game(s);
  s->game_info->field[0][0] = 1;
  s->game_info->field[1][0] = 1;
  s->game_info->field[2][0] = 1;
  s->game_info->field[3][0] = 1;
  s->game_info->field[4][0] = 1;
  reset_game_info(s);
  generate_new_figure(s);
  spawn_stage(s);
  while(can_move_left(s)) {
    move_left(s);
  }
  destroy_game(s);
}


START_TEST(can_not_move_down_test_1) {
  singleton *s = get_instance();
  init_game(s);

  reset_game_info(s);
  generate_new_figure(s);
  spawn_stage(s);
  while(can_move_down(s)) {
    move_down(s);
  }
  destroy_game(s);
}

START_TEST(can_not_move_down_test_2) {
  singleton *s = get_instance();
  init_game(s);

  reset_game_info(s);
  generate_new_figure(s);
  spawn_stage(s);
  s->game_info->field[WIDTH - 1][0] = 1;
  s->game_info->field[WIDTH - 1][1] = 1;
  s->game_info->field[WIDTH - 1][2] = 1;
  s->game_info->field[WIDTH - 1][3] = 1;
  s->game_info->field[WIDTH - 1][4] = 1;
  s->game_info->field[WIDTH - 1][5] = 1;
  s->game_info->field[WIDTH - 1][6] = 1;
  s->game_info->field[WIDTH - 1][7] = 1;
  s->game_info->field[WIDTH - 1][8] = 1;
  s->game_info->field[WIDTH - 1][9] = 1;
  while(can_move_down(s)) {
    move_down(s);
  }
  destroy_game(s);
}



START_TEST(can_rotate_test_1) {
  singleton *s = get_instance();
  init_game(s);
  reset_game_info(s);
  generate_new_figure(s);
  spawn_stage(s);

  move_down(s);
  if(can_rotate(s)) {
    rotate_figure(s);
  }

  destroy_game(s);
}

START_TEST(can_rotate_test_2) {
  singleton *s = get_instance();
  init_game(s);
  reset_game_info(s);
  
  s->figure.current_figure[0][1] = 1; 
  s->figure.current_figure[1][1] = 1; 
  s->figure.current_figure[2][1] = 1; 
  s->figure.current_figure[3][1] = 1; 
  get_rotated_figure(s);
  move_down(s);
  while(can_move_right(s)) {
    move_right(s);
  }
  
  if(can_rotate(s)) {
    rotate_figure(s);
  }

  destroy_game(s);
}

START_TEST(check_full_lines_test_1) {
  singleton *s = get_instance();
  init_game(s);
  reset_game_info(s);
  generate_new_figure(s);
  spawn_stage(s);
  while (can_move_down(s)) {
    move_down(s);
  }
  check_full_lines(s);

  destroy_game(s);
}

START_TEST(check_full_lines_test_2) {
  singleton *s = get_instance();
  init_game(s);
  reset_game_info(s);
  for(int i = HEIGHT - 1; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      s->game_info->field[i][j] = 1;
    }
  }
  check_full_lines(s);

  destroy_game(s);
}

START_TEST(check_full_lines_test_3) {
  singleton *s = get_instance();
  init_game(s);
  reset_game_info(s);
  for(int i = HEIGHT - 2; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      s->game_info->field[i][j] = 1;
    }
  }
  check_full_lines(s);

  destroy_game(s);
}

START_TEST(check_full_lines_test_4) {
  singleton *s = get_instance();
  init_game(s);
  reset_game_info(s);
  for(int i = HEIGHT - 3; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      s->game_info->field[i][j] = 1;
    }
  }
  check_full_lines(s);

  destroy_game(s);
}

START_TEST(check_full_lines_test_5) {
  singleton *s = get_instance();
  init_game(s);
  reset_game_info(s);
  for(int i = HEIGHT - 4; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      s->game_info->field[i][j] = 1;
    }
  }
  check_full_lines(s);

  destroy_game(s);
}

START_TEST(hign_score_test) {
  singleton *s = get_instance();
  init_game(s);
  reset_game_info(s);
  s->game_info->high_score = 100;
  for(int i = HEIGHT - 4; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      s->game_info->field[i][j] = 1;
    }
  }
  check_full_lines(s);

  destroy_game(s);
}

START_TEST(update_level_test) {
  singleton *s = get_instance();
  init_game(s);
  reset_game_info(s);
  s->game_info->score = 7000;
  for(int i = HEIGHT - 4; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      s->game_info->field[i][j] = 1;
    }
  }
  check_full_lines(s);

  destroy_game(s);
}

START_TEST(can_put_new_line_test_1) {
  singleton *s = get_instance();
  init_game(s);
  reset_game_info(s);
  can_put_new_line(s);
  destroy_game(s);
}

START_TEST(can_put_new_line_test_2) {
  singleton *s = get_instance();
  init_game(s);
  reset_game_info(s);
  generate_new_figure(s);
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      s->game_info->field[i][j] = 1;
    }
  }
  can_put_new_line(s);
  destroy_game(s);
}


Suite *checks_test() {
  Suite *tetris = suite_create("checks tests:");

  TCase *tc_checks_test = tcase_create("checks test");
  tcase_add_test(tc_checks_test, can_not_move_right_test_1);
  tcase_add_test(tc_checks_test, can_not_move_right_test_2);
  tcase_add_test(tc_checks_test, can_not_move_left_test_1);
  tcase_add_test(tc_checks_test, can_not_move_left_test_2);
  tcase_add_test(tc_checks_test, can_not_move_down_test_1);
  tcase_add_test(tc_checks_test, can_not_move_down_test_2);
  tcase_add_test(tc_checks_test, can_rotate_test_1);
  tcase_add_test(tc_checks_test, can_rotate_test_2);
  tcase_add_test(tc_checks_test, check_full_lines_test_1);
  tcase_add_test(tc_checks_test, check_full_lines_test_2);
  tcase_add_test(tc_checks_test, check_full_lines_test_3);
  tcase_add_test(tc_checks_test, check_full_lines_test_4);
  tcase_add_test(tc_checks_test, check_full_lines_test_5);
  tcase_add_test(tc_checks_test, hign_score_test);
  tcase_add_test(tc_checks_test, update_level_test);
  tcase_add_test(tc_checks_test, can_put_new_line_test_1);
  tcase_add_test(tc_checks_test, can_put_new_line_test_2);

  suite_add_tcase(tetris, tc_checks_test);

  return tetris;
}