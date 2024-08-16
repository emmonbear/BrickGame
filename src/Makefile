#================================ PROJECT NAME =================================
PROJECT_NAME          := brick_game

#================================== FILENAMES ==================================
CLI                   := $(PROJECT_NAME)_cli
MAX_SCORE_FILE        := $(PROJECT_NAME)/tetris/max_score.txt
DIST_ARCHIVE          := $(DIST_DIR)/$(PROJECT_NAME).tar.gz

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

#=============================== TARGET NAMES =================================
MODEL_LIB             := model.a
VIEW_LIB              := view.a
CONTROLLER_LIB        := controller.a
COMMON_LIB            := common.a
TEST                  := test
GCOV                  := gcov_report
DVI                   := dvi

#=============================== DIRECTORY NAMES ===============================
MODEL_DIR             := ./brick_game/tetris
VIEW_DIR              := ./gui/cli
CONTROLLER_DIR        := ./controller/tetris
COMMON_DIR            := ./common
OBJ_DIR               := ./obj
OBJ_DIR_COV           := ./obj_cov
REPORT_DIR            := ./report
TESTS_DIR             := ./tests
DOCS_DIR              := ../docs
BIN_DIR               := ../bin
DIST_DIR              := ../dist

#================================== FILE LIST ==================================
MAIN                  := $(PROJECT_NAME).cc
MAIN_TEST             := $(TESTS_DIR)/main_test.cc

#=================================== COMMON ====================================
COMMON_C              := $(shell find $(COMMON_DIR) -type f -name "*.c")
COMMON_H              := $(shell find $(COMMON_DIR) -type f -name "*.h")
COMMON_O              := $(COMMON_C:$(COMMON_DIR)/modules/%.c=$(OBJ_DIR)/common/%.o)

#=============================== TETRIS CLI VIEW ===============================
VIEW_C                := $(shell find $(VIEW_DIR) -type f -name "*.c")
VIEW_H                := $(shell find $(VIEW_DIR) -type f -name "*.h")
VIEW_O                := $(VIEW_C:$(VIEW_DIR)/modules/%.c=$(OBJ_DIR)/tetris/view/%.o)
VIEW_O_COV            := $(VIEW_C:$(VIEW_DIR)/modules/%.c=$(OBJ_DIR_COV)/tetris/view/%.o)

#================================ TETRIS MODEL =================================
MODEL_C               := $(shell find $(MODEL_DIR) -type f -name "*.c")
MODEL_H               := $(shell find $(MODEL_DIR) -type f -name "*.h")
MODEL_O               := $(MODEL_C:$(MODEL_DIR)/modules/%.c=$(OBJ_DIR)/tetris/model/%.o)
MODEL_O_COV           := $(MODEL_C:$(MODEL_DIR)/modules/%.c=$(OBJ_DIR_COV)/tetris/model/%.o)

#============================== TETRIS CONTROLLER ==============================
CONTROLLER_C          := $(shell find $(CONTROLLER_DIR) -type f -name "*.c")
CONTROLLER_H          := $(shell find $(CONTROLLER_DIR) -type f -name "*.h")
CONTROLLER_O          := $(CONTROLLER_C:$(CONTROLLER_DIR)/modules/%.c=$(OBJ_DIR)/tetris/controller/%.o)
CONTROLLER_O_COV      := $(CONTROLLER_C:$(CONTROLLER_DIR)/modules/%.c=$(OBJ_DIR_COV)/tetris/controller/%.o)

#================================= TESTS FILES =================================
TEST_CC               := $(shell find $(TESTS_DIR)/modules -type f -name "*.cc")
TEST_H                := $(shell find $(TESTS_DIR) -type f -name "*.h")
TEST_O                := $(TEST_CC:$(TESTS_DIR)/modules/%.cc=$(OBJ_DIR)/tests/%.o)
TEST_O_COV            := $(TEST_CC:$(TESTS_DIR)/modules/%.cc=$(OBJ_DIR_COV)/tests/%.o)

#======================= LIST OF FILES FOR STYLE CHECKS ========================
C_FILES               := $(VIEW_C) $(MODEL_C) $(CONTROLLER_C) $(COMMON_O)
H_FILES               := $(VIEW_H) $(MODEL_H) $(CONTROLLER_H) $(COMMON_H)
CC_FILES              := $(MAIN) $(MAIN_TEST) $(TEST_CC)
ALL_FILES             := $(C_FILES) $(H_FILES) $(CC_FILES) $(TEST_H)

#============================== OBJECTIVE TARGETS ==============================
$(OBJ_DIR)/tetris/model/%.o: $(MODEL_DIR)/modules/%.c $(MODEL_H) $(COMMON_H)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/tetris/view/%.o: $(VIEW_DIR)/modules/%.c $(VIEW_H)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/tetris/controller/%.o: $(CONTROLLER_DIR)/modules/%.c $(CONTROLLER_H)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/tests/%.o: $(TESTS_DIR)/modules/%.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)/common/%.o: $(COMMON_DIR)/modules/%.c $(COMMON_H)
	$(CC) $(CFLAGS) -c -o $@ $<
 
$(OBJ_DIR_COV)/tetris/model/%.o: $(MODEL_DIR)/modules/%.c $(MODEL_H) $(COMMON_H)
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) -c -o $@ $<

$(OBJ_DIR_COV)/tetris/view/%.o: $(VIEW_DIR)/modules/%.c $(VIEW_H)
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) -c -o $@ $<

$(OBJ_DIR_COV)/tetris/controller/%.o: $(CONTROLLER_DIR)/modules/%.c $(CONTROLLER_H)
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) -c -o $@ $<

