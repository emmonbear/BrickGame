/**
 * @file enums.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-08-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_COMMON_INCLUDE_ENUMS_H_
#define SRC_COMMON_INCLUDE_ENUMS_H_

/**
 * @brief Enumeration of user actions
 *
 * @details
 *
 * This enumeration represents all possible actions that a user can take while
 * playing the game. These actions include starting the game, pausing the game,
 * terminating the game, moving the current block left, moving the current block
 * right, rotating the current block clockwise, moving the current block down,
 * and performing an "action" (such as triggering a hard drop or activating a
 * special ability).
 */
typedef enum {
  Start,      ///< Start the game
  Pause,      ///< Pause the game
  Terminate,  ///< Terminate the game
  Left,       ///< Move the current tetromino to the left
  Right,      ///< Move the current tetromino to the right
  Up,         ///< is not used in this project
  Down,       ///< Move the current tetromino down
  Action,     ///< rotate the current tetromino
  None        ///< No action
} UserAction_t;

#endif  // SRC_COMMON_INCLUDE_ENUMS_H_
