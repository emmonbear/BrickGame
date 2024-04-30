/**
 * @file types.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief Auxiliary header
 * @version 1.0
 * @date 2024-04-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */

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
 * @brief Enumeration of playing field
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

void userInput(UserAction_t action, bool hold);

GameInfo_t updateCurrentState();
