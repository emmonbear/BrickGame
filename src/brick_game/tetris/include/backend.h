/**
 * @file backend.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-05-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef MODULES_BACKEND_H
#define MODULES_BACKEND_H

#include <stdbool.h>

/// @brief number of lines on Field
#define F_ROWS 20

/// @brief number of columns on Field
#define F_COLS 10

/// @brief Tetromino size
#define T_SIZE 4

/// @brief Cell size
#define C_SIZE 2

/// @brief Size of border
#define BOARD_SIZE 2

/// @brief Emergency program termination in case of memory allocation error
#define MEM_ALLOC_ERROR                         \
  fprintf(stderr, "Memory allocation error\n"); \
  exit(1);

/// @brief Count of tetrominos
#define NUM_FIGURES 7

/// @brief Number of possible positions for tetrominos
#define NUM_POSITIONS 5

/// @brief Enumeration of user actions
typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

/// @brief
typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef struct {
  int y;
  int x;
} location_t;

typedef struct {
  int type;
  int orientation;
  location_t loc;
} tetromino_t;


/// @brief
typedef struct {
  GameInfo_t *game_info;
  tetromino_t tet;
} singleton;



typedef enum {
  TET_I,
  TET_Z,
  TET_S,
  TET_T,
  TET_L,
  TET_J,
  TET_O,
} tet_type;

int get_random_figure();
void generate_new_figure();
singleton *get_instance();
void init_game();
void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();
void destroy_game();
void init_game();

#endif  // MODULES_BACKEND_H