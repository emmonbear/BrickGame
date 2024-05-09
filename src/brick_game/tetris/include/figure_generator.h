/**
 * @file figure_generator.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-05-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef MODULES_FIGURE_GENERATOR
#define MODULES_FIGURE_GENERATOR

/// @brief Enumeration representing the different types of tetrominoes in the
/// game
typedef enum {
  TET_I,  ///< The "I" shaped tetromino, consisting of four blocks in a straight
          ///< line.
  TET_Z,  ///< The "Z" shaped tetromino, consisting of three blocks in a zigzag
          ///< pattern and one block on the side.
  TET_S,  ///< The "S" shaped tetromino, consisting of three blocks in a zigzag
          ///< pattern and one block on the opposite side.
  TET_T,  ///< The "T" shaped tetromino, consisting of three blocks in a
          ///< straight line and one block perpendicular to the middle block.
  TET_L,  ///< The "L" shaped tetromino, consisting of three blocks in a
          ///< straight line and one block perpendicular to the end block.
  TET_J,  ///< The "J" shaped tetromino, consisting of three blocks in a
          ///< straight line and one block perpendicular to the opposite end
          ///< block.
  TET_O,  ///< The "O" shaped tetromino, consisting of four blocks arranged in a
          ///< 2x2 square.
} type_t;

/// @brief Struct representing a tetromino figure in the game
typedef struct {
  type_t current_type;  ///< The current type of the figure (one of the seven
                        ///< types defined in the `type_t` enumeration).
  type_t next_type;     ///< The type of the next figure that will appear
                        /// in the game.
  int rotation;  ///< The current rotation of the figure (an integer value
                 ///< between 0 and 3, representing the four possible rotations
                 ///< of the figure).
  int x;  ///< The x-coordinate of the top-left corner of the figure on the game
          ///< board.
  int y;  ///< The y-coordinate of the top-left corner of the figure on the game
          ///< board.
} Figure_t;

#endif  // MODULES_FIGURE_GENERATOR