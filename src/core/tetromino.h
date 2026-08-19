#pragma once

#include <QColor>
#include <QPoint>
#include <array>

// Типы фигур тетрамино
enum class TetrominoType { I, O, T, S, Z, J, L };

class Tetromino
{
public:
    // Возвращает массив из 4 относительных координат (0..3)
    // для заданного типа и поворота (0-3)
    static std::array<QPoint, 4> cells(TetrominoType type, int rotation);
    static QColor color(TetrominoType type);
};