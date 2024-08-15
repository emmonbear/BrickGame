#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static constexpr int kHeight = 800;
    static constexpr int kWidth = 700;


    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_startTetris_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
