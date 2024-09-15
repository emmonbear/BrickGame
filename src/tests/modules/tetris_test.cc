/**
 * @file tetris_test.cc
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-09-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../include/main_test.h"
extern "C" {
#include "../../include/tetris/model.h"
}

namespace s21 {
class TetrisModelTest : public ::testing::Test {
 protected:
  GameInfo_t* game_info_;
  Model_t* model_;

  void SetUp() override {
    game_info_ = new GameInfo_t;
    model_ = new Model_t;

    init_model();

    *game_info_ = updateCurrentState();
    *model_ = get_model();
  }

  void TearDown() override {
    destroy_model();

    delete game_info_;
    delete model_;
  }
};

TEST_F(TetrisModelTest, InitialState) {
  EXPECT_EQ(game_info_->score, 0);
  EXPECT_EQ(game_info_->level, 1);
  EXPECT_EQ(model_->stage, SPAWN);
  EXPECT_FALSE(model_->game_over);
}

TEST_F(TetrisModelTest, SpawnStageTest) {
  set_model_stage(SPAWN);
  userInput(Left, false);
  *model_ = get_model();
  EXPECT_EQ(model_->stage, SHIFTING);
}

TEST_F(TetrisModelTest, MovingStageTest) {
  set_model_stage(MOVING);
  userInput(Left, false);
  *model_ = get_model();

  EXPECT_EQ(model_->stage, SHIFTING);
}

TEST_F(TetrisModelTest, MovingStageRightTest) {
  set_model_stage(MOVING);
  userInput(Right, false);
  *model_ = get_model();

  EXPECT_EQ(model_->stage, SHIFTING);
}

TEST_F(TetrisModelTest, MovingStageDownTest) {
  set_model_stage(MOVING);
  userInput(Down, false);
  *model_ = get_model();

  EXPECT_EQ(model_->stage, SHIFTING);
}

TEST_F(TetrisModelTest, MovingStageDefaultTest) {
  set_model_stage(MOVING);
  userInput(Start, false);
  *model_ = get_model();

  EXPECT_EQ(model_->stage, SHIFTING);
}

TEST_F(TetrisModelTest, WinStageTest) {
  set_model_stage(WIN);
  userInput(Start, false);
  *model_ = get_model();

  EXPECT_EQ(model_->stage, WIN);
}

TEST_F(TetrisModelTest, MovingStageActionTest) {
  set_model_stage(MOVING);
  userInput(Action, false);
  *model_ = get_model();

  EXPECT_EQ(model_->stage, SHIFTING);
}

TEST_F(TetrisModelTest, ShiftingStageTest) {
  set_model_stage(SHIFTING);
  userInput(Left, false);
  *model_ = get_model();

  EXPECT_EQ(model_->stage, SHIFTING);
}

TEST_F(TetrisModelTest, ShiftingStageTerminateTest) {
  set_model_stage(SHIFTING);
  userInput(Terminate, false);
  *model_ = get_model();

  EXPECT_EQ(model_->stage, GAME_OVER);
}

TEST_F(TetrisModelTest, ShiftingStagePauseTest) {
  set_model_stage(SHIFTING);
  userInput(Pause, false);
  *model_ = get_model();

  EXPECT_EQ(model_->stage, PAUSE);
}

TEST_F(TetrisModelTest, PauseStageTest) {
  set_model_stage(PAUSE);
  userInput(Pause, false);
  *model_ = get_model();

  EXPECT_EQ(model_->stage, SHIFTING);
}

TEST_F(TetrisModelTest, PauseStageTerminateTest) {
  set_model_stage(PAUSE);
  userInput(Terminate, false);
  *model_ = get_model();

  EXPECT_EQ(model_->stage, GAME_OVER);
}

TEST_F(TetrisModelTest, AttachingStageTest) {
  set_model_stage(ATTACHING);
  userInput(Left, false);
  *model_ = get_model();

  EXPECT_EQ(model_->stage, SPAWN);
}

TEST_F(TetrisModelTest, GameOverStageTest) {
  set_model_stage(GAME_OVER);
  userInput(Start, false);
  *model_ = get_model();

  EXPECT_EQ(model_->stage, SPAWN);
  EXPECT_FALSE(model_->game_over);
}

TEST_F(TetrisModelTest, GameOverStageTerminateTest) {
  set_model_stage(GAME_OVER);
  userInput(Terminate, false);
  *model_ = get_model();

  EXPECT_EQ(model_->stage, GAME_OVER);
}

TEST_F(TetrisModelTest, CheckCollisionTest) {
  is_collision(model_, game_info_, 1, 1);
  is_inside_figure(model_, 1, 1);
}

TEST_F(TetrisModelTest, GenerateNewFigureTest) {
  model_->figure.next_type = TET_I;
  model_->figure.next_color = 0;

  generate_new_figure(model_, game_info_);
  set_model(*model_);
  set_game_info(*game_info_);
  EXPECT_EQ(model_->figure.next_color, TET_I + 1);

  EXPECT_EQ(game_info_->next[0][0], model_->figure.next_color);
  EXPECT_EQ(game_info_->next[0][1], model_->figure.next_color);
  EXPECT_EQ(game_info_->next[0][2], model_->figure.next_color);
  EXPECT_EQ(game_info_->next[0][3], model_->figure.next_color);
}

TEST_F(TetrisModelTest, GenerateNewFigureITest) {
  model_->figure.next_type = TET_I;
  model_->figure.next_color = 0;

  generate_new_figure(model_, game_info_);
  set_model(*model_);
  set_game_info(*game_info_);

  EXPECT_EQ(model_->figure.next_color, TET_I + 1);
  EXPECT_EQ(game_info_->next[0][0], model_->figure.next_color);
  EXPECT_EQ(game_info_->next[0][1], model_->figure.next_color);
  EXPECT_EQ(game_info_->next[0][2], model_->figure.next_color);
  EXPECT_EQ(game_info_->next[0][3], model_->figure.next_color);
}

TEST_F(TetrisModelTest, GenerateNewFigureZTest) {
  model_->figure.next_type = TET_Z;
  model_->figure.next_color = 0;

  generate_new_figure(model_, game_info_);
  set_model(*model_);
  set_game_info(*game_info_);

  EXPECT_EQ(model_->figure.next_color, TET_Z + 1);
  EXPECT_EQ(game_info_->next[0][0], model_->figure.next_color);
  EXPECT_EQ(game_info_->next[0][1], model_->figure.next_color);
  EXPECT_EQ(game_info_->next[1][1], model_->figure.next_color);
  EXPECT_EQ(game_info_->next[1][2], model_->figure.next_color);
}

TEST_F(TetrisModelTest, GenerateNewFigureSTest) {
  model_->figure.next_type = TET_S;
  model_->figure.next_color = 0;

  generate_new_figure(model_, game_info_);
  set_model(*model_);
  set_game_info(*game_info_);

  EXPECT_EQ(model_->figure.next_color, TET_S + 1);
  EXPECT_EQ(game_info_->next[1][0], model_->figure.next_color);
  EXPECT_EQ(game_info_->next[1][1], model_->figure.next_color);
  EXPECT_EQ(game_info_->next[0][1], model_->figure.next_color);
  EXPECT_EQ(game_info_->next[0][2], model_->figure.next_color);
}

TEST_F(TetrisModelTest, GenerateNewFigureTTest) {
  model_->figure.next_type = TET_T;
  model_->figure.next_color = 0;

  generate_new_figure(model_, game_info_);
  set_model(*model_);
  set_game_info(*game_info_);

  EXPECT_EQ(model_->figure.next_color, TET_T + 1);
  EXPECT_EQ(game_info_->next[0][0], model_->figure.next_color);
  EXPECT_EQ(game_info_->next[0][1], model_->figure.next_color);
  EXPECT_EQ(game_info_->next[0][2], model_->figure.next_color);
  EXPECT_EQ(game_info_->next[1][1], model_->figure.next_color);
}

TEST_F(TetrisModelTest, GenerateNewFigureLTest) {
  model_->figure.next_type = TET_L;
  model_->figure.next_color = 0;

  generate_new_figure(model_, game_info_);
  set_model(*model_);
  set_game_info(*game_info_);

  EXPECT_EQ(model_->figure.next_color, TET_L + 1);
  EXPECT_EQ(game_info_->next[0][0], model_->figure.next_color);
  EXPECT_EQ(game_info_->next[0][1], model_->figure.next_color);
  EXPECT_EQ(game_info_->next[0][2], model_->figure.next_color);
  EXPECT_EQ(game_info_->next[1][0], model_->figure.next_color);
}

TEST_F(TetrisModelTest, GenerateNewFigureJTest) {
  model_->figure.next_type = TET_J;
  model_->figure.next_color = 0;

  generate_new_figure(model_, game_info_);
  set_model(*model_);
  set_game_info(*game_info_);

  EXPECT_EQ(model_->figure.next_color, TET_J + 1);
  EXPECT_EQ(game_info_->next[0][0], model_->figure.next_color);
  EXPECT_EQ(game_info_->next[1][0], model_->figure.next_color);
  EXPECT_EQ(game_info_->next[1][1], model_->figure.next_color);
  EXPECT_EQ(game_info_->next[1][2], model_->figure.next_color);
}

TEST_F(TetrisModelTest, GenerateNewFigureOTest) {
  model_->figure.next_type = TET_O;
  model_->figure.next_color = 0;

  generate_new_figure(model_, game_info_);
  set_model(*model_);
  set_game_info(*game_info_);

  EXPECT_EQ(model_->figure.next_color, TET_O + 1);
  EXPECT_EQ(game_info_->next[0][0], model_->figure.next_color);
  EXPECT_EQ(game_info_->next[0][1], model_->figure.next_color);
  EXPECT_EQ(game_info_->next[1][0], model_->figure.next_color);
  EXPECT_EQ(game_info_->next[1][1], model_->figure.next_color);
}

TEST_F(TetrisModelTest, CheckNoFullLines) {
  for (size_t i = 0; i < HEIGHT; i++) {
    for (size_t j = 0; j < WIDTH; j++) {
      game_info_->field[i][j] = 0;
    }
  }

  check_full_lines(game_info_);
  set_game_info(*game_info_);

  for (size_t i = 0; i < HEIGHT; i++) {
    for (size_t j = 0; j < WIDTH; j++) {
      EXPECT_EQ(game_info_->field[i][j], 0);
    }
  }
}

TEST_F(TetrisModelTest, CheckOneFullLine) {
  for (size_t j = 0; j < WIDTH; j++) {
    game_info_->field[2][j] = 1;
  }

  set_game_info(*game_info_);
  check_full_lines(game_info_);

  for (size_t j = 0; j < WIDTH; j++) {
    EXPECT_EQ(game_info_->field[2][j], 0);
    EXPECT_EQ(game_info_->field[1][j], 0);
    EXPECT_EQ(game_info_->field[0][j], 0);
  }
}

TEST_F(TetrisModelTest, CheckFullLinesAndUpdateScore) {
  for (size_t j = 0; j < WIDTH; j++) {
    game_info_->field[2][j] = 1;
  }

  game_info_->score = 0;
  set_game_info(*game_info_);

  check_full_lines(game_info_);

  EXPECT_GT(game_info_->score, 0);
}

TEST_F(TetrisModelTest, CheckFullLinesInMiddle) {
  for (size_t j = 0; j < WIDTH; j++) {
    game_info_->field[3][j] = 1;
    game_info_->field[4][j] = 1;
  }
  set_game_info(*game_info_);

  check_full_lines(game_info_);
}

TEST_F(TetrisModelTest, CheckFullLinesThreeLines) {
  for (size_t j = 0; j < WIDTH; j++) {
    game_info_->field[1][j] = 1;
    game_info_->field[2][j] = 1;
    game_info_->field[3][j] = 1;
  }
  set_game_info(*game_info_);

  check_full_lines(game_info_);

  for (size_t j = 0; j < WIDTH; j++) {
    EXPECT_EQ(game_info_->field[0][j], 0);
    EXPECT_EQ(game_info_->field[1][j], 0);
    EXPECT_EQ(game_info_->field[2][j], 0);
  }

  for (size_t i = 3; i < HEIGHT; i++) {
    for (size_t j = 0; j < WIDTH; j++) {
      EXPECT_EQ(game_info_->field[i - 3][j], game_info_->field[i][j]);
    }
  }

  EXPECT_EQ(game_info_->score, 700);
}

TEST_F(TetrisModelTest, CheckFullLinesFourLines) {
  for (size_t j = 0; j < WIDTH; j++) {
    game_info_->field[1][j] = 1;
    game_info_->field[2][j] = 1;
    game_info_->field[3][j] = 1;
    game_info_->field[4][j] = 1;
  }
  set_game_info(*game_info_);

  check_full_lines(game_info_);
}
}  // namespace s21
