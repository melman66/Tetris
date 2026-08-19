#pragma once

#include <array>
#include <QColor>

constexpr int BOARD_WIDTH = 10;
constexpr int BOARD_HEIGHT = 15;

class Board
{
public:
    Board();

    bool isCellEmpty(int x, int y) const;
    void setCell(int x, int y, const QColor &color);
    QColor cellColor(int x, int y) const;
    bool isLineFull(int y) const;
    void clearLine(int y);
    void clear();

private:
    std::array<std::array<QColor, BOARD_WIDTH>, BOARD_HEIGHT> m_grid;
};