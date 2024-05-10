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

/// @brief Amount of tetrominoes
#define NUM_TETROMINOS 7

/// @brief Number of positions
#define NUM_POSITIONS 5

/// @brief The size of the tetromino
#define TETROMINO_SIZE 4

/// @brief Enumeration representing the different types of tetrominoes in the
/// game.
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

/// @brief Figure coordinates
typedef struct {
  int x;  ///< X-coordinate
  int y;  ///< Y-coordinate
} cell_t;

/**
 * @brief Struct representing a tetromino figure in the game.
 *
 * @details
 *
 * This struct represents a tetromino figure, which consists of a type (one of
 * the seven possible tetromino shapes), a color (an integer value representing
 * the color of the blocks that make up the figure), and an array of cells
 * (where each cell is a struct containing the coordinates of a block that makes
 * up the figure).
 */
typedef struct {
  type_t type;  ///< The type of the tetromino figure (one of the seven possible
                ///< shapes)
  int color;    ///< The color of the blocks that make up the figure (an integer
                ///< value)
  cell_t cells[TETROMINO_SIZE *
               TETROMINO_SIZE];  ///< An array of cells representing the blocks
                                 ///< that make up the figure. Each cell is a
                                 ///< struct containing the coordinates of the
                                 ///< block.
} figure_t;

// void generate_new_figure(Figure_t *figure);

#endif  // MODULES_FIGURE_GENERATOR