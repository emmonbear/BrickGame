/**
 * @file input_gui.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-05-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef GUI_INPUT_H
#define GUI_INPUT_H

#include "./common_gui.h"

/**
 * @brief Gets the user input and sets the corresponding action.
 *
 * @details
 * This function takes a pointer to an `enum UserAction_t` variable and sets the
 * variable to the corresponding action based on the user input. The function
 * uses the `getch()` function from the ncurses library to get the user input
 * and a switch statement to set the action.
 *
 * @param[in] action - A pointer to an `enum UserAction_t` variable to be set.
 */
void get_user_input(UserAction_t *action);

#endif  // GUI_INPUT_H