/**
 * @file init_gui.c
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-05-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../include/view.h"

#include <stdlib.h>

#include "../include/field_renderer.h"

static void init_window(window_t *w, int height, int width, int y, int x);
static void get_user_input(Controller_t *controller);
static void destroy_window(window_t *window);

/**
 * @brief Initializes the terminal screen for the game.
 *
 * @details This function sets up the terminal for the game by initializing
 * ncurses mode, configuring input settings, and setting up color pairs for
 * different game elements. It ensures that the terminal is in raw mode,
 * disables echoing of typed characters, and makes the cursor invisible.
 */
void init_screen() {
  initscr();              // Initialize ncurses mode
  raw();                  // Disable line buffering
  nodelay(stdscr, TRUE);  // Set non-blocking input
  noecho();               // Disable echoing of typed characters
  keypad(stdscr, TRUE);   // Enable special keys to be read
  curs_set(0);            // Hide the cursor
  start_color();          // Enable color functionality

  init_pair(0, COLOR_WHITE, COLOR_BLACK);
  init_pair(1, COLOR_BLUE, COLOR_BLACK);
  init_pair(2, COLOR_CYAN, COLOR_BLACK);
  init_pair(3, COLOR_GREEN, COLOR_BLACK);
  init_pair(4, COLOR_RED, COLOR_BLACK);
  init_pair(5, COLOR_YELLOW, COLOR_BLACK);
  init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(7, COLOR_WHITE, COLOR_BLACK);
}

static void init_window(window_t *w, int height, int width, int y, int x) {
  w->height = height;
  w->width = width;
  w->y = y;
  w->x = x;
  w->w = newwin(w->height, w->width, w->y, w->x);
}

/**
 * @brief Initializes the view components for the game.
 *
 * @details This function sets up the windows for different game elements
 * (field, next, score, high score, level, start screen, info, and game over) by
 * calling `init_window` for each component with the appropriate dimensions and
 * positions.
 *
 * @param view A pointer to the View_t structure that contains all the windows
 * to be initialized.
 */
void init_windows(Windows_t *windows) {
  if (!windows) {
    MEM_ALLOC_ERROR;
  }
  init_window(&windows->field, FIELD_HEIGHT, FIELD_WIDTH, Y_CENTER_FIELD,
              X_CENTER_FIELD);
  init_window(&windows->next, NEXT_HEIGHT, NEXT_WIDTH, Y_CENTER_NEXT,
              X_CENTER_NEXT);
  init_window(&windows->score, SCORE_HEIGHT, SCORE_WIDTH, Y_CENTER_SCORE,
              X_CENTER_SCORE);
  init_window(&windows->high_score, HIGH_SCORE_HEIGHT, HIGH_SCORE_WIDTH,
              Y_CENTER_HIGH_SCORE, X_CENTER_HIGH_SCORE);
  init_window(&windows->level, LEVEL_HEIGHT, LEVEL_WIDTH, Y_CENTER_LEVEL,
              X_CENTER_LEVEL);
  init_window(&windows->start, START_HEIGHT, START_WIDTH, Y_CENTER_START,
              X_CENTER_START);
  init_window(&windows->info, INFO_HEIGHT, INFO_WIDTH, Y_CENTER_INFO,
              X_CENTER_INFO);
  init_window(&windows->game_over, START_HEIGHT, START_WIDTH, Y_CENTER_START,
              X_CENTER_START);
}

View_t *init_view() {
  View_t *view = (View_t *)malloc(sizeof(View_t));

  if (!view) {
    MEM_ALLOC_ERROR;
  }

  init_windows(&view->windows);
  init_controller(&view->controller);

  return view;
}

static void destroy_window(window_t *window) {
  if (window && window->w) {
    delwin(window->w);
    window->w = NULL;
  }
}

static void destroy_windows(Windows_t *windows) {
  if (windows) {
    destroy_window(&windows->field);
    destroy_window(&windows->next);
    destroy_window(&windows->score);
    destroy_window(&windows->high_score);
    destroy_window(&windows->start);
    destroy_window(&windows->game_over);
    destroy_window(&windows->info);
    destroy_window(&windows->level);
  }
}

/**
 * @brief Destroys the view components of the game.
 *
 * @details This function deletes all the windows created for the different game
 * elements (field, next, score, high score, level, start screen, info, and game
 * over) by calling `delwin` for each window.
 *
 * @param view A pointer to the View_t structure containing the windows to be
 * destroyed.
 */
void destroy_view(View_t *view) {
  if (view) {
    destroy_windows(&view->windows);
    destroy_controller(&view->controller);
    free(view);
  }
}

static void get_user_input(Controller_t *controller) {
  switch (getch()) {
    case KEY_LEFT:
      controller->model.action = Left;
      break;
    case KEY_RIGHT:
      controller->model.action = Right;
      break;
    case KEY_DOWN:
      controller->model.action = Down;
      break;
    case ' ':
      controller->model.action = Action;
      break;
    case '\n':
      controller->model.action = Start;
      break;
    case 'p':
    case 'P':
      controller->model.action = Pause;
      break;
    case 'q':
    case 'Q':
      controller->model.action = Terminate;
      break;
    default:
      controller->model.action = None;
      break;
  }
}

/**
 * @brief Resizes the game windows if the terminal size has changed.
 *
 * @details This function checks if the dimensions of the terminal have changed.
 * If they have, it destroys the existing view windows, clears the screen, and
 * reinitializes the view with the new terminal size.
 *
 * @param view Pointer to the view structure containing game windows.
 * @param lines Pointer to the variable holding the current number of terminal
 * lines.
 * @param cols Pointer to the variable holding the current number of terminal
 * columns.
 */
void resize_windows(Windows_t *windows, int *lines, int *cols) {
  if (*lines != LINES || *cols != COLS) {
    destroy_windows(windows);
    clear();
    init_windows(windows);
    *lines = LINES;
    *cols = COLS;
  }
}

/**
 * @brief Runs the main game loop, handling game state updates and rendering.
 *
 * @details This function initializes the game state by resetting game
 * information, generating a new tetromino figure, and then enters a loop that
 * continues until the game is over. Within the loop, it performs the following
 * actions:
 * - Adjusts the window size if needed.
 * - Executes the function associated with the current game stage.
 * - Captures user input to determine the next action.
 * - Renders the current game state to the view.
 *
 * The loop will break when the `game_over` flag in the `Controller_t` structure
 * is set to true.
 *
 * @param controller A pointer to the `Controller_t` structure that manages the
 * game's state, view, and user actions.
 */
void game_loop(View_t *view) {
  int lines = LINES;
  int cols = COLS;

  while (!view->controller.model.game_over) {
    resize_windows(&view->windows, &lines, &cols);
    run_state(&view->controller.model);
    get_user_input(&view->controller);
    update(view);
  }
}
