#include "./main_test.h"

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  if (argc > 1) {
    ::testing::GTEST_FLAG(filter) = argv[1];
  }

  return RUN_ALL_TESTS();
}
