#include "nextpieceview.h"
#include <QPainter>

NextPieceView::NextPieceView(QWidget *parent)
    : QWidget(parent)
    , m_piece(nullptr)
{
    // Размер как в исходном .ui (150x190)
    setFixedSize(150, 190);
}

void NextPieceView::setPiece(const Piece *piece)
{
    m_piece = piece;
    update();
}

void NextPieceView::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(rect(), QColor(240, 240, 240));

    if (!m_piece)
        return;

    const auto &cells = m_piece->cells();

    // Вычисляем границы фигуры
    int minX = 0, maxX = 0, minY = 0, maxY = 0;
    for (const QPoint &cell : cells) {
        minX = std::min(minX, cell.x());
        maxX = std::max(maxX, cell.x());
        minY = std::min(minY, cell.y());
        maxY = std::max(maxY, cell.y());
    }
    int pieceW = (maxX - minX + 1) * CELL_SIZE;
    int pieceH = (maxY - minY + 1) * CELL_SIZE;

    // Центрируем
    int offsetX = (width() - pieceW) / 2 - minX * CELL_SIZE;
    int offsetY = (height() - pieceH) / 2 - minY * CELL_SIZE;

    painter.setPen(Qt::NoPen);
    painter.setBrush(Tetromino::color(m_piece->type()));
    for (const QPoint &cell : cells) {
        painter.drawRect(offsetX + cell.x() * CELL_SIZE + 1,
                         offsetY + cell.y() * CELL_SIZE + 1,
                         CELL_SIZE - 2, CELL_SIZE - 2);
    }
}