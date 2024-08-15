#include "mainwindow.h"
#include "tetris_controller.h"
#include "tetris_view.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(MainWindow::kHeight, MainWindow::kWidth);
    w.show();
    return a.exec();
}
