/**
 * @file init.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief
 * @version 1.0
 * @date 2024-05-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef MODULES_INIT_H
#define MODULES_INIT_H

#include <stdio.h>
#include <stdlib.h>

#define MEM_ALLOC_ERROR                         \
  fprintf(stderr, "Memory allocation error\n"); \
  exit(1);

/**
 * @brief Allocates memory for a 2D array of integers.
 *
 * @param[in,out] array pointer to a pointer to the array for which memory is
 * allocated.
 * @param[in] rows number of rows in the array.
 * @param[in] cols number of columns in the array.
 *
 * @note In case of unsuccessful memory allocation, the function terminates the
 * program with an error message.
 */
void allocate_2d_array(int **array, size_t rows, size_t cols);

/**
 * @brief Frees the memory allocated for a 2D array of integers.
 *
 * @param[in, out] array - pointer to a pointer to the array for which memory is
 * freed.
 * @param[in] rows number of rows in the array.
 * @param[in] cols number of columns in the array.
 */
void destroy_2d_array(int **array, size_t rows, size_t cols);

#endif  // MODULES_INIT_H