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

extern "C" {
  #include "./brick_game/tetris/include/fsm.h"
  #include "./gui/cli/include/field_gui.h"
  #include "./gui/cli/include/init_gui.h"
  #include "./gui/cli/include/input_gui.h"
}

static Game_t game;

static void draw_game(windows *wins) {
  refresh();
  switch (game.stage) {
    case START:
      draw_start_screen(wins->start.w);
      break;
    case PAUSE:
      draw_pause();
      break;
    case GAME_OVER:
      draw_game_over(wins->game_over.w, game.game_info.score,
                     game.game_info.high_score);
      break;
    default:
      draw_field(game.game_info.field, wins->field.w);
      draw_next(game.game_info.next, wins->next.w);
      draw_score(game.game_info.score, wins->score.w);
      draw_level(game.game_info.level, wins->level.w);
      draw_high_score(game.game_info.high_score, wins->high_score.w);
      draw_info(wins->info.w);
      break;
  }
}

static void game_loop() {
  windows *wins = init_windows();
  game.stage = START;
  game.action = None;
  int lines = LINES;
  int cols = COLS;

  reset_game_info(&game);
  generate_new_figure(&game);

  while (!game.game_over) {
    update_windows(&wins, &lines, &cols);
    run_state(&game);
    get_user_input(&game.action);
    draw_game(wins);
  }

  destroy_windows(&wins);
}

int main() {
  init_game(&game);
  init_screen();
  game_loop();
  endwin();
  destroy_game(&game);

  return 0;
}
