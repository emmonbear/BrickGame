QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# C++ sources
CPP_SOURCES += \
    main.cpp \
    mainwindow.cpp \
    tetris_controller.cpp

# C sources
C_SOURCES += \
    ../../../brick_game/tetris/modules/init.c \
    ../../../brick_game/tetris/modules/figures.c \
    ../../../brick_game/tetris/modules/checks.c \
    ../../../brick_game/tetris/modules/operations.c

# Headers
HEADERS += \
    mainwindow.h \
    tetris_controller.h \
    tetris_view.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Compile C++ sources with g++
QMAKE_CXX = g++

# Compile C sources with gcc
QMAKE_CC = gcc

# Add C++ sources to the project
SOURCES += $$CPP_SOURCES \
  tetris_view.cpp

# Add C sources to the project
SOURCES += $$C_SOURCES

# Add necessary flags for C and C++ compilation
QMAKE_CFLAGS += -Wall -Wextra
QMAKE_CXXFLAGS += -Wall -Wextra
