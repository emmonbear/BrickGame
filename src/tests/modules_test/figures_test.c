/**
 * @file figures_test.c
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief 
 * @version 1.0
 * @date 2024-05-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "../main_test.h"

START_TEST(get_TET_I_test) {
  singleton *s = get_instance();
  init_game(s);
  
  while(s->figure.next_type != TET_I) {
    generate_new_figure(s);
  }
  destroy_game(s);
}

START_TEST(get_TET_Z_test) {
  singleton *s = get_instance();
  init_game(s);
  
  while(s->figure.next_type != TET_Z) {
    generate_new_figure(s);
  }
  destroy_game(s);
}

START_TEST(get_TET_S_test) {
  singleton *s = get_instance();
  init_game(s);
  
  while(s->figure.next_type != TET_S) {
    generate_new_figure(s);
  }
  destroy_game(s);
}

START_TEST(get_TET_T_test) {
  singleton *s = get_instance();
  init_game(s);
  
  while(s->figure.next_type != TET_T) {
    generate_new_figure(s);
  }
  destroy_game(s);
}

START_TEST(get_TET_L_test) {
  singleton *s = get_instance();
  init_game(s);
  
  while(s->figure.next_type != TET_L) {
    generate_new_figure(s);
  }
  destroy_game(s);
}

START_TEST(get_TET_J_test) {
  singleton *s = get_instance();
  init_game(s);
  
  while(s->figure.next_type != TET_J) {
    generate_new_figure(s);
  }
  destroy_game(s);
}

START_TEST(get_TET_O_test) {
  singleton *s = get_instance();
  init_game(s);
  
  while(s->figure.next_type != TET_O) {
    generate_new_figure(s);
  }
  destroy_game(s);
}

Suite *figures_test() {
  Suite *tetris = suite_create("figures tests:");

  TCase *tc_figures_test = tcase_create("figures test");
  tcase_add_test(tc_figures_test, get_TET_I_test);
  tcase_add_test(tc_figures_test, get_TET_Z_test);
  tcase_add_test(tc_figures_test, get_TET_S_test);
  tcase_add_test(tc_figures_test, get_TET_T_test);
  tcase_add_test(tc_figures_test, get_TET_L_test);
  tcase_add_test(tc_figures_test, get_TET_J_test);
  tcase_add_test(tc_figures_test, get_TET_O_test);

  suite_add_tcase(tetris, tc_figures_test);

  return tetris;
}