/**
 * @file snake_model_test.cc
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-09-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../include/snake_test.h"

namespace s21 {
bool SnakeTest::ArrayIsEmpty(int **array, int rows, int cols) {
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (array[i][j] != 0) {
        return false;
      }
    }
  }

  return true;
}

TEST(SnakeTest, Constructor) {
  SnakeTest model;
  const auto &snake = model.snake();

  EXPECT_TRUE(
      model.ArrayIsEmpty(model.updateCurrentState().field, HEIGHT, WIDTH));
  EXPECT_TRUE(model.ArrayIsEmpty(model.updateCurrentState().next, 4, 4));
  EXPECT_EQ(snake.size(), 3);
  EXPECT_EQ(snake[0], std::make_pair(HEIGHT / 2, WIDTH / 2));
  EXPECT_EQ(snake[1], std::make_pair(HEIGHT / 2, WIDTH / 2 - 1));
  EXPECT_EQ(snake[2], std::make_pair(HEIGHT / 2, WIDTH / 2 - 2));
  EXPECT_FALSE(model.game_over());
}

TEST(SnakeTest, StartStageTerminate) {
  SnakeTest model;
  UserAction_t action = Terminate;
  bool hold = false;
  model.userInput(action, hold);
  EXPECT_EQ(model.stage(), GAME_OVER);
}

TEST(SnakeTest, StartStageSpawn) {
  SnakeTest model;
  UserAction_t action = Start;
  bool hold = false;
  model.userInput(action, hold);
  EXPECT_EQ(model.stage(), SPAWN);
}

TEST(SnakeTest, SpawnStage) {
  SnakeTest model;

  model.set_stage(SPAWN);

  model.userInput(Start, false);
  EXPECT_EQ(model.stage(), SHIFTING);
  EXPECT_EQ(model.updateCurrentState().field[model.snake().front().first]
                                            [model.snake().front().second],
            blue);
  EXPECT_EQ(model.updateCurrentState().field[model.snake().front().first]
                                            [model.snake().front().second],
            blue);
  for (size_t i = 1; i < model.snake().size(); ++i) {
    EXPECT_EQ(model.updateCurrentState()
                  .field[model.snake()[i].first][model.snake()[i].second],
              yellow);
  }
}

}  // namespace s21
