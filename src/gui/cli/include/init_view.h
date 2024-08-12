/**
 * @file init_gui.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief Initialize view header
 * @version 1.0
 * @date 2024-05-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef GUI_INIT_H
#define GUI_INIT_H

#include "./view.h"

void init_screen();
void init_view(View_t *view);
void destroy_view(View_t *view);

#endif  // GUI_INIT_H