$(OBJ_DIR_COV)/tests/%.o: $(TESTS_DIR)/modules/%.cc
	$(CXX) $(CXXFLAGS) $(COVERAGE_FLAGS) -c -o $@ $<

#=================================== TARGETS ===================================
.PHONY: all install run clean $(MODEL_LIB) $(VIEW_LIB) $(CONTROLLER_LIB) \
				preferences $(GCOV) $(TEST) $(DVI) $(DIST)

m: install_desk
	./gui/desktop/Desktop/build/Desktop

all: install run

install: $(BIN_DIR) $(COMMON_LIB) $(MODEL_LIB) $(VIEW_LIB) $(CONTROLLER_LIB)
	$(CXX) $(CXXFLAGS) $(MAIN) $(CONTROLLER_LIB) $(MODEL_LIB) $(COMMON_LIB) $(VIEW_LIB) $(LDGUI) -o $(BIN_DIR)/$(CLI)

install_desk:
	rm -rf ./gui/desktop/build
	mkdir -p ./gui/desktop/Desktop/build
	cd ./gui/desktop/Desktop/build && qmake ..
	cd ./gui/desktop/Desktop/build && make

uninstall: clean
	rm -f $(MAX_SCORE_FILE)
	rm -rf $(BIN_DIR)
	rm -rf $(DOCS_DIR)
	rm -rf $(DIST_DIR)
	rm -rf $(REPORT_DIR)

run:
	$(BIN_DIR)/$(CLI)

	
#=========================== STATIC LIBRARY BUILDING ===========================
$(MODEL_LIB): $(OBJ_DIR) $(MODEL_O)
	ar rcs $@ $(MODEL_O)
	ranlib $@

$(VIEW_LIB): $(OBJ_DIR) $(VIEW_O)
	ar rcs $@ $(VIEW_O)
	ranlib $@

$(CONTROLLER_LIB): $(OBJ_DIR) $(CONTROLLER_O)
	ar rcs $@ $(CONTROLLER_O)
	ranlib $@

$(COMMON_LIB): $(OBJ_DIR) $(COMMON_O)
	ar rcs $@ $(COMMON_O)
	ranlib $@

#================================= TESTS START =================================
$(TEST): $(OBJ_DIR) $(COMMON_O) $(MODEL_O) $(VIEW_O) $(CONTROLLER_O) $(TEST_O)
	$(CXX) $(MAIN_TEST) $(TEST_O) $(COMMON_O) $(MODEL_O) $(VIEW_O) $(CONTROLLER_O) $(LDFLAGS) $(LDGUI) -o $@
	./$@

val:
	valgrind $(BIN_DIR)/$(CLI)

val_test:
	valgrind $(VALGRIND) ./$(TEST)

preferences:
	sudo apt install libgtest-dev

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(OBJ_DIR_COV)
	rm -f $(VIEW_LIB)
	rm -f $(MODEL_LIB)
	rm -f $(CONTROLLER_LIB)
	rm -f $(TEST)
	rm -rf ./gui/desktop/BrickGame/build

#================================= GCOV REPORT =================================
GCOVR_EXCLUDES := --exclude='.*gui/cli/.*|.*tests/.*'
GCOVR_HTML := -r . $(GCOVR_EXCLUDES) --html --html-details -o $(REPORT_DIR)/coverage.html 
GCOVR_TXT := -r . $(GCOVR_EXCLUDES) --txt -o $(REPORT_DIR)/coverage.txt 

gcov_report: $(REPORT_DIR) $(OBJ_DIR_COV) $(MODEL_O_COV) $(VIEW_O_COV) $(CONTROLLER_O_COV) $(TEST_O_COV)
	$(CXX) $(MAIN_TEST) $(TEST_O_COV) $(MODEL_O_COV) $(VIEW_O_COV) $(CONTROLLER_O_COV) $(LDFLAGS) $(LDGUI) $(COVERAGE_FLAGS) -o $(OBJ_DIR_COV)/tests/gcov_report
	./$(OBJ_DIR_COV)/tests/gcov_report
	gcovr $(GCOVR_HTML)
	gcovr $(GCOVR_TXT)
	@echo
	@echo
	@cat $(REPORT_DIR)/coverage.txt

gcov_open:
	xdg-open $(REPORT_DIR)/coverage.html

#================================ STYLE CHECKS =================================
clang_fix:
	clang-format -style=Google -i $(ALL_FILES)

clang_check:
	clang-format -style=Google -n $(ALL_FILES)

cpplint:
	cpplint $(CC_FILES)

#================================= DIST TARGET =================================
dist: clean $(DIST_DIR)
	tar -czf $(DIST_ARCHIVE) -C ../ .

#=========================== GENERATE DOCUMENTATION ============================
$(DVI): 
	rm -rf $(DOCS_DIR)
	doxygen Doxyfile

$(DVI)_open:
	xdg-open $(DOCS_DIR)/html/index.html

#============================= CREATE DIRECTORIES ==============================
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)/tetris/model
	mkdir -p $(OBJ_DIR)/tetris/view
	mkdir -p $(OBJ_DIR)/tetris/controller
	mkdir -p $(OBJ_DIR)/tests
	mkdir -p $(OBJ_DIR)/common

$(OBJ_DIR_COV):
	mkdir -p $(OBJ_DIR_COV)/tetris/model
	mkdir -p $(OBJ_DIR_COV)/tetris/view
	mkdir -p $(OBJ_DIR_COV)/tetris/controller
	mkdir -p $(OBJ_DIR_COV)/tests


$(REPORT_DIR):
	mkdir -p $(REPORT_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(DIST_DIR):
	mkdir -p $(DIST_DIR)

$(DOCS_DIR):
	mkdir -p $(DOCS_DIR)
