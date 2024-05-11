/**
 * @file field_gui.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-05-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef GUI_FIELD_H
#define GUI_FIELD_H

#include "./common_gui.h"

void draw_field(int **field, WINDOW *w);
void draw_next(int **next, WINDOW *w);

#endif  // GUI_FIELD_H