/**
 * @file init_game.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief 
 * @version 1.0
 * @date 2024-05-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef MODULES_INIT_GAME_H
#define MODULES_INIT_GAME_H

#include "./fsm.h"

GameInfo_t *init_game(void);
void destrust_game(GameInfo_t *game_info);

#endif // MODULES_INIT_GAME_H