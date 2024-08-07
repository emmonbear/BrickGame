/**
 * @file fsm.c
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-05-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../include/fsm.h"

#include <time.h>

static int get_current_time() { return (int)(clock() * 1000 / CLOCKS_PER_SEC); }

/**
 * @brief Runs the current state of the game's state machine.
 *
 * @details
 *
 * This function uses an array of function pointers to call the appropriate
 * function for the current state of the game. The function takes a singleton
 * structure as an argument and invokes the function corresponding to the
 * current state of the game.
 *
 * @param[in,out] s The singleton structure containing the game's state and
 * data.
 */
void run_state(singleton *s) {
  static func_ptr state_funcs[NUM_STAGES] = {
      start_stage, spawn_stage,     shifting_stage, moving_stage,
      pause_stage, attaching_stage, game_over_stage};

  state_funcs[s->stage](s);
}
/**
 * @brief Handles the start state of the game's state machine.
 *
 * @details
 *
 * This function initializes the game's data structures and sets the game's
 * state to the spawn state. It is called by the run_state function when the
 * game's state machine is in the start state.
 *
 * @param[in,out] s The singleton structure containing the game's state and
 * data.
 */
void start_stage(singleton *s) {
  switch (*(s->action)) {
    case Start:
      s->stage = SPAWN;
      break;
    case Terminate:
      s->stage = GAME_OVER;
      break;
    default:
      break;
  }
}

/**
 * @brief Handles the game over state of the game's state machine.
 *
 * @details
 *
 * This function is called by the run_state function when the game's state
 * machine is in the game over state. In this state, the game is ended and
 * the player is shown the final score and game statistics.
 *
 * @param[in,out] s The singleton structure containing the game's state and
 * data.
 */
void game_over_stage(singleton *s) {
  write_high_score(s);

  switch (*(s->action)) {
    case Start:
      reset_field(s);
      reset_game_info(s);
      generate_new_figure(s);
      s->stage = SPAWN;
      s->game_over = 0;
      break;
    case Terminate:
      s->game_over = 1;
      break;
    default:
      break;
  }
}

/**
 * @brief Handles the spawn state of the game's state machine.
 *
 * @details
 *
 * This function creates a new block and selects the next block to be spawned.
 * It is called by the run_state function when the game's state machine is in
 * the spawn state.
 *
 * @param[in,out] s The singleton structure containing the game's state and
 * data.
 */
void spawn_stage(singleton *s) {
  copy_next_to_current(s);
  put_figure(s);
  generate_new_figure(s);
  s->stage = SHIFTING;
}

/**
 * @brief Handles the shifting state of the game's state machine.
 *
 * @details
 *
 * This function moves the current block down one level after the timer expires.
 * It is called by the run_state function when the game's state machine is in
 * the shifting state.
 *
 * @param[in,out] s The singleton structure containing the game's state and
 * data.
 */
void shifting_stage(singleton *s) {
  int current_time = get_current_time();
  int wait_time = 1000 - (s->game_info->level * 100);

  if (wait_time < 100) {
    wait_time = 100;
  }

  if (can_move_down(s)) {
    if (current_time - s->timer >= wait_time) {
      move_down(s);
      s->timer = current_time;
    }
  } else {
    if ((current_time - s->timer >= wait_time)) {
      s->stage = ATTACHING;
    }
  }

  switch (*(s->action)) {
    case Left:
    case Right:
    case Down:
    case Action:
      moving_stage(s);
      break;
    case Terminate:
      s->stage = GAME_OVER;
      break;
    case Pause:
      s->stage = PAUSE;
      break;
    default:
      break;
  }
}

/**
 * @brief Handles the moving state of the game's state machine.
 *
 * @details
 *
 * This function processes user input to rotate blocks and move blocks
 * horizontally. It is called by the run_state function when the game's state
 * machine is in the moving state.
 *
 * @param[in,out] s The singleton structure containing the game's state and
 * data.
 */
void moving_stage(singleton *s) {
  s->stage = SHIFTING;

  switch (*(s->action)) {
    case Left:
      move_left(s);
      break;

    case Right:
      move_right(s);
      break;

    case Down:
      while (can_move_down(s)) {
        move_down(s);
      }
      break;
    case Action:
      get_rotated_figure(s);

      if (can_rotate(s)) {
        rotate_figure(s);
      }

      break;
    default:
      break;
  }
}

/**
 * @brief Handles the pause state of the game's state machine.
 *
 * @details
 *
 * This function pauses the game and waits for the user to resume or quit.
 * It is called by the run_state function when the game's state machine is in
 * the pause state.
 *
 * @param[in,out] s The singleton structure containing the game's state and
 * data.
 */
void pause_stage(singleton *s) {
  switch (*(s->action)) {
    case Pause:
      s->stage = SHIFTING;
      break;
    case Terminate:
      s->stage = GAME_OVER;
      break;
    default:
      break;
  }
}

/**
 * @brief Handles the attaching state of the game's state machine.
 *
 * @details
 *
 * This function is called by the run_state function when the game's state
 * machine is in the attaching state. In this state, the current block is
 * attached to the already fallen blocks or the ground. If a filled line is
 * formed, it is destroyed and the remaining blocks are shifted down. If a
 * block is stopped in the topmost row, the game goes to the game over state.
 *
 * @param[in,out] s The singleton structure containing the game's state and
 * data.
 */
void attaching_stage(singleton *s) {
  check_full_lines(s);
  s->figure.x = 3;
  s->figure.y = 0;

  if (can_put_new_line(s)) {
    s->stage = SPAWN;
  } else {
    s->stage = GAME_OVER;
  }
}

singleton *get_instance() {
  static singleton instance;
  return &instance;
}