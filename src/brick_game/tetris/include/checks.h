/**
 * @file checks.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-05-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef MODULES_CHECKS_H
#define MODULES_CHECKS_H

#include <stdbool.h>

#include "./common_module.h"

/**
 * @brief Checks if the current tetromino can be moved down.
 *
 * @details
 *
 * This function iterates over the cells of the current tetromino using a nested
 * loop and checks if the cell is occupied. If the cell is occupied, the
 * function checks if the cell below it is also occupied and outside of the
 * current tetromino. If it is, the function sets the res variable to false and
 * returns it. If the function has checked all the cells and the res variable is
 * still true, it returns true.
 *
 * @param[in, out] s A pointer to the singleton object that contains the game's
 * state and information.
 * @return bool - true if the current tetromino can be moved down, false
 * otherwise.
 */
bool can_move_down(singleton *s);

/**
 * @brief Checks if the current tetromino can be moved left.
 *
 * @details
 *
 * This function iterates over the cells of the current tetromino using a nested
 * loop and checks if the cell is occupied. If the cell is occupied, the
 * function checks if the cell to the left of it is also occupied and outside of
 * the current tetromino. If it is, the function sets the res variable to false
 * and returns it. If the function has checked all the cells and the res
 * variable is still true, it returns true.
 *
 * @param[in, out] s A pointer to the singleton object that contains the game's
 * state and information.
 * @return bool - true if the current tetromino can be moved left, false
 * otherwise.
 */
bool can_move_left(singleton *s);

/**
 * @brief Checks if the current tetromino can be moved right.
 *
 * @details
 *
 * This function iterates over the cells of the current tetromino using a nested
 * loop and checks if the cell is occupied. If the cell is occupied, the
 * function checks if the cell to the right of it is also occupied and outside
 * of the current tetromino. If it is, the function sets the res variable to
 * false and returns it. If the function has checked all the cells and the res
 * variable is still true, it returns true.
 *
 * @param[in, out] s A pointer to the singleton object that contains the game's
 * state and information.
 * @return bool - true if the current tetromino can be moved right, false
 * otherwise.
 */
bool can_move_right(singleton *s);

/**
 * @brief Checks if the current tetromino can be rotated.
 *
 * @details
 *
 * This function first removes the current tetromino from the game field using
 * the remove_figure() function. Then, it iterates over the cells of the rotated
 * tetromino using a nested loop and checks if the cell is occupied. If the cell
 * is occupied, the function checks if the cell's new position after rotation is
 * outside of the game field or is occupied by another tetromino. If it is, the
 * function sets the res variable to false and returns it. If the function has
 * checked all the cells and the res variable is still true, it returns true.
 *
 * @param[in, out] s A pointer to the singleton object that contains the game's
 * state and information.
 * @return bool - true if the current tetromino can be rotated, false otherwise.
 */
bool can_rotate(singleton *s);

/**
 * @brief Checks if a cell is inside the current tetromino.
 *
 * @details
 *
 * This function iterates over the cells of the current tetromino using a nested
 * loop and checks if the cell is occupied. If the cell is occupied, the
 * function checks if the cell's position is equal to the specified position (y,
 * x). If it is, the function sets the res variable to true and returns it. If
 * the function has checked all the cells and the res variable is still false,
 * it returns false.
 *
 * @param[in, out] s A pointer to the singleton object that contains the game's
 * state and information.
 * @param[in] y The y-coordinate of the cell to check.
 * @param[in] x The x-coordinate of the cell to check.
 * @return bool - true if the cell is inside the current tetromino, false
 * otherwise.
 */
bool is_inside_figure(singleton *s, int y, int x);

/**
 * @brief Checks for full lines in the game field and updates the score and
 * level.
 *
 * @details
 *
 * This function iterates over the rows of the game field using a nested loop
 * and checks if the row is filled with tetrominos. If the row is filled, the
 * function shifts all the rows above it down by one row and increments the
 * full_lines variable. If the function has checked all the rows and the
 * full_lines variable is greater than 0, it updates the score and level using
 * the get_score() and update_level() functions.
 *
 * @param[in, out] s A pointer to the singleton object that contains the game's
 * state and information.
 */
void check_full_lines(singleton *s);

/**
 * @brief Checks if a new tetromino can be placed on the game field.
 *
 * @details
 * This function iterates over the cells of the next tetromino using a nested
 * loop and checks if the cell is occupied. If the cell is occupied, the
 * function checks if the cell's position on the game field is already occupied
 * by another tetromino. If it is, the function sets the res variable to false
 * and returns it. If the function has checked all the cells and the res
 * variable is still true, it returns true.
 *
 * @param[in, out] s - A pointer to the singleton object that contains the
 * game's state and information.
 * @return bool - true if a new tetromino can be placed on the game field, false
 * otherwise.
 */
bool can_put_new_line(singleton *s);

#endif  // MODULES_CHECKS_H