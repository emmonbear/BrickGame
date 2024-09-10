/**
 * @file game_info.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-09-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_INCLUDE_COMMON_GAME_INFO_H_
#define SRC_INCLUDE_COMMON_GAME_INFO_H_

/// @brief Number of lines on Field
#define HEIGHT 20

/// @brief Number of columns on Field
#define WIDTH 10

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action,
  None,
} UserAction_t;

typedef enum {
  START,
  SPAWN,
  SHIFTING,
  MOVING,
  PAUSE,
  ATTACHING,
  GAME_OVER,
} stage_t;

#endif  // SRC_INCLUDE_COMMON_GAME_INFO_H_
