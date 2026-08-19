#include "piece.h"

Piece::Piece(TetrominoType type, int rotation)
    : m_type(type)
    , m_rotation(rotation)
    , m_x(0)
    , m_y(0)
{
    m_cells = Tetromino::cells(type, rotation);
}

TetrominoType Piece::type() const
{
    return m_type;
}

int Piece::rotation() const
{
    return m_rotation;
}

const std::array<QPoint, 4>& Piece::cells() const
{
    return m_cells;
}

void Piece::move(int dx, int dy)
{
    m_x += dx;
    m_y += dy;
}

void Piece::rotateLeft()
{
    m_rotation = (m_rotation + 3) % 4;
    m_cells = Tetromino::cells(m_type, m_rotation);
}

void Piece::rotateRight()
{
    m_rotation = (m_rotation + 1) % 4;
    m_cells = Tetromino::cells(m_type, m_rotation);
}

int Piece::x() const
{
    return m_x;
}

int Piece::y() const
{
    return m_y;
}

void Piece::setPosition(int x, int y)
{
    m_x = x;
    m_y = y;
}

int Piece::width() const
{
    int minX = 0, maxX = 0;
    for (const QPoint &cell : m_cells) {
        minX = std::min(minX, cell.x());
        maxX = std::max(maxX, cell.x());
    }
    return maxX - minX + 1;
}

int Piece::height() const
{
    int minY = 0, maxY = 0;
    for (const QPoint &cell : m_cells) {
        minY = std::min(minY, cell.y());
        maxY = std::max(maxY, cell.y());
    }
    return maxY - minY + 1;
}