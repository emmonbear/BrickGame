PROJECT_NAME = brick_game
EXE_FILENAME = game

# COMPILER 
CC = gcc

# FLAGS
CFLAGS = -Wall -Wextra -Werror -std=c11 -pedantic -O3 -funroll-loops
LDFLAGS = -lcheck -lsubuinit -lm
LDGUI = -lncursesw
DEBUG = -g
VALGRIND = --tool=memcheck --leak-check=yes

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

# CONFIGURING PATH TO SEARH FOR UNPREFIXED PATHS
vpath %.c $(MODULES_DIRS) : $(GUI_DIRS)
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

.PHONY: rebuild
rebuild: clean install
# OBJECTIVE TARGETS
%.o: %.c ${MODULES_H}
	$(CC) $(CFLAGS) -c -o $(addprefix $(OBJ_DIR)/, $@) $<

%_gui.o: gui_%.c $(GUI_H)
	$(CC) $(CFLAGS) -c -o $(addprefix $(OBJ_DIR)/, $@) $<

# CHECKS
valgrind: $(EXE_FILENAME)
	@$@ $(VALGRIND) ./$(EXE_FILENAME) > val.txt 2>&1 
# { \
# 	Valgrind test results:\n"; \
# 	Passed tests $$(grep "ERROR SUMMARY: 0" -c val.txt) \
# 	from $$(grep "ERROR SUMMARY:" -c val.txt)\n\n"; \
# }

clang_fix:
	clang-format -style=Google -i $(ALL_FILES)

clang_check:
	clang-format -style=Google -n $(ALL_FILES)

# CREATE DIRECTORIES
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(REPORT_DIR):
	mkdir -p $(REPORT_DIR)

