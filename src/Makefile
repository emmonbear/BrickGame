PROJECT_NAME = brick_game

# COMPILER 
CC = gcc

# FLAGS
CFLAGS = -Wall -Wextra -Werror -std=c11 -pedantic
LDFLAGS = -lcheck -lsubuinit -lm
LDGUI = -lncurses
DEBUG = -g

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
MAIN_H = $(PROJECT_NAME).h

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

# CONFIGURING PATH TO SEARH FOR UNPREFIXED PATHS
vpath %.c $(MODULES_DIRS) : $(GUI_DIRS)
vpath %.o $(OBJ_DIR)

# TARGETS
.PHONY: m
m:
	clear
	$(MAKE) install

.PHONY: install
install: $(LIB) $(GUI_LIB)
	$(CC) $(CFLAGS) $(MAIN_C) $(LIB) $(GUI_LIB) $(LDGUI) -o $(PROJECT_NAME)
	./$(PROJECT_NAME)

.PHONY: $(LIB)
$(LIB): $(OBJ_DIR) $(MODULES_O) $(MODULES_H) $(MAIN_H)
	ar rcs $@ $(MODULES_OBJ_PATH)
	ranlib $@

.PHONY: $(GUI_LIB)
$(GUI_LIB): $(OBJ_DIR) $(GUI_O) $(GUI_H) $(MAIN_H)
	ar rcs $@ $(GUI_OBJ_PATH)
	ranlib $@

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
	rm -f $(PROJECT_NAME)

# OBJECTIVE TARGETS
%.o: %.c ${MODULES_H}
	$(CC) $(CFLAGS) -c -o $(addprefix $(OBJ_DIR)/, $@) $<
 
# CREATE DIRECTORIES
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(REPORT_DIR):
	mkdir -p $(REPORT_DIR)

