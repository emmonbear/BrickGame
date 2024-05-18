/**
 * @file main_test.c
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief 
 * @version 1.0
 * @date 2024-05-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "./main_test.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

static void test_function(Suite *(**array)(void), size_t size, char *name,
                          int *passed_count, int *failed_count);
static void conclusion(int passed_count, int failed_count, double time);
static void function_declaration(char *function);
static int test_suite(Suite *test, int *passed_count);
static void greetings();
static void line();
static void declare_line(int mode);

int main(void) {
  int failed_count = 0;
  int passed_count = 0;

  greetings();
  struct timeval start, end;

  gettimeofday(&start, NULL);

#ifdef OPERATIONS
  Suite *(*operations[])(void) = {
      operations_test,
  };
  test_function(operations, sizeof(operations) / sizeof(operations[0]), "OPERATIONS",
                &passed_count, &failed_count);
#endif

#ifdef INIT
  Suite *(*init[])(void) = {
      init_test,
  };
  test_function(init, sizeof(init) / sizeof(init[0]), "INIT", &passed_count,
                &failed_count);
#endif

#ifdef CHECKS
  Suite *(*checks[])(void) = {
      checks_test,
  };
  test_function(checks, sizeof(checks) / sizeof(checks[0]), "CHECKS", &passed_count,
                &failed_count);
#endif

#ifdef FIGURES
  Suite *(*figures[])(void) = {
      figures_test,
  };
  test_function(figures, sizeof(figures) / sizeof(figures[0]), "FIGURES",
                &passed_count, &failed_count);
#endif

#ifdef FSM
  Suite *(*fsm[])(void) = {
      fsm_test,
  };
  test_function(fsm, sizeof(fsm) / sizeof(fsm[0]),
                "FSM", &passed_count, &failed_count);
#endif

  gettimeofday(&end, NULL);
  double micros = (((double)((end.tv_sec - start.tv_sec) * 1000000.0) +
                    (double)end.tv_usec) -
                   (double)(start.tv_usec)) /
                  1000000.0;
  conclusion(passed_count, failed_count, micros);

  return (failed_count) ? EXIT_FAILURE : EXIT_SUCCESS;
}

static int test_suite(Suite *test, int *passed_count) {
  SRunner *suite_runner = srunner_create(test);

  srunner_run_all(suite_runner, CK_NORMAL);
  int failed_count = srunner_ntests_failed(suite_runner);
  *passed_count += srunner_ntests_run(suite_runner) - failed_count;
  srunner_free(suite_runner);

  return failed_count;
}

static void greetings() {
  printf(ORANGE
         "\t\t\t\t __          __  _                            _          _   "
         "         _   _\n");
  printf(
      "\t\t\t\t \\ \\        / / | |                          | |        | |   "
      "       | | (_)            \n");
  printf(
      "\t\t\t\t  \\ \\  /\\  / /__| | ___ ___  _ __ ___   ___  | |_ ___   | |_ "
      "___  ___| |_ _ _ __   __ _ \n");
  printf(
      "\t\t\t\t   \\ \\/  \\/ / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | __/ _ \\  "
      "| __/ _ \\/ __| __| | '_ \\ / _` |\n");
  printf(
      "\t\t\t\t    \\  /\\  /  __/ | (_| (_) | | | | | |  __/ | || (_) | | ||  "
      "__/\\__ \\ |_| | | | | (_| |\n");
  printf(
      "\t\t\t\t     \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|  \\__\\___/  "
      " \\__\\___||___/\\__|_|_| |_|\\__, |\n");
  printf(
      "\t\t\t\t                                                                "
      "                   __/ |\n");
  printf(
      "\t\t\t\t                                                                "
      "                  |___/ \n");
  printf("\t\t\t\t                                    _\n");
  printf("\t\t\t\t                                   | |\n");
  printf("\t\t\t\t                                   | |__  _   _\n");
  printf("\t\t\t\t                                   | '_ \\| | | |\n");
  printf("\t\t\t\t                                   | |_) | |_| |\n");
  printf("\t\t\t\t                                   |_.__/ \\__, |\n");
  printf(
      "\t\t\t\t                       _                   __/ |   _     _\n");
  printf(
      "\t\t\t\t                      | |                 |___/   | |   | |\n");
  printf(
      "\t\t\t\t                      | | _____  ___ ___  __ _  __| | __| | __ "
      "_\n");
  printf(
      "\t\t\t\t                      | |/ / _ \\/ __/ __|/ _` |/ _` |/ _` |/ "
      "_` |\n");
  printf(
      "\t\t\t\t                      |   < (_) \\__ \\__ \\ (_| | (_| | (_| | "
      "(_| |\n");
  printf(
      "\t\t\t\t                      "
      "|_|\\_\\___/|___/___/\\__,_|\\__,_|\\__,_|\\__,_|\n");
  printf(
      "\t\t\t\t                                                     | |        "
      "       \n");
  printf(
      "\t\t\t\t                  ___ _ __ ___  _ __ ___   ___  _ __ | |__   "
      "___  __ _ \n");
  printf(
      "\t\t\t\t                 / _ \\ '_ ` _ \\| '_ ` _ \\ / _ \\| '_ \\| '_ "
      "\\ / _ \\/ _` |\n");
  printf(
      "\t\t\t\t                |  __/ | | | | | | | | | | (_) | | | | |_) |  "
      "__/ (_| |\n");
  printf(
      "\t\t\t\t                 \\___|_| |_| |_|_| |_| |_|\\___/|_| |_|_.__/ "
      "\\___|\\__,_|\n" RESET);
}

static void test_function(Suite *(**array)(void), size_t size, char *name,
                          int *passed_count, int *failed_count) {
  function_declaration(name);
  for (size_t i = 0; i < size; i++) {
    line();
    *failed_count += test_suite(array[i](), passed_count);
  }
  line();
}

static void function_declaration(char *function) {
  char space[] =
      "                                                                        "
      " ";
  char space1[100];
  char space2[100];
  sprintf(space1, "%s", space);
  sprintf(space2, "%s", space);
  int len = strlen(function) / 2;
  space1[strlen(space1) - len] = '\0';
  space2[strlen(space2) - (len + ((strlen(function) % 2) ? 1 : 0))] = '\0';
  declare_line(0);
  printf("|%s%s TESTS %s|\n", space1, function, space2);
  declare_line(1);
}

static void line() {
  printf(ORANGE
         "====================================================================="
         "====================================================================="
         "=================\n");
}

static void declare_line(int mode) {
  if (mode) {
    printf("|");
  } else {
    printf(ORANGE "\n\n ");
  }
  for (int i = 0; i < 153; i++) {
    printf("_");
  }
  if (mode) {
    printf("|\n\n\n" RESET);
  } else {
    printf("\n");
  }
  if (!mode) {
    printf("|");
    for (int i = 0; i < 153; i++) {
      printf(" ");
    }
    printf("|\n");
  }
}

static void conclusion(int passed_count, int failed_count, double time) {
  char result[] =
      "                                                               ";
  char temp[50];
  sprintf(temp, "%d", passed_count);
  result[strlen(result) - strlen(temp)] = '\0';
  sprintf(temp, "%d", failed_count);
  result[strlen(result) - strlen(temp)] = '\0';
  sprintf(temp, "%.2lf", time);
  result[strlen(result) - strlen(temp)] = '\0';

  printf(ORANGE
         "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
         "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
         "~~~~~~~~~~~~~~~~~~~~~\n");
  printf(
      "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "
      "TOTAL RESULTS "
      "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
      "~~\n");
  printf(
      "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
      "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
      "~~~~~~~~~~~\n\n");
  printf("%sPASSED %d tests from %d for %.2lf seconds\n\n", result,
         passed_count, passed_count + failed_count, time);
  printf(
      "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
      "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
      "~~~~~~~~~~~" RESET "\n\n");
}
