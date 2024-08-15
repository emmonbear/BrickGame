#include "tetris_view.h"

TetrisView::TetrisView(TetrisController *controller, QWidget *parent)
    : QWidget{parent}, controller_{controller}
{

}

void TetrisView::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    draw_field(painter);
    draw_high_score(painter);
    draw_level(painter);
    draw_score(painter);
    draw_next(painter);
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

void TetrisView::draw_level(QPainter &painter) {
    QRect levelRect(kLevelX, kLevelY, kLevelWidth, kLevelHeight);

    painter.setBrush(QBrush(Qt::white));
    painter.drawRect(levelRect);

    QFont title_font("Arial", 22, QFont::Bold);
    painter.setFont(title_font);
    painter.setPen(QPen(Qt::black));

    painter.drawText(levelRect.adjusted(0, 0, 0, -levelRect.height() / 2), Qt::AlignCenter, "LEVEL");

    QFont font("Monospace", 28, QFont::Bold);
    font.setStyleHint(QFont::Monospace);
    painter.setFont(font);
    painter.setPen(QPen(Qt::black));

    int level = 1;
    painter.drawText(levelRect.adjusted(0, levelRect.height() / 2, 0, 0), Qt::AlignCenter, QString("%1").arg(level, 2));
}

void TetrisView::draw_field(QPainter &painter) {;
    Model_t *model = controller_->get_model();

    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            int value = model->game_info.field[i][j];
            QColor color = getColorForValue(value);
            painter.setBrush(color);
            painter.drawRect(j * kCellSize + kFieldX, i * kCellSize + kFieldY, kCellSize, kCellSize);
        }
    }
}

void TetrisView::draw_high_score(QPainter &painter) {
    QRect highScoreRect(kHighScoreX, kHighScoreY, kHighScoreWidth, kHighScoreHeight);

    painter.setBrush(QBrush(Qt::white));
    painter.drawRect(highScoreRect);


    QFont title_font("Arial", 22, QFont::Bold);
    painter.setFont(title_font);
    painter.setPen(QPen(Qt::black));

    painter.drawText(highScoreRect.adjusted(0, 0, 0, -highScoreRect.height() / 2), Qt::AlignCenter, "HIGH SCORE");

    QFont font("Monospace", 28, QFont::Bold);
    font.setStyleHint(QFont::Monospace);
    painter.setFont(font);
    painter.setPen(QPen(Qt::black));

    int high_score = 1234567;
    painter.drawText(highScoreRect.adjusted(0, highScoreRect.height() / 2, 0, 0), Qt::AlignCenter, QString("%1").arg(high_score, 6, 10, QChar('0')));
}

void TetrisView::draw_score(QPainter &painter) {
    QRect scoreRect(kScoreX, kScoreY, kScoreWidth, kScoreHeight);

    painter.setBrush(QBrush(Qt::white));
    painter.drawRect(scoreRect);

    QFont title_font("Arial", 22, QFont::Bold);
    painter.setFont(title_font);
    painter.setPen(QPen(Qt::black));

    painter.drawText(scoreRect.adjusted(0, 0, 0, -scoreRect.height() / 2), Qt::AlignCenter, "SCORE");

    QFont font("Monospace", 28, QFont::Bold);
    font.setStyleHint(QFont::Monospace);
    painter.setFont(font);
    painter.setPen(QPen(Qt::black));

    int score = 12345;
    painter.drawText(scoreRect.adjusted(0, scoreRect.height() / 2, 0, 0), Qt::AlignCenter, QString("%1").arg(score, 6, 10, QChar('0')));
}

void TetrisView::draw_next(QPainter &painter) {
    QRect next_rect(kNextX, kNextY, kNextWidth, kNextHeight);

    // Рисуем белый фон для секции "NEXT"
    painter.setBrush(QBrush(Qt::white));
    painter.drawRect(next_rect);

    QFont title_font("Arial", 22, QFont::Bold);
    painter.setFont(title_font);
    painter.setPen(QPen(Qt::black));

    painter.drawText(next_rect.adjusted(0, 0, 0, -(next_rect.height() - title_font.pointSize()) + kSpace), Qt::AlignCenter, "NEXT");

    Model_t *model = controller_->get_model();

    int offsetX = (kNextWidth - KTetrominoSize * kCellSize) / 2;
    int startY = kNextY + (title_font.pointSize() + kSpace);


    for (int i = 0; i < KTetrominoSize; ++i) {
        for (int j = 0; j < KTetrominoSize; ++j) {
            int value = model->game_info.next[i][j];
            QColor color = getColorForValue(value);
            painter.setBrush(color);

            QRect cellRect(j * kCellSize + kNextX + offsetX, i * kCellSize + startY + kSpace , kCellSize, kCellSize);
            painter.drawRect(cellRect);
        }
    }
}