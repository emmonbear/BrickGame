/**
 * @file common.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-09-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_INCLUDE_COMMON_COMMON_H_
#define SRC_INCLUDE_COMMON_COMMON_H_

#include <stdio.h>
#include <stdlib.h>

#define MEM_ALLOC_ERROR                                                        \
  do {                                                                         \
    fprintf(stderr, "Memory allocation error at %s:%d\n", __FILE__, __LINE__); \
    exit(EXIT_FAILURE);                                                        \
  } while (0)

void allocate_2d_array(int ***array, size_t rows, size_t cols);
void destroy_2d_array(int ***array, size_t rows);

#endif  // SRC_INCLUDE_COMMON_COMMON_H_
