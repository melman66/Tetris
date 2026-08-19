#pragma once

#include "tetromino.h"
#include <QPoint>
#include <array>

class Piece
{
public:
    Piece(TetrominoType type, int rotation = 0);

    TetrominoType type() const;
    int rotation() const;
    const std::array<QPoint, 4>& cells() const;

    void move(int dx, int dy);
    void rotateLeft();
    void rotateRight();

    int x() const;
    int y() const;
    void setPosition(int x, int y);

    int width() const;
    int height() const;

private:
    TetrominoType m_type;
    int m_rotation;
    int m_x;
    int m_y;
    std::array<QPoint, 4> m_cells;
};