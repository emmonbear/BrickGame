PROJECT_NAME = brick_game
EXE_FILENAME = game

# COMPILER 
CC = gcc

# FLAGS
CFLAGS = -Wall -Wextra -Werror -std=c11 -pedantic
LDFLAGS = -lcheck -lsubunit -lm
LDGUI = -lncursesw
DEBUG = -g
VALGRIND = --tool=memcheck --leak-check=yes
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

# TARGET NAMES
LIB = $(PROJECT_NAME).a
GUI_LIB = $(PROJECT_NAME)_gui.a
TARGET = test
GCOV = gcov_report

# DIRECTORY NAMES
OBJ_DIR = ./obj
REPORT_DIR = ./report
TESTS_DIR = ./tests
GUI_DIR = ./gui/cli
DOCS_DIR = ../docs
MODULES_DIR = ./brick_game/tetris

# MAIN
MAIN_C = $(PROJECT_NAME).c

# COMMON_H
COMMON_H = common.h

# LIST OF FILES AND DIRECTORIES IN MODULES_DIR
MODULES_DIRS = $(shell find $(MODULES_DIR) -type d)
MODULES_C = $(shell find $(MODULES_DIR) -type f -name "*.c")
MODULES_H = $(shell find $(MODULES_DIR) -type f -name "*.h")
MODULES_O = $(notdir $(MODULES_C:%.c=%.o))
MODULES_OBJ_PATH = $(addprefix $(OBJ_DIR)/, $(MODULES_O))

# LIST OF FILES AND DIRECTORIES IN GUI_DIR
GUI_DIRS = $(shell find $(GUI_DIR) -type d)
GUI_C = $(shell find $(GUI_DIR) -type f -name "*.c")
GUI_H = $(shell find $(GUI_DIR) -type f -name "*.h")
GUI_O = $(notdir $(GUI_C:%.c=%.o))
GUI_OBJ_PATH = $(addprefix $(OBJ_DIR)/, $(GUI_O))

# LIST OF FILES TO CLANG-FORMAT AND CPPCHECK
C_FILES = $(MODULES_C) $(GUI_C)
H_FILES = $(MODULES_H) $(GUI_H)
ALL_FILES = $(C_FILES) $(H_FILES)

# LIST of FILES AND DIRECTORIES IN TESTS
TESTS_DIRS = $(shell find $(TESTS_DIR) -type d)
TESTS_C = $(shell find $(TESTS_DIR) -type f -name "*.c")
TESTS_H = $(shell find $(TESTS_DIR) -type f -name "*.h")
TESTS_O = $(notdir $(TESTS_C:%.c=%.o))
TESTS_OBJ_PATH = $(OBJ_DIR)/*_test.o

# CONFIGURING PATH TO SEARH FOR UNPREFIXED PATHS
vpath %.c $(MODULES_DIRS) : $(GUI_DIRS) : $(TESTS_DIRS)
vpath %.o $(OBJ_DIR)

# TARGETS

.PHONY: all
all: rebuild

.PHONY: install
install: $(LIB) $(GUI_LIB) $(COMMON_H)
	$(CC) $(CFLAGS) $(DEBUG) $(MAIN_C) $(LIB) $(GUI_LIB) $(LDGUI) -o $(EXE_FILENAME)
	./$(EXE_FILENAME)

.PHONY: $(LIB)
$(LIB): $(OBJ_DIR) $(MODULES_O) $(MODULES_H)
	ar rcs $@ $(MODULES_OBJ_PATH)
	ranlib $@

.PHONY: $(GUI_LIB)
$(GUI_LIB): $(OBJ_DIR) $(GUI_O) $(GUI_H)
	ar rcs $@ $(GUI_OBJ_PATH)
	ranlib $@

.PHONY: $(TARGET)
$(TARGET): $(OBJ_DIR) $(TESTS_O) $(LIB)
	$(CC) $(TESTS_OBJ_PATH) $(LIB) $(LDFLAGS) -o $@
	./$@

.PHONE: $(GCOV)
$(GCOV): $(OBJ_DIR) $(REPORT_DIR) $(TESTS_O)
	$(CC) $(TESTS_OBJ_PATH) $(MODULES_C) $(LDFLAGS) $(GCOV_FLAGS) -o $(addprefix $(OBJ_DIR)/, $(TARGET))
	-./$(addprefix $(OBJ_DIR)/, $(TARGET))
	gcovr -r . --html --html-details -o $(REPORT_DIR)/coverage.html
	xdg-open $(REPORT_DIR)/coverage.html

.PHONY: dvi
dvi:
	rm -rf $(DOCS_DIR)
	doxygen Doxyfile
	xdg-open $(DOCS_DIR)/html/index.html

.PHONY: clean
clean:
	rm -rf $(REPORT_DIR)
	rm -rf $(OBJ_DIR)
	rm -rf $(DOCS_DIR)
	rm -f $(LIB)
	rm -f $(GUI_LIB)
	rm -f $(EXE_FILENAME)
	rm -f ./val.txt
	rm -f $(TARGET)

.PHONY: rebuild
rebuild: clean install

# OBJECTIVE TARGETS
%.o: %.c ${MODULES_H}
	$(CC) $(CFLAGS) -c -o $(addprefix $(OBJ_DIR)/, $@) $<

%_gui.o: gui_%.c $(GUI_H)
	$(CC) $(CFLAGS) -c -o $(addprefix $(OBJ_DIR)/, $@) $<

# CHECKS
valgrind: $(TARGET)
	@printf '\033[1;33m\n\t\t\t\t                   _            _           _   _            _   _             \n'
	@printf '\t\t\t\t                  | |          (_)         | | | |          | | (_)            \n'
	@printf '\t\t\t\t       __   ____ _| | __ _ _ __ _ _ __   __| | | |_ ___  ___| |_ _ _ __   __ _ \n'
	@printf '\t\t\t\t       \ \ / / _` | |/ _` | '\''__| | '\''_ \ / _` | | __/ _ \/ __| __| | '\''_ \ / _` |\n'
	@printf '\t\t\t\t        \ V / (_| | | (_| | |  | | | | | (_| | | ||  __/\__ \ |_| | | | | (_| |\n'
	@printf '\t\t\t\t         \_/ \__,_|_|\__, |_|  |_|_| |_|\__,_|  \__\___||___/\__|_|_| |_|\__, |\n'
	@printf '\t\t\t\t                      __/ |                                               __/ |\n'
	@printf '\t\t\t\t                     |___/                                               |___/ \n\033[0m\n'

	@$@ $(VALGRIND) ./$(TARGET) > val.txt 2>&1 && \
	{ \
		printf "\033[1;33m\n"; \
		printf "###########################################################################################################################################################\n\n"; \
		printf "                                                                 Valgrind test results:\n"; \
		printf "                                                                Passed tests $$(grep "ERROR SUMMARY: 0" -c val.txt) from $$(grep "ERROR SUMMARY:" -c val.txt)\n\n"; \
		printf "###########################################################################################################################################################\n"; \
		printf "\033[0m\n"; \
	}

clang_fix:
	clang-format -style=Google -i $(ALL_FILES)

clang_check:
	clang-format -style=Google -n $(ALL_FILES)

# CREATE DIRECTORIES
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(REPORT_DIR):
	mkdir -p $(REPORT_DIR)

