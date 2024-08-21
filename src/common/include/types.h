/**
 * @file types.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-08-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_COMMON_INCLUDE_TYPES_H_
#define SRC_COMMON_INCLUDE_TYPES_H_

typedef struct {
  int **field;  ///< 2D array representing the game field, where each element
                ///< corresponds to a cell on the field. The value of an element
                ///< is either 0 (empty cell) or a positive integer (cell
                ///< occupied by a block, with the value indicating the color of
                ///< the block).
  int **next;   ///< 2D array representing the next block to be spawned.
  int score;    ///< The current score of the player.
  int high_score;  ///< The highest score achieved by any player.
  int level;  ///< The current level of the game, which determines the speed at
              ///< which blocks fall.
  int speed;  ///< The speed at which blocks fall, measured in milliseconds
              ///< between each downward movement.
  int pause;  ///< A flag indicating whether the game is currently paused (1) or
              ///< not (0).
} GameInfo_t;

#endif  // SRC_COMMON_INCLUDE_TYPES_H_
