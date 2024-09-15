/**
 * @file view.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-09-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_INCLUDE_GUI_CLI_VIEW_H_
#define SRC_INCLUDE_GUI_CLI_VIEW_H_

#include "../../common/game_info.h"
#include "./types.h"

void init_screen();
void init_windows(Windows_t *windows);
void destroy_windows(Windows_t *windows);
void resize_windows(Windows_t *windows, int *lines, int *cols);
void get_input(UserAction_t *action, bool *hold);
void show_menu(int *choise);

#endif  // SRC_INCLUDE_GUI_CLI_VIEW_H_
