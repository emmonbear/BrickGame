/**
 * @file init_gui.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-05-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef GUI_INIT_H
#define GUI_INIT_H

#include "./common_gui.h"

/**
 * @brief Initializes the screen and sets up the colors for the game.
 *
 * @details
 * This function initializes the screen using the initscr() function from the
 * ncurses library. It also sets up the screen to be in raw mode, to not delay
 * input, to not echo input, and to enable the keypad. The function sets the
 * cursor to be invisible and starts the color system using the start_color()
 * function from the ncurses library. Finally, the function initializes the
 * color pairs using the init_pair() function from the ncurses library.
 */
void init_screen();

/**
 * @brief Initializes the windows for the game.
 *
 * @details
 * This function allocates memory for a `windows` struct using the `malloc()`
 * function from the C standard library. It then initializes each window in the
 * struct using the `init_window()` function. The windows include the game
 * field, the next tetromino, the score, the high score, the level, the start
 * window, the info window, and the game over window.
 *
 * @return windows* A pointer to the initialized `windows` struct.
 */
windows *init_windows();

/**
 * @brief Destroys the windows for the game.
 *
 * @details
 * This function takes a pointer to a pointer to a `windows` struct and destroys
 * each window in the struct using the `delwin()` function from the ncurses
 * library. It then frees the memory allocated for the struct using the `free()`
 * function from the C standard library.
 *
 * @param[in,out] wins - A pointer to a pointer to the `windows` struct to be
 * destroyed.
 */
void destroy_windows(windows **wins);

/**
 * @brief Updates the windows for the game.
 *
 * @details
 *
 * This function takes a pointer to a pointer to a `windows` struct and two
 * pointers to integers representing the current number of lines and columns on
 * the screen. It checks if the current number of lines and columns is different
 * from the number of lines and columns that were used to initialize the
 * windows. If the number of lines and columns has changed, the function
 * destroys the current windows using the `destroy_windows()` function, clears
 * the screen using the `clear()` function from the ncurses library, and
 * initializes new windows using the `init_windows()` function. The function
 * then updates the values of the pointers to the current number of lines and
 * columns.
 *
 * @param[in, out] wins - A pointer to a pointer to the `windows` struct to be
 * updated.
 * @param[in, out] lines - A pointer to an integer representing the current
 * number of lines on the screen.
 * @param[in, out] cols - A pointer to an integer representing the current
 * number of columns on the screen.
 */
void update_windows(windows **wins, int *lines, int *cols);

#endif  // GUI_INIT_H