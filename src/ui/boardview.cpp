#include "boardview.h"
#include <QPainter>
#include <QLinearGradient>

BoardView::BoardView(GameEngine *engine, QWidget *parent)
    : QWidget(parent)
    , m_engine(engine)
    , m_gameOver(false)
{
    setFixedSize(BOARD_WIDTH * CELL_SIZE, BOARD_HEIGHT * CELL_SIZE);
}

QSize BoardView::sizeHint() const
{
    return QSize(BOARD_WIDTH * CELL_SIZE, BOARD_HEIGHT * CELL_SIZE);
}

void BoardView::onGameOver()
{
    m_gameOver = true;
    update();  // перерисовка с оверлеем
}

void BoardView::onGameStarted()
{
    m_gameOver = false;
    update();  // перерисовка без оверлея
}

void BoardView::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(rect(), QColor(255, 255, 255, 50));

    // Сетка
    painter.setPen(QPen(Qt::lightGray, 1));
    for (int x = 0; x <= BOARD_WIDTH; ++x)
        painter.drawLine(x * CELL_SIZE, 0, x * CELL_SIZE, BOARD_HEIGHT * CELL_SIZE);
    for (int y = 0; y <= BOARD_HEIGHT; ++y)
        painter.drawLine(0, y * CELL_SIZE, BOARD_WIDTH * CELL_SIZE, y * CELL_SIZE);

    // Зафиксированные фигуры (цветные)
    Board *board = m_engine->board();
    for (int y = 0; y < BOARD_HEIGHT; ++y) {
        for (int x = 0; x < BOARD_WIDTH; ++x) {
            QColor cellColor = board->cellColor(x, y);
            if (cellColor.isValid()) {
                painter.fillRect(x * CELL_SIZE + 1, y * CELL_SIZE + 1,
                                 CELL_SIZE - 2, CELL_SIZE - 2, cellColor);
            }
        }
    }

    // Текущая падающая фигура (только если игра не окончена)
    if (!m_gameOver) {
        if (Piece *piece = m_engine->currentPiece()) {
            painter.setPen(Qt::NoPen);
            painter.setBrush(Tetromino::color(piece->type()));
            for (const QPoint &cell : piece->cells()) {
                int x = (piece->x() + cell.x()) * CELL_SIZE;
                int y = (piece->y() + cell.y()) * CELL_SIZE;
                if (y >= 0)
                    painter.drawRect(x + 1, y + 1, CELL_SIZE - 2, CELL_SIZE - 2);
            }
        }
    }

    // Оверлей Game Over
    if (m_gameOver) {
        // Градиентная заливка поля
        QLinearGradient gradient(0, 0, 0, height());
        gradient.setColorAt(0.0, QColor(255, 120, 0));  // оранжевый
        gradient.setColorAt(1.0, QColor(255, 0, 0));    // красный
        painter.fillRect(rect(), QBrush(gradient));

        // Текст
        QFont font = painter.font();
        font.setPointSize(30);
        font.setBold(true);
        painter.setFont(font);
        painter.setPen(QColor(100, 0, 0));

        QString gameOverText = "GAME OVER";
        QFontMetrics fm(font);
        int textWidth = fm.horizontalAdvance(gameOverText);
        int textHeight = fm.height();
        int x = (width() - textWidth) / 2;
        int y = height() / 2 - textHeight;
        painter.drawText(x, y, gameOverText);

        QString scoreText = QString("Score: %1").arg(m_engine->score());
        textWidth = fm.horizontalAdvance(scoreText);
        x = (width() - textWidth) / 2;
        y += textHeight + 20;
        painter.drawText(x, y, scoreText);
    }
}
