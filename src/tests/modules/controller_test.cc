/**
 * @file controller_test.cc
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief Controller tests
 * @version 1.0
 * @date 2024-08-12
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../main_test.h"

class ControllerTest : public ::testing::Test {
 protected:
  void SetUp() override {
    controller = init_controller();
    reset_game_info(&controller->model);
  }

  void TearDown() override { destroy_controller(controller); }

  Controller_t *controller;
};

TEST_F(ControllerTest, InitialSetup) {
  EXPECT_EQ(controller->action, None);
  EXPECT_EQ(controller->stage, Start);
  EXPECT_EQ(controller->timer, 0);
  EXPECT_EQ(controller->game_over, false);
}

TEST_F(ControllerTest, StartStage) {
  controller->stage = START;
  controller->action = Start;
  run_state(controller);

  EXPECT_EQ(controller->stage, SPAWN);
}

TEST_F(ControllerTest, StartStage1) {
  controller->stage = START;
  controller->action = Terminate;
  run_state(controller);

  EXPECT_EQ(controller->stage, GAME_OVER);
}

TEST_F(ControllerTest, StartStage2) {
  controller->stage = START;
  controller->action = Pause;
  run_state(controller);

  EXPECT_EQ(controller->stage, START);
}

TEST_F(ControllerTest, SpawnStage) {
  controller->stage = START;
  controller->action = Start;
  run_state(controller);

  EXPECT_EQ(controller->stage, SPAWN);

  run_state(controller);
}

TEST_F(ControllerTest, MoveLeft) {
  controller->stage = MOVING;
  controller->action = Left;
  run_state(controller);
  EXPECT_EQ(controller->stage, SHIFTING);
}

TEST_F(ControllerTest, MoveRight) {
  controller->stage = MOVING;
  controller->action = Right;
  run_state(controller);
  EXPECT_EQ(controller->stage, SHIFTING);
}

TEST_F(ControllerTest, MoveDown) {
  controller->stage = MOVING;
  controller->action = Down;
  run_state(controller);
  EXPECT_EQ(controller->stage, SHIFTING);
}

TEST_F(ControllerTest, Action) {
  controller->stage = MOVING;
  controller->action = Action;
  run_state(controller);
  EXPECT_EQ(controller->stage, SHIFTING);
}

TEST_F(ControllerTest, MovingStageDefault) {
  controller->stage = MOVING;
  controller->action = Pause;
  run_state(controller);
  EXPECT_EQ(controller->stage, SHIFTING);
}

TEST_F(ControllerTest, ShiftingStage) {
  controller->stage = MOVING;
  controller->action = Down;
  run_state(controller);
  EXPECT_EQ(controller->stage, SHIFTING);
  run_state(controller);
}

TEST_F(ControllerTest, ShiftingStage1) {
  controller->model.figure.next_type = TET_L;
  generate_new_figure(&controller->model);
  copy_next_to_current(&controller->model);

  for (int i = 0; i < HEIGHT; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
      controller->model.game_info.field[i][j] = 1;
    }
  }
  controller->stage = SHIFTING;
  run_state(controller);
  EXPECT_EQ(controller->stage, SHIFTING);
}

TEST_F(ControllerTest, ShiftingStage2) {
  controller->model.figure.next_type = TET_L;
  generate_new_figure(&controller->model);
  copy_next_to_current(&controller->model);

  for (int i = 0; i < HEIGHT; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
      controller->model.game_info.field[i][j] = 1;
    }
  }

  controller->stage = SHIFTING;
  controller->model.game_info.level = 10;
  controller->timer = -98;
  run_state(controller);
  EXPECT_EQ(controller->stage, ATTACHING);
}

TEST_F(ControllerTest, ShiftingStage3) {
  controller->action = Right;
  controller->stage = SHIFTING;
  run_state(controller);
}

TEST_F(ControllerTest, ShiftingStage4) {
  controller->action = Terminate;
  controller->stage = SHIFTING;
  run_state(controller);
  EXPECT_EQ(controller->stage, GAME_OVER);
}

TEST_F(ControllerTest, ShiftingStage5) {
  controller->action = Pause;
  controller->stage = SHIFTING;
  run_state(controller);
  EXPECT_EQ(controller->stage, PAUSE);
}

TEST_F(ControllerTest, PauseStage) {
  controller->stage = PAUSE;
  controller->action = Pause;
  run_state(controller);
  EXPECT_EQ(controller->stage, SHIFTING);
}

TEST_F(ControllerTest, PauseStage1) {
  controller->stage = PAUSE;
  controller->action = Terminate;
  run_state(controller);
  EXPECT_EQ(controller->stage, GAME_OVER);
}

TEST_F(ControllerTest, PauseStage2) {
  controller->stage = PAUSE;
  controller->action = Start;
  run_state(controller);
  EXPECT_EQ(controller->stage, PAUSE);
}

TEST_F(ControllerTest, GameOverStage) {
  controller->stage = GAME_OVER;
  controller->action = Start;
  run_state(controller);
  EXPECT_EQ(controller->stage, SPAWN);
}

TEST_F(ControllerTest, GameOverStage1) {
  controller->stage = GAME_OVER;
  controller->action = Terminate;
  run_state(controller);
  EXPECT_EQ(controller->game_over, true);
}

TEST_F(ControllerTest, GameOverStage2) {
  controller->stage = GAME_OVER;
  controller->action = Pause;
  run_state(controller);
  EXPECT_EQ(controller->stage, GAME_OVER);
}

TEST_F(ControllerTest, AttachingStage) {
  controller->stage = ATTACHING;
  run_state(controller);
  EXPECT_EQ(controller->stage, SPAWN);
}

TEST_F(ControllerTest, AttachingStage1) {
  for (size_t i = 0; i < TETROMINO_SIZE; i++) {
    for (size_t j = 0; j < TETROMINO_SIZE; j++) {
      controller->model.game_info.next[i][j] = 1;
      controller->model.game_info.field[i][j] = 1;
    }
  }

  controller->model.figure.x = 0;
  controller->model.figure.y = 0;
  controller->stage = ATTACHING;

  run_state(controller);

  EXPECT_EQ(controller->stage, GAME_OVER);
}
