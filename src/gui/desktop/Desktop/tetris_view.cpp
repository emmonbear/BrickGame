#include "tetris_view.h"

TetrisView::TetrisView(TetrisController *controller, QWidget *parent)
    : QWidget{parent}, controller_{controller}
{

}

void TetrisView::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    const int cellSize = 30;
    
    Model_t *model = controller_->get_model();

    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            int value = model->game_info.field[i][j];
            QColor color = getColorForValue(value);
            painter.setBrush(color);
            painter.drawRect(j * cellSize, i * cellSize, cellSize, cellSize);
        }
    }
}

QColor TetrisView::getColorForValue (int value) const {
    switch(value) {
        case 0:
            return Qt::white;
        case 1:
            return Qt::red;
        case 2:
            return Qt::green;
        case 3:
            return Qt::yellow;
        case 4:
            return Qt::cyan;
        case 5:
            return Qt::magenta;
        case 6:
            return Qt::darkGray;
        case 7:
            return Qt::darkRed;
        default:
            return Qt::black;
    }
}
