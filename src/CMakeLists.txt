cmake_minimum_required(VERSION 3.5)

project(desktop VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(VIEW_SOURCES
    ${CMAKE_SOURCE_DIR}/include/gui/desktop/main_window.h
    ${CMAKE_SOURCE_DIR}/include/gui/desktop/desktop_view.h
    ${CMAKE_SOURCE_DIR}/include/gui/desktop/scoreboard.h
    ${CMAKE_SOURCE_DIR}/gui/desktop/main_window.cc
    ${CMAKE_SOURCE_DIR}/gui/desktop/desktop_view.cc
    ${CMAKE_SOURCE_DIR}/gui/desktop/scoreboard.cc
)

set(TETRIS_C_SOURCES
    ${CMAKE_SOURCE_DIR}/include/tetris/figures.h
    ${CMAKE_SOURCE_DIR}/include/tetris/model.h
    ${CMAKE_SOURCE_DIR}/include/tetris/operations.h
    ${CMAKE_SOURCE_DIR}/include/tetris/types.h
    ${CMAKE_SOURCE_DIR}/brick_game/tetris/figures.c
    ${CMAKE_SOURCE_DIR}/brick_game/tetris/model.c
    ${CMAKE_SOURCE_DIR}/brick_game/tetris/operations.c
)

set(CONTROLLER_SOURCES
    ${CMAKE_SOURCE_DIR}/include/controller/controller.h
    ${CMAKE_SOURCE_DIR}/controller/controller.cc
)

set(SNAKE_SOURCES
    ${CMAKE_SOURCE_DIR}/include/snake/snake_model.h
    ${CMAKE_SOURCE_DIR}/brick_game/snake/snake_model.cc
)

set(TETRIS_SOURCES
    ${CMAKE_SOURCE_DIR}/include/wrappers/tetris_model.h
    ${CMAKE_SOURCE_DIR}/wrappers/tetris_model.cc
)

set(COMMON_SOURCES
    ${CMAKE_SOURCE_DIR}/include/common/common.h
    ${CMAKE_SOURCE_DIR}/include/common/game_info.h 
    ${CMAKE_SOURCE_DIR}/common/common.c
)

set(INTERFACES_SOURCES
    ${CMAKE_SOURCE_DIR}/include/interfaces/IModel.h
)

set(MAIN_SOURCES
    ${VIEW_SOURCES} ${CONTROLLER_SOURCES} ${SNAKE_SOURCES} 
    ${INTERFACES_SOURCES} ${TETRIS_SOURCES} ${TETRIS_C_SOURCES}
    ${COMMON_SOURCES} ${CMAKE_SOURCE_DIR}/app/desktop.cc
)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(desktop
    MANUAL_FINALIZATION
    ${MAIN_SOURCES}
)
else()
    add_executable(desktop
    ${MAIN_SOURCES}
)
endif()

target_link_libraries(desktop PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core)

set_target_properties(desktop PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS desktop
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(desktop)
endif()
