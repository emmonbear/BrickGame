/**
 * @file brick_game.c
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief 
 * @version 1.0
 * @date 2024-05-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "./brick_game/tetris/include/fsm.h"
#include "./gui/cli/include/field_gui.h"
#include "./gui/cli/include/input_gui.h"
#include "./gui/cli/include/init_gui.h"

static singleton *get_instance() {
  static singleton instance;
  return &instance;
}

static void game_loop() {
  singleton *s = get_instance();
  WINDOW *field, *next, *score, *level, *high_score, *start_screen;

  field = newwin(FIELD_HEIGHT, FIELD_WIDTH, Y_CENTER_FIELD, X_CENTER_FIELD);
  next = newwin(NEXT_HEIGHT, NEXT_WIDTH, Y_CENTER_NEXT, X_CENTER_NEXT);
  score = newwin(SCORE_HEIGHT, SCORE_WIDTH, Y_CENTER_SCORE, X_CENTER_SCORE);
  level = newwin(LEVEL_HEIGHT, LEVEL_WIDTH, Y_CENTER_LEVEL, X_CENTER_LEVEL);
  high_score = newwin(HIGH_SCORE_HEIGHT, HIGH_SCORE_WIDTH, Y_CENTER_HIGH_SCORE, X_CENTER_HIGH_SCORE);
  start_screen = newwin(START_HEIGHT, START_WIDTH, Y_CENTER_START, X_CENTER_START);

  s->stage = START;
  *(s->action) = -1;

  reset_game_info(s);
  generate_new_figure(s);

  while(!s->game_over) {
    refresh();
    run_state(s);
    get_user_input(s->action); 

    switch (s->stage) {
      case START:
      // draw_start_screen(start_screen);
        break;
      default:
        draw_field(s->game_info->field, field);
        draw_next(s->game_info->next, next);
        draw_score(s->game_info->score, score);
        draw_level(s->game_info->level, level);
        draw_high_score(s->game_info->high_score, high_score);
    }
  }

  delwin(field);
  delwin(next);
  delwin(score);
  delwin(high_score);
  delwin(start_screen);
}

int main() {
  singleton *s = get_instance();

  init_game(s);

  init_screen();
  game_loop();
  endwin();

  destroy_game(s);

  return 0;
}
