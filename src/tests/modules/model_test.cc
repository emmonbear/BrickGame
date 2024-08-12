/**
 * @file model_test.cc
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief Model tests
 * @version 1.0
 * @date 2024-08-12
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../main_test.h"

class ModelTest : public ::testing::Test {
 protected:
  void SetUp() override {
    model = new Model_t;
    init_model(model);
    reset_game_info(model);
  }

  void TearDown() override {
    destroy_model(model);
    delete model;
  }
  Model_t *model;
};

TEST_F(ModelTest, ModelInitializaton) {
  ASSERT_NE(model->game_info.field, nullptr);
  ASSERT_NE(model->game_info.next, nullptr);
  ASSERT_NE(model->figure.current_figure, nullptr);
  ASSERT_NE(model->figure.rotated_figure, nullptr);
}

TEST_F(ModelTest, PutFigure) {
  model->figure.x = 3;
  model->figure.y = 2;
  model->figure.current_color = 1;

  model->figure.current_figure[0][0] = 1;
  model->figure.current_figure[0][1] = 1;
  model->figure.current_figure[1][0] = 1;
  model->figure.current_figure[1][1] = 1;

  put_figure(model);

  EXPECT_EQ(model->game_info.field[2][3], 1);
  EXPECT_EQ(model->game_info.field[2][4], 1);
  EXPECT_EQ(model->game_info.field[3][3], 1);
  EXPECT_EQ(model->game_info.field[3][4], 1);
}

TEST_F(ModelTest, GeneratesFigureI) {
  model->figure.next_type = TET_I;

  generate_new_figure(model);

  EXPECT_EQ(model->figure.next_type, TET_I);
}

TEST_F(ModelTest, GeneratesFigureZ) {
  model->figure.next_type = TET_Z;

  generate_new_figure(model);

  EXPECT_EQ(model->figure.next_type, TET_Z);
}

TEST_F(ModelTest, GeneratesFigureS) {
  model->figure.next_type = TET_S;

  generate_new_figure(model);

  EXPECT_EQ(model->figure.next_type, TET_S);
}

TEST_F(ModelTest, GeneratesFigureT) {
  model->figure.next_type = TET_T;

  generate_new_figure(model);

  EXPECT_EQ(model->figure.next_type, TET_T);
}

TEST_F(ModelTest, GeneratesFigureL) {
  model->figure.next_type = TET_L;

  generate_new_figure(model);

  EXPECT_EQ(model->figure.next_type, TET_L);
}

TEST_F(ModelTest, GeneratesFigureO) {
  model->figure.next_type = TET_O;

  generate_new_figure(model);

  EXPECT_EQ(model->figure.next_type, TET_O);
}

TEST_F(ModelTest, GeneratesFigureJ) {
  model->figure.next_type = TET_J;

  generate_new_figure(model);

  EXPECT_EQ(model->figure.next_type, TET_J);
}

TEST_F(ModelTest, GeneratesNone) {
  model->figure.next_type = NONE;

  generate_new_figure(model);

  EXPECT_EQ(model->figure.next_type, NONE);
}

TEST_F(ModelTest, CopyNextToCurrent) {
  model->game_info.next[0][0] = 1;
  model->game_info.next[0][1] = 2;
  model->game_info.next[1][0] = 3;
  model->game_info.next[1][1] = 4;

  model->figure.next_color = 5;
  model->figure.next_type = TET_L;

  copy_next_to_current(model);

  EXPECT_EQ(model->figure.current_figure[0][0], 1);
  EXPECT_EQ(model->figure.current_figure[0][1], 2);
  EXPECT_EQ(model->figure.current_figure[1][0], 3);
  EXPECT_EQ(model->figure.current_figure[1][1], 4);

  EXPECT_EQ(model->figure.current_color, 5);

  EXPECT_EQ(model->figure.current_type, TET_L);
}

TEST_F(ModelTest, GenerateRandomFigure) {
  type_t current_type = TET_I;

  type_t new_type = generate_random(current_type);

  EXPECT_NE(new_type, current_type);

  EXPECT_GE(new_type, 0);
  EXPECT_LT(new_type, NUM_TETROMINOS);
}

TEST_F(ModelTest, IsInsideFigure) {
  model->figure.x = 3;
  model->figure.y = 2;

  model->figure.current_figure[0][0] = 1;
  model->figure.current_figure[0][1] = 1;
  model->figure.current_figure[1][0] = 1;
  model->figure.current_figure[1][1] = 1;

  EXPECT_TRUE(is_inside_figure(model, 2, 3));
  EXPECT_TRUE(is_inside_figure(model, 2, 4));
  EXPECT_TRUE(is_inside_figure(model, 3, 3));
  EXPECT_TRUE(is_inside_figure(model, 3, 4));

  EXPECT_FALSE(is_inside_figure(model, 0, 0));
  EXPECT_FALSE(is_inside_figure(model, 1, 1));
  EXPECT_FALSE(is_inside_figure(model, 4, 5));
  EXPECT_FALSE(is_inside_figure(model, 3, 5));
}

TEST_F(ModelTest, CanMoveRight) {
  model->figure.x = 3;
  model->figure.y = 2;

  model->figure.current_figure[0][2] = 1;
  model->figure.current_figure[1][2] = 1;

  EXPECT_TRUE(can_move_right(model));

  model->figure.x = WIDTH - 2;
  EXPECT_FALSE(can_move_right(model));

  model->figure.x = 3;
  model->game_info.field[2][6] = 1;
  EXPECT_FALSE(can_move_right(model));
}

TEST_F(ModelTest, CanMoveLeft) {
  model->figure.x = 3;
  model->figure.y = 2;

  model->figure.current_figure[0][0] = 1;
  model->figure.current_figure[1][0] = 1;

  EXPECT_TRUE(can_move_left(model));

  model->figure.x = 0;
  EXPECT_FALSE(can_move_left(model));

  model->figure.x = 3;
  model->game_info.field[2][2] = 1;
  EXPECT_FALSE(can_move_left(model));
}

TEST_F(ModelTest, CanRotate) {
  model->figure.x = 3;
  model->figure.y = 2;

  model->figure.rotated_figure[0][0] = 1;
  model->figure.rotated_figure[1][0] = 1;
  model->figure.rotated_figure[0][1] = 1;
  model->figure.rotated_figure[1][1] = 1;

  EXPECT_TRUE(can_rotate(model));

  model->figure.x = WIDTH - 1;
  EXPECT_FALSE(can_rotate(model));

  model->figure.x = 3;
  model->game_info.field[2][4] = 1;
  EXPECT_FALSE(can_rotate(model));
}

TEST_F(ModelTest, CanMoveDown) {
  model->figure.x = 3;
  model->figure.y = 0;

  model->figure.current_figure[0][0] = 1;
  model->figure.current_figure[1][0] = 1;
  model->figure.current_figure[0][1] = 1;
  model->figure.current_figure[1][1] = 1;

  EXPECT_TRUE(can_move_down(model));

  model->figure.y = HEIGHT - 2;
  EXPECT_FALSE(can_move_down(model));
}

TEST_F(ModelTest, CanMoveDown1) {
  model->figure.x = 0;
  model->figure.y = 0;

  model->figure.current_figure[0][0] = 1;
  model->figure.current_figure[1][0] = 1;
  model->figure.current_figure[0][1] = 1;
  model->figure.current_figure[1][1] = 1;

  model->game_info.field[2][0] = 1;
  EXPECT_FALSE(can_move_down(model));
}

TEST_F(ModelTest, CheckFullLines) {
  for (size_t i = 1; i < 4; i++) {
    for (size_t j = 0; j < WIDTH; j++) {
      model->game_info.field[i][j] = 0;
    }
  }

  check_full_lines(model);
}

TEST_F(ModelTest, CheckFullLines1) {
  for (size_t i = 3; i < 4; i++) {
    for (size_t j = 0; j < WIDTH; j++) {
      model->game_info.field[i][j] = 1;
    }
  }

  check_full_lines(model);
}

TEST_F(ModelTest, CheckFullLines2) {
  for (size_t i = 3; i < 5; i++) {
    for (size_t j = 0; j < WIDTH; j++) {
      model->game_info.field[i][j] = 1;
    }
  }

  check_full_lines(model);
}

TEST_F(ModelTest, CheckFullLines3) {
  for (size_t i = 3; i < 6; i++) {
    for (size_t j = 0; j < WIDTH; j++) {
      model->game_info.field[i][j] = 1;
    }
  }

  check_full_lines(model);
}

TEST_F(ModelTest, CheckFullLines4) {
  model->game_info.level = 1;
  for (size_t i = 3; i < 7; i++) {
    for (size_t j = 0; j < WIDTH; j++) {
      model->game_info.field[i][j] = 1;
    }
  }

  check_full_lines(model);
}

TEST_F(ModelTest, CanPutNewLine) {
  model->figure.next_type = TET_L;
  generate_new_figure(model);

  for (size_t i = 0; i < WIDTH; i++) {
    model->game_info.field[1][i] = 1;
  }

  EXPECT_FALSE(can_put_new_line(model));
}

TEST_F(ModelTest, CanPutNewLine1) {
  model->figure.next_type = TET_L;
  generate_new_figure(model);

  EXPECT_TRUE(can_put_new_line(model));
}

TEST_F(ModelTest, ResetGameInfo) {
  model->game_info.score = 100;
  model->game_info.high_score = 500;
  model->game_info.level = 3;
  model->game_info.speed = 2;
  model->game_info.pause = 1;
  model->figure.next_color = 5;
  model->figure.next_type = TET_I;
  model->figure.current_type = TET_Z;
  model->figure.current_color = 6;

  reset_game_info(model);

  EXPECT_EQ(model->game_info.score, 0);
  EXPECT_EQ(model->game_info.level, 1);
  EXPECT_EQ(model->game_info.speed, 1);
  EXPECT_EQ(model->game_info.pause, 0);
  EXPECT_EQ(model->figure.next_color, -1);
  EXPECT_EQ(model->figure.next_type, NONE);
  EXPECT_EQ(model->figure.current_type, NONE);
  EXPECT_EQ(model->figure.current_color, -1);
}

TEST_F(ModelTest, WriteHighScore) {
  model->game_info.high_score = 9999;
  write_high_score(model);

  EXPECT_EQ(model->game_info.high_score, 9999);
}

TEST_F(ModelTest, MoveDown) {
  model->figure.x = 1;
  model->figure.y = 1;
  model->figure.current_figure[0][0] = 1;

  move_down(model);

  EXPECT_EQ(model->figure.y, 2);
}

TEST_F(ModelTest, MoveLeft) {
  model->figure.x = 5;
  model->figure.y = 1;
  model->figure.current_figure[0][0] = 1;

  move_left(model);

  EXPECT_EQ(model->figure.x, 4);
}

TEST_F(ModelTest, MoveRight) {
  model->figure.x = 3;
  model->figure.y = 1;
  model->figure.current_figure[0][0] = 1;

  move_right(model);

  EXPECT_EQ(model->figure.x, 4);
}

TEST_F(ModelTest, RotateFigure) {
  model->figure.next_type = TET_T;
  generate_new_figure(model);
  copy_next_to_current(model);
  get_rotated_figure(model);
  rotate_figure(model);
  EXPECT_EQ(model->figure.current_figure[0][1], TET_T + 1);
  EXPECT_EQ(model->figure.current_figure[1][0], TET_T + 1);
  EXPECT_EQ(model->figure.current_figure[1][1], TET_T + 1);
  EXPECT_EQ(model->figure.current_figure[2][1], TET_T + 1);
}

TEST_F(ModelTest, GetRotatedFigure) {
  model->figure.current_figure[0][0] = 1;
  model->figure.current_figure[0][1] = 2;
  model->figure.current_figure[1][0] = 3;
  model->figure.current_figure[1][1] = 4;

  get_rotated_figure(model);

  EXPECT_EQ(model->figure.rotated_figure[0][0], 3);
  EXPECT_EQ(model->figure.rotated_figure[0][1], 1);
  EXPECT_EQ(model->figure.rotated_figure[1][0], 4);
  EXPECT_EQ(model->figure.rotated_figure[1][1], 2);
}

TEST_F(ModelTest, ResetField) {
  model->game_info.field[0][0] = 1;
  model->game_info.field[1][1] = 1;

  reset_field(model);

  EXPECT_EQ(model->game_info.field[0][0], 0);
  EXPECT_EQ(model->game_info.field[1][1], 0);
}
