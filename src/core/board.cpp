#include "board.h"

Board::Board()
{
    clear();
}

bool Board::isCellEmpty(int x, int y) const
{
    if (x < 0 || x >= BOARD_WIDTH || y < 0 || y >= BOARD_HEIGHT)
        return false;
    return !m_grid[y][x].isValid();
}

void Board::setCell(int x, int y, const QColor &color)
{
    if (x >= 0 && x < BOARD_WIDTH && y >= 0 && y < BOARD_HEIGHT)
        m_grid[y][x] = color;
}

QColor Board::cellColor(int x, int y) const
{
    if (x >= 0 && x < BOARD_WIDTH && y >= 0 && y < BOARD_HEIGHT)
        return m_grid[y][x];
    return QColor();
}

bool Board::isLineFull(int y) const
{
    for (int x = 0; x < BOARD_WIDTH; ++x) {
        if (!m_grid[y][x].isValid())   // если есть хотя бы одна пустая ячейка
            return false;
    }
    return true;
}

void Board::clearLine(int y)
{
    for (int row = y; row > 0; --row)
        m_grid[row] = m_grid[row - 1];
    m_grid[0].fill(QColor());   // верхняя строка очищается
}

void Board::clear()
{
    for (auto &row : m_grid)
        row.fill(QColor());
}