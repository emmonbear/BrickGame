#================================ PROJECT NAME =================================
PROJECT_NAME          := brick_game

#================================== FILENAMES ==================================
CLI                   := $(PROJECT_NAME)_cli
MAX_SCORE_FILE        := $(PROJECT_NAME)/tetris/max_score.txt

#================================== COMPILER =================================== 
CC                    := gcc
CXX                   := g++

#==================================== FLAGS ====================================
CFLAGS                := -Wall -Wextra -std=c11 -pedantic
CXXFLAGS              := -Wall -Wextra -std=c++17
LDFLAGS               := -lcheck -lsubunit -lm
LDGUI                 := -lncurses
VALGRIND              := --tool=memcheck --leak-check=yes
GCOV_FLAGS            := -fprofile-arcs -ftest-coverage

#=============================== TARGET NAMES =================================
MODEL_LIB             := model.a
VIEW_LIB              := view.a
CONTROLLER_LIB        := controller.a
TARGET                := test
GCOV                  := gcov_report

#=============================== DIRECTORY NAMES ===============================
MODEL_DIR             := ./brick_game/tetris
VIEW_DIR              := ./gui/cli
CONTROLLER_DIR        := ./controller/tetris
OBJ_DIR               := ./obj
REPORT_DIR            := ./report
TESTS_DIR             := ./tests
DOCS_DIR              := ../docs
BIN_DIR               := ../bin
DIST_DIR              := ../dist

#================================== MAIN FILE ==================================
MAIN                  := $(PROJECT_NAME).cc

#================================ COMMON MODEL =================================
COMMON_MODEL_H        := $(PROJECT_NAME)/common.h

#================================== FILE LIST ==================================
#=============================== TETRIS CLI VIEW ===============================
VIEW_C                := $(shell find $(VIEW_DIR) -type f -name "*.c")
VIEW_H                := $(shell find $(VIEW_DIR) -type f -name "*.h")
VIEW_O                := $(VIEW_C:$(VIEW_DIR)/modules/%.c=$(OBJ_DIR)/tetris/view/%.o)

#================================ TETRIS MODEL =================================
MODEL_C               := $(shell find $(MODEL_DIR) -type f -name "*.c")
MODEL_H               := $(shell find $(MODEL_DIR) -type f -name "*.h")
MODEL_O               := $(MODEL_C:$(MODEL_DIR)/modules/%.c=$(OBJ_DIR)/tetris/model/%.o)

#============================== TETRIS CONTROLLER ==============================
CONTROLLER_C          := $(shell find $(CONTROLLER_DIR) -type f -name "*.c")
CONTROLLER_H          := $(shell find $(CONTROLLER_DIR) -type f -name "*.h")
CONTROLLER_O          := $(CONTROLLER_C:$(CONTROLLER_DIR)/modules/%.c=$(OBJ_DIR)/tetris/controller/%.o)

#======================= LIST OF FILES FOR CLANG-FORMAT ========================
C_FILES               := $(VIEW_C) $(MODEL_C) $(CONTROLLER_C) $(MAIN)
H_FILES               := $(VIEW_H) $(MODEL_H) $(CONTROLLER_H)

#================================ CLANG-FORMAT =================================
clang_fix:
	clang-format -style=Google -i $(C_FILES) $(H_FILES)

clang_check:
	clang-format -style=Google -n $(C_FILES) $(H_FILES)

#=================================== TARGETS ===================================
.PHONY: all install run clean $(MODEL_LIB) $(VIEW_LIB) $(CONTROLLER_LIB)

all: install run

val:
	valgrind $(BIN_DIR)/$(CLI)

install: $(BIN_DIR) $(MODEL_LIB) $(VIEW_LIB) $(CONTROLLER_LIB)
	$(CXX) $(CXXFLAGS) $(MAIN) $(CONTROLLER_LIB) $(MODEL_LIB) $(VIEW_LIB) $(LDGUI) -o $(BIN_DIR)/$(CLI)

run:
	$(BIN_DIR)/$(CLI)

$(MODEL_LIB): $(OBJ_DIR) $(MODEL_O)
	ar rcs $@ $(MODEL_O)
	ranlib $@

$(VIEW_LIB): $(OBJ_DIR) $(VIEW_O)
	ar rcs $@ $(VIEW_O)
	ranlib $@

$(CONTROLLER_LIB): $(OBJ_DIR) $(CONTROLLER_O)
	ar rcs $@ $(CONTROLLER_O)
	ranlib $@

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(VIEW_LIB)
	rm -f $(MODEL_LIB)
	rm -f $(CONTROLLER_LIB)
	rm -rf $(BIN_DIR)

#============================== OBJECTIVE TARGETS ==============================
$(OBJ_DIR)/tetris/model/%.o: $(MODEL_DIR)/modules/%.c $(MODEL_H) $(COMMON_MODEL_H)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/tetris/view/%.o: $(VIEW_DIR)/modules/%.c $(VIEW_H)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/tetris/controller/%.o: $(CONTROLLER_DIR)/modules/%.c $(CONTROLLER_H)
	$(CC) $(CFLAGS) -c -o $@ $<

#============================= CREATE DIRECTORIES ==============================
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)/tetris/model
	mkdir -p $(OBJ_DIR)/tetris/view
	mkdir -p $(OBJ_DIR)/tetris/controller

$(REPORT_DIR):
	mkdir -p $(REPORT_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(DIST_DIR):
	mkdir -p $(DIST_DIR)
