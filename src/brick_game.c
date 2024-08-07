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
#include "./gui/cli/include/init_gui.h"
#include "./gui/cli/include/input_gui.h"

static void game_loop() {
  Game_t *s = get_instance();
  windows *wins = init_windows();

  s->stage = START;
  (s->action) = -1;

  reset_game_info(s);
  generate_new_figure(s);

  int lines = LINES;
  int cols = COLS;

  while (!s->game_over) {
    update_windows(&wins, &lines, &cols);
    refresh();
    run_state(s);
    get_user_input(&(s->action));

    switch (s->stage) {
      case START:
        draw_start_screen(wins->start.w);
        break;
      case PAUSE:
        draw_pause();
        break;
      case GAME_OVER:
        draw_game_over(wins->game_over.w, s->game_info.score,
                       s->game_info.high_score);
        break;
      default:
        draw_field(s->game_info.field, wins->field.w);
        draw_next(s->game_info.next, wins->next.w);
        draw_score(s->game_info.score, wins->score.w);
        draw_level(s->game_info.level, wins->level.w);
        draw_high_score(s->game_info.high_score, wins->high_score.w);
        draw_info(wins->info.w);
        break;
    }
  }
  destroy_windows(&wins);
}

int main() {
  Game_t *s = get_instance();

  init_game(s);
  init_screen();
  game_loop();
  endwin();

  destroy_game(s);

  return 0;
}
