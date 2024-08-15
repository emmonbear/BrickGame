#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tetris_view.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->startTetris, &QPushButton::clicked, this, &MainWindow::on_startTetris_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_startTetris_clicked()
{
    TetrisController *controller = new TetrisController();
    TetrisView *tetrisView = new TetrisView(controller);

    setCentralWidget(tetrisView);

    tetrisView->setFocus();
    resize(kHeight, kWidth);
}

