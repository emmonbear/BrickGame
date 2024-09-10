#================================ PROJECT NAME =================================
PROJECT_NAME          := brick_game

#================================== GAME LIST ==================================
TETRIS                := tetris
SNAKE                 := snake

#================================== COMPILER =================================== 
CC                    := gcc
CXX                   := g++

#==================================== FLAGS ====================================
CFLAGS                := -Wall -Wextra -std=c11 -pedantic -g
CXXFLAGS              := -Wall -Wextra -std=c++17 -g
LDFLAGS               := -lgtest
COVERAGE_FLAGS        := -fprofile-arcs -ftest-coverage
LDGUI                 := -lncurses
VALGRIND              := --tool=memcheck --leak-check=yes

#================================ TARGET NAMES =================================
TETRIS_LIB            := $(TETRIS).a
SNAKE_LIB             := $(SNAKE).a
COMMON_LIB            := common.a
WRAPPERS_LIB          := wrappers.a
CONTROLLER_LIB        := controller.a
CLI_LIB               := cli.a

#=============================== DIRECTORY NAMES ===============================
APP_DIR               := ./app
INCLUDE_DIR           := ./include
TETRIS_DIR            := ./$(PROJECT_NAME)/$(TETRIS)
SNAKE_DIR             := ./$(PROJECT_NAME)/$(SNAKE)
COMMON_DIR            := ./common
WRAPPERS_DIR          := ./wrappers
CONTROLLER_DIR        := ./controller
CLI_DIR               := ./gui/cli
OBJ_DIR               := ./obj
OBJ_DIR_COV           := ./obj_cov
BIN_DIR               := ../bin

#================================== FILE LIST ==================================
CLI                   := $(APP_DIR)/cli.cc
BIN_CLI               := $(BIN_DIR)/cli

#================================ TETRIS MODEL =================================
TETRIS_C              := $(shell find $(TETRIS_DIR) -type f -name "*.c")
TETRIS_H              := $(shell find $(INCLUDE_DIR)/$(TETRIS) -type f -name "*.h")
TETRIS_O              := $(TETRIS_C:$(TETRIS_DIR)/%.c=$(OBJ_DIR)/$(TETRIS)/%.o)
TETRIS_O_COV          := $(TETRIS_C:$(TETRIS_DIR)/%.c=$(OBJ_DIR_COV)/$(TETRIS)/%.o)

#================================= SNAKE MODEL =================================
SNAKE_CC              := $(shell find $(SNAKE_DIR) -type f -name "*.cc")
SNAKE_H               := $(shell find $(INCLUDE_DIR)/$(SNAKE) -type f -name "*.h")
SNAKE_O               := $(SNAKE_CC:$(SNAKE_DIR)/%.cc=$(OBJ_DIR)/$(SNAKE)/%.o)
SNAKE_O_COV           := $(SNAKE_CC:$(SNAKE_DIR)/%.cc=$(OBJ_DIR_COV)/$(SNAKE)/%.o)

#=================================== COMMON ====================================
COMMON_C              := $(shell find $(COMMON_DIR) -type f -name "*.c")
COMMON_H              := $(shell find $(INCLUDE_DIR)/common -type f -name "*.h")
COMMON_O              := $(COMMON_C:$(COMMON_DIR)/%.c=$(OBJ_DIR)/common/%.o)
COMMON_O_COV          := $(COMMON_C:$(COMMON_DIR)/%.c=$(OBJ_DIR_COV)/common/%.o)

#================================== WRAPPERS ===================================
WRAPPERS_CC           := $(shell find $(WRAPPERS_DIR) -type f -name "*.cc")
WRAPPERS_H            := $(shell find $(INCLUDE_DIR)/wrappers -type f -name "*.h")
WRAPPERS_O            := $(WRAPPERS_CC:$(WRAPPERS_DIR)/%.cc=$(OBJ_DIR)/wrappers/%.o)
WRAPPERS_O_COV        := $(WRAPPERS_CC:$(WRAPPERS_DIR)/%.cc=$(OBJ_DIR_COV)/wrappers/%.o)

#================================= INTERFACES ==================================
INTERFACES_H          := $(shell find $(INCLUDE_DIR)/interfaces -type f -name "*.h")

#================================= CONTROLLER ==================================
CONTROLLER_CC         := $(shell find $(CONTROLLER_DIR) -type f -name "*.cc")
CONTROLLER_H          := $(shell find $(INCLUDE_DIR)/controller -type f -name "*.h")
CONTROLLER_O          := $(CONTROLLER_CC:$(CONTROLLER_DIR)/%.cc=$(OBJ_DIR)/controller/%.o)
CONTROLLER_O_COV      := $(CONTROLLER_CC:$(CONTROLLER_DIR)/%.cc=$(OBJ_DIR_COV)/controller/%.o)

#=========================== COMMAND LINE INTERFACE ============================
CLI_C                 := $(shell find $(CLI_DIR) -type f -name "*.c")
CLI_H                 := $(shell find $(INCLUDE_DIR)/gui/cli -type f -name "*.h")
CLI_O                 := $(CLI_C:$(CLI_DIR)/%.c=$(OBJ_DIR)/cli/%.o)
CLI_O_COV             := $(CLI_C:$(CLI_DIR)/%.c=$(OBJ_DIR_COV)/cli/%.o)

