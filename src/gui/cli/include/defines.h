/**
 * @file defines.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief 
 * @version 1.0
 * @date 2024-05-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef GUI_DEFINES_H
#define GUI_DEFINES_H

#include "./common.h"

/**
 * @brief NCURSES initialization
 * 
 * @param initscr()   initializes the terminal in curses mode
 * @param cbreak()    disable line buffering
 * @param noecho()    switches off echoing
 * @param keypad()    enables thr reading of function keys
 * @param timeout(0)  disable blocking from getch
 * @param curs_set(0) set the cursor to invisible
 */
#define INIT_SCR \
                  initscr();\
                  cbreak();\
                  noecho();\
                  keypad(stdscr, TRUE);\
                  timeout(0);\
                  curs_set(0);

#endif // GUI_DEFINES_H