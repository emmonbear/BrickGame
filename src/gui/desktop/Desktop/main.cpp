#include "mainwindow.h"
#include "tetris_controller.h"
#include "tetris_view.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TetrisController controller;

    TetrisView view(&controller);
    view.setFixedSize(400, 800); // Устанавливаем фиксированный размер окна
    view.show();
//    MainWindow w;
//    w.show();
    return a.exec();
}