#======================= LIST OF FILES FOR STYLE CHECKS ========================
C_FILES               := $(TETRIS_C) $(COMMON_C) $(CLI_C)
CC_FILES              := $(WRAPPERS_CC) $(CONTROLLER_CC) $(SNAKE_CC)
HEADERS               := $(shell find $(INCLUDE_DIR) -type f -name "*.h")
ALL_FILES             := $(C_FILES) $(CC_FILES) $(HEADERS)

#============================== OBJECTIVE TARGETS ==============================
$(OBJ_DIR)/$(TETRIS)/%.o: $(TETRIS_DIR)/%.c $(TETRIS_H)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/common/%.o: $(COMMON_DIR)/%.c $(COMMON_H)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/wrappers/%.o: $(WRAPPERS_DIR)/%.cc $(WRAPPERS_H)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)/controller/%.o: $(CONTROLLER_DIR)/%.cc $(CONTROLLER_H)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)/cli/%.o: $(CLI_DIR)/%.c $(CLI_H)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/$(SNAKE)/%.o: $(SNAKE_DIR)/%.cc $(SNAKE_H)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

install: $(BIN_DIR) $(COMMON_LIB) $(WRAPPERS_LIB) $(TETRIS_LIB) $(CONTROLLER_LIB) $(CLI_LIB)
	$(CXX) $(CXXFLAGS) $(CLI) $(CONTROLLER_LIB) $(WRAPPERS_LIB) $(TETRIS_LIB) $(COMMON_LIB) $(CLI_LIB) $(LDGUI) -o $(BIN_CLI)
	$(BIN_DIR)/cli

1:
	@echo $(CLI_C)
	@echo
	@echo $(CLI_H)
	@echo
	@echo $(CLI_O)
	@echo
	@echo $(CLI_O_COV)

#=========================== STATIC LIBRARY BUILDING ===========================
$(TETRIS_LIB): $(OBJ_DIR)/$(TETRIS) $(TETRIS_O)
	ar rcs $@ $(TETRIS_O)
	ranlib $@

$(SNAKE_LIB): $(OBJ_DIR)/snake $(SNAKE_O)
	ar rcs $@ $(SNAKE_O)
	ranlib $@

$(COMMON_LIB): $(OBJ_DIR)/common $(COMMON_O)
	ar rcs $@ $(COMMON_O)
	ranlib $@

$(WRAPPERS_LIB): $(OBJ_DIR)/wrappers $(WRAPPERS_O)
	ar rcs $@ $(WRAPPERS_O)
	ranlib $@

$(CONTROLLER_LIB): $(OBJ_DIR)/controller $(CONTROLLER_O)
	ar rcs $@ $(CONTROLLER_O)
	ranlib $@


$(CLI_LIB): $(OBJ_DIR)/cli $(CLI_O)
	ar rcs $@ $(CLI_O)
	ranlib $@

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(OBJ_DIR_COV)
	rm -f $(TETRIS_LIB)
	rm -f $(COMMON_LIB)
	rm -f $(WRAPPERS_LIB)
	rm -f $(CONTROLLER_LIB)
	rm -f $(CLI_LIB)
	rm -f $(SNAKE_LIB)

#=================================== CHECKS ====================================
cpplint:
	cpplint $(HEADERS) $(CC_FILES)

clang:
	clang-format -style=Google -i $(ALL_FILES)

valgrind:
	valgrind $(VALGRIND) $(BIN_CLI)

#============================= CREATE DIRECTORIES ==============================
$(OBJ_DIR)/$(TETRIS):
	mkdir -p $(OBJ_DIR)/$(TETRIS)

$(OBJ_DIR)/common:
	mkdir -p $(OBJ_DIR)/common

$(OBJ_DIR)/wrappers:
	mkdir -p $(OBJ_DIR)/wrappers

$(OBJ_DIR)/controller:
	mkdir -p $(OBJ_DIR)/controller

$(OBJ_DIR)/cli:
	mkdir -p $(OBJ_DIR)/cli

$(OBJ_DIR)/snake:
	mkdir -p $(OBJ_DIR)/snake

$(OBJ_DIR_COV)/$(TETRIS):
	mkdir -p $(OBJ_DIR_COV)/$(TETRIS)

$(OBJ_DIR_COV)/common:
	mkdir -p $(OBJ_DIR_COV)/common

$(OBJ_DIR_COV)/wrappers:
	mkdir -p $(OBJ_DIR_COV)/wrappers

$(OBJ_DIR_COV)/controller:
	mkdir -p $(OBJ_DIR_COV)/controller

$(OBJ_DIR_COV)/cli:
	mkdir -p $(OBJ_DIR_COV)/cli

$(OBJ_DIR_COV)/snake:
	mkdir -p $(OBJ_DIR_COV)/snake

$(BIN_DIR):
	mkdir $(BIN_DIR)