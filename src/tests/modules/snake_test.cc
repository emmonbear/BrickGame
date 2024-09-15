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

TEST(SnakeTest, SpawnStage) {
  SnakeTest model;

  model.set_stage(SPAWN);

  model.userInput(Start, false);
  EXPECT_EQ(model.stage(), SHIFTING);
  EXPECT_EQ(model.updateCurrentState().field[model.snake().front().first]
                                            [model.snake().front().second],
            snake_head);

  for (size_t i = 1; i < model.snake().size(); ++i) {
    EXPECT_EQ(model.updateCurrentState()
                  .field[model.snake()[i].first][model.snake()[i].second],
              snake_body);
  }
}

TEST(SnakeTest, MovingStage) {
  SnakeTest model;

  model.set_stage(MOVING);
  model.userInput(Start, false);

  EXPECT_EQ(model.stage(), SHIFTING);
}

TEST(SnakeTest, PauseStageToShift) {
  SnakeTest model;
  model.set_stage(PAUSE);
  model.userInput(Pause, false);

  EXPECT_EQ(model.stage(), SHIFTING);
}

TEST(SnakeTest, PauseStagToGameOver) {
  SnakeTest model;
  model.set_stage(PAUSE);
  model.userInput(Terminate, false);

  EXPECT_EQ(model.stage(), GAME_OVER);
}

TEST(SnakeTest, GenerateFoodWhenSnakeFillsAllSpaces) {
  SnakeTest model;

  s21::SnakeModel::PointVector full_snake;
  for (int i = 0; i < HEIGHT; ++i) {
    for (int j = 0; j < WIDTH - 1; ++j) {
      full_snake.push_back({i, j});
    }
  }
  model.set_snake(full_snake);

  model.GenerateFood();
}

TEST(SnakeTest, GameOverStageTerminate) {
  SnakeTest model;

  model.set_stage(GAME_OVER);
  model.userInput(Terminate, false);

  EXPECT_TRUE(model.game_over());
}

TEST(SnakeTest, GameOverStageNoTerminate) {
  SnakeTest model;

  model.set_stage(GAME_OVER);
  model.userInput(Pause, false);

  EXPECT_FALSE(model.game_over());
}

TEST(SnakeTest, ShiftingStageHandleDirectionLeft) {
  SnakeTest model;
  model.set_stage(SHIFTING);

  model.userInput(Left, false);

  EXPECT_EQ(model.stage(), SHIFTING);
}

TEST(SnakeTest, ShiftingStageHandleDirectionRight) {
  SnakeTest model;
  model.set_stage(SHIFTING);

  model.userInput(Right, false);

  EXPECT_EQ(model.stage(), SHIFTING);
}

TEST(SnakeTest, ShiftingStageHandleDirectionUp) {
  SnakeTest model;
  model.set_stage(SHIFTING);

  model.userInput(Up, false);

  EXPECT_EQ(model.stage(), SHIFTING);
}

TEST(SnakeTest, ShiftingStageHandleDirectionDown) {
  SnakeTest model;
  model.set_stage(SHIFTING);

  model.userInput(Down, false);

  EXPECT_EQ(model.stage(), SHIFTING);
}

TEST(SnakeTest, ShiftingStageAction) {
  SnakeTest model;
  model.set_stage(SHIFTING);

  model.userInput(Action, false);

  EXPECT_EQ(model.stage(), SHIFTING);
}

TEST(SnakeTest, ShiftingStageDefault) {
  SnakeTest model;
  model.set_stage(SHIFTING);

  model.userInput(Start, false);

  EXPECT_EQ(model.stage(), SHIFTING);
}

TEST(SnakeTest, ShiftingStageTerminate) {
  SnakeTest model;
  model.set_stage(SHIFTING);

  model.userInput(Terminate, false);

  EXPECT_EQ(model.stage(), GAME_OVER);
}

TEST(SnakeTest, ShiftingStagePause) {
  SnakeTest model;
  model.set_stage(SHIFTING);

  model.userInput(Pause, false);

  EXPECT_EQ(model.stage(), PAUSE);
}

TEST(SnakeTest, AttachingStage) {
  SnakeTest model;
  model.set_stage(ATTACHING);

  model.userInput(Start, false);

  EXPECT_EQ(model.stage(), SHIFTING);
}

TEST(SnakeTest, WinStage) {
  SnakeTest model;
  model.set_stage(WIN);

  model.userInput(Start, false);

  EXPECT_EQ(model.stage(), WIN);
}

}  // namespace s21
