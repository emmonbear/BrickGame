/**
 * @file backend.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief 
 * @version 1.0
 * @date 2024-05-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef MODULES_BACKEND_H
#define MODULES_BACKEND_H

#include <stdbool.h>

/**
 * @brief Enumeration of user actions
 * 
 */
typedef enum {
    Start,
    Pause,
    Terminate,
    Left,
    Right,
    Up,
    Down,
    Action
} UserAction_t;

/**
 * @brief 
 * 
 */
typedef struct {
    int **field;
    int **next;
    int score;
    int high_score;
    int level;
    int speed;
    int pause;
} GameInfo_t;

/**
 * @brief 
 * 
 */
typedef struct {
  GameInfo_t game_info;
} singleton;

/**
 * @brief Get the instance object
 * 
 * @return singleton* 
 */
singleton *get_instance() {
  static singleton instance;
  return &instance;
}

void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();

#endif // MODULES_BACKEND_H