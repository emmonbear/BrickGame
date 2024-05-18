/**
 * @file operations.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-05-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef MODULES_OPERATIONS_H
#define MODULES_OPERATIONS_H

#include "../include/checks.h"
#include "../include/common_module.h"

/**
 * @brief Puts the current tetromino on the game field.
 *
 * @details
 *
 * This function iterates over the cells of the current tetromino and, if a cell
 * is occupied, sets the corresponding cell of the game field to the color of
 * the current tetromino. The function does not check if the current tetromino
 * collides with other tetrominoes or the boundaries of the game field.
 *
 * @param[in, out] s A pointer to the singleton object that contains the
 * game's state and information.
 */
void put_figure(singleton *s);

/**
 * @brief Removes the current figure from the game field.
 *
 * This function iterates over the cells of the current figure and, if a cell is
 * occupied, sets the corresponding cell in the game field to 0 (empty).
 *
 * @param[in, out] s A pointer to the singleton object that contains the
 * game's state and information.
 */
void remove_figure(singleton *s);

/**
 * @brief Moves the current figure one unit to the right.
 *
 * @details
 *
 * This function first checks if the figure can be moved to the right using the
 * can_move_right() function. If the function returns true, the function removes
 * the figure from the game field using the remove_figure() function, increments
 * the x-coordinate of the figure by one, and then puts the figure back on the
 * game field using the put_figure() function.
 *
 * @param[in, out] s A pointer to the singleton object that contains the
 * game's state and information.
 */
void move_right(singleton *s);

/**
 * @brief Moves the current figure one unit to the left.
 *
 * @details
 *
 * This function first checks if the figure can be moved to the left using the
 * can_move_left() function. If the function returns true, the function removes
 * the figure from the game field using the remove_figure() function, decrements
 * the x-coordinate of the figure by one, and then puts the figure back on the
 * game field using the put_figure() function.
 *
 * @param[in, out] s A pointer to the singleton object that contains the
 * game's state and information.
 */
void move_left(singleton *s);

/**
 * @brief Moves the current figure down by one unit.
 *
 * @details
 *
 * This function removes the current figure from the game field, increments the
 * vertical coordinate of the figure by one, and then puts the figure back on
 * the game field.
 *
 * @param[in, out] s A pointer to the singleton object that contains the
 game's state and information.

 */
void move_down(singleton *s);

/**
 * @brief Rotates the current figure on the game field.
 *
 * @details
 *
 * This function first copies the current figure's rotation state into the
 * current figure's matrix using a nested loop. Then, it removes the current
 * figure from the game field using the remove_figure() function, and puts the
 * rotated figure back on the game field using the put_figure() function.
 *
 * @param[in, out] s A pointer to the singleton object that contains the
 * game's state and information.
 */
void rotate_figure(singleton *s);

/**
 * @brief Generates a rotated version of the current figure.
 *
 * @details
 *
 * This function first transposes the current figure's matrix using a nested
 * loop and a temporary matrix. Then, it reverses the columns of the transposed
 * matrix using another nested loop and stores the result in the current
 * figure's rotated matrix. Finally, it shifts the resulting shape relative to
 * the top left block
 *
 * @param[in, out] s A pointer to the singleton object that contains the
 * game's state and information.
 */
void get_rotated_figure(singleton *s);

/**
 * @brief Resets the game field to its initial state.
 *
 * @details
 * This function iterates over the cells of the game field using a nested loop
 * and sets each cell to 0 (empty).
 *
 * @param[in, out] s A pointer to the singleton object that contains the
 * game's state and information
 */
void reset_field(singleton *s);

#endif  // MODULES_OPERATIONS_H