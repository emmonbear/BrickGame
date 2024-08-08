PROJECT_NAME = brick_game
EXE_FILENAME = game

# COMPILER 
CC = gcc
CXX = g++

# FLAGS
CFLAGS = -Wall -Wextra -Werror -std=c11 -pedantic
CXXFLAGS = -Wall -Wextra -Werror -std=c++17
LDFLAGS = -lcheck -lsubunit -lm

LDGUI = -lncurses
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
TETRIS_DIR = ./brick_game/tetris
BIN_DIR = ../bin
DIST_DIR = ../dist

# MAIN
MAIN_C = $(PROJECT_NAME).c

# COMMON HEADER FOR FRONTEND AND BACKEND 
COMMON_H = $(PROJECT_NAME).h

# COMMON HEADER FOR BACKEND
COMMON_BACKEND_H = $(PROJECT_NAME)/common.h

# LIST OF FILES AND DIRECTORIES IN TETRIS_DIR
TETRIS_DIRS = $(shell find $(TETRIS_DIR) -type d)
TETRIS_C = $(shell find $(TETRIS_DIR) -type f -name "*.c")
TETRIS_H = $(shell find $(TETRIS_DIR) -type f -name "*.h")
TETRIS_O = $(notdir $(TETRIS_C:%.c=%.o))
TETRIS_OBJ_PATH = $(addprefix $(OBJ_DIR)/, $(TETRIS_O))

# LIST OF FILES AND DIRECTORIES IN GUI_DIR
GUI_DIRS = $(shell find $(GUI_DIR) -type d)
GUI_C = $(shell find $(GUI_DIR) -type f -name "*.c")
GUI_H = $(shell find $(GUI_DIR) -type f -name "*.h")
GUI_O = $(notdir $(GUI_C:%.c=%.o))
GUI_OBJ_PATH = $(addprefix $(OBJ_DIR)/, $(GUI_O))

# LIST OF FILES TO CLANG-FORMAT AND CPPCHECK
C_FILES = $(TETRIS_C) $(GUI_C) $(MAIN_C) $(TESTS_C)
H_FILES = $(TETRIS_H) $(GUI_H) $(COMMON_H) $(TESTS_H) $(COMMON_BACKEND_H)
ALL_FILES = $(C_FILES) $(H_FILES)

# LIST of FILES AND DIRECTORIES IN TESTS
TESTS_DIRS = $(shell find $(TESTS_DIR) -type d)
TESTS_C = $(shell find $(TESTS_DIR) -type f -name "*.c")
TESTS_H = $(shell find $(TESTS_DIR) -type f -name "*.h")
TESTS_O = $(notdir $(TESTS_C:%.c=%.o))
TESTS_OBJ_PATH = $(OBJ_DIR)/*_test.o

# CONFIGURING PATH TO SEARH FOR UNPREFIXED PATHS
vpath %.c $(TETRIS_DIRS) : $(GUI_DIRS) : $(TESTS_DIRS)
vpath %.o $(OBJ_DIR)

# TARGETS

.PHONY: all
all: install run

.PHONY: install
install: $(BIN_DIR) $(LIB) $(GUI_LIB) $(COMMON_H) $(COMMON_BACKEND_H)
	$(CC) $(CFLAGS) $(MAIN_C) $(LIB) $(GUI_LIB) $(LDGUI) -o $(BIN_DIR)/$(PROJECT_NAME)

.PHONY: run
run:
	$(BIN_DIR)/$(PROJECT_NAME)

.PHONY: uninstall
uninstall: clean
	rm -rf $(BIN_DIR)
	rm -rf $(DOCS_DIR)
	rm -f ./brick_game/tetris/max_score.txt

.PHONY: $(LIB)
$(LIB): $(OBJ_DIR) $(TETRIS_O) $(TETRIS_H)
	ar rcs $@ $(TETRIS_OBJ_PATH)
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
	$(CC) $(TESTS_OBJ_PATH) $(TETRIS_C) $(LDFLAGS) $(GCOV_FLAGS) -o $(addprefix $(OBJ_DIR)/, $(TARGET))
	-./$(addprefix $(OBJ_DIR)/, $(TARGET))
	gcovr -r . --html --html-details -o $(REPORT_DIR)/coverage.html
	xdg-open $(REPORT_DIR)/coverage.html

.PHONY: dvi
dvi:
	rm -rf $(DOCS_DIR)
	doxygen Doxyfile

.PHONY: dvi_open
dvi_open:
	xdg-open $(DOCS_DIR)/html/index.html

.PHONY: clean
clean:
	rm -rf $(REPORT_DIR)
	rm -rf $(OBJ_DIR)
	rm -rf $(DOCS_DIR)
	rm -f $(LIB)
	rm -f $(GUI_LIB)
	rm -rf $(BIN_DIR)
	rm -f ./val.txt
	rm -f $(TARGET)
	rm -rf $(DIST_DIR)

.PHONY: dist
dist: uninstall dvi $(DIST_DIR) $(LIB) $(GUI_LIB) install
	cp $(LIB) $(GUI_LIB) $(DIST_DIR)
	cp -r $(DOCS_DIR) $(DIST_DIR)
	cp -r $(BIN_DIR) $(DIST_DIR)
	tar -czf $(PROJECT_NAME).tar.gz  $(DIST_DIR)
	rm -rf $(DIST_DIR)


.PHONY: rebuild
rebuild: clean install

.PHONY: dependencies
dependencies:
	sudo apt install libgtest-dev -y
	sudo apt install python3-pip
	pip install cpplint


# OBJECTIVE TARGETS
%.o: %.c ${TETRIS_H}
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

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(DIST_DIR):
	mkdir -p $(DIST_DIR)

