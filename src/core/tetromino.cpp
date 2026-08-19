#include "tetromino.h"

std::array<QPoint, 4> Tetromino::cells(TetrominoType type, int rotation)
{
    rotation = ((rotation % 4) + 4) % 4; // нормализация поворота

    switch (type) {
    case TetrominoType::I:
        if (rotation == 0 || rotation == 2)
            return { QPoint(0,0), QPoint(1,0), QPoint(2,0), QPoint(3,0) };
        else
            return { QPoint(0,0), QPoint(0,1), QPoint(0,2), QPoint(0,3) };

    case TetrominoType::O:
        return { QPoint(0,0), QPoint(1,0), QPoint(0,1), QPoint(1,1) };

    case TetrominoType::T:
        switch (rotation) {
        case 0: return { QPoint(0,0), QPoint(1,0), QPoint(2,0), QPoint(1,1) };
        case 1: return { QPoint(1,0), QPoint(0,1), QPoint(1,1), QPoint(1,2) };
        case 2: return { QPoint(1,0), QPoint(0,1), QPoint(1,1), QPoint(2,1) };
        case 3: return { QPoint(0,0), QPoint(0,1), QPoint(0,2), QPoint(1,1) };
        }
        break;

    case TetrominoType::S:
        if (rotation == 0 || rotation == 2)
            return { QPoint(1,0), QPoint(2,0), QPoint(0,1), QPoint(1,1) };
        else
            return { QPoint(0,0), QPoint(0,1), QPoint(1,1), QPoint(1,2) };

    case TetrominoType::Z:
        if (rotation == 0 || rotation == 2)
            return { QPoint(0,0), QPoint(1,0), QPoint(1,1), QPoint(2,1) };
        else
            return { QPoint(1,0), QPoint(0,1), QPoint(1,1), QPoint(0,2) };

    case TetrominoType::J:
        switch (rotation) {
        case 0: return { QPoint(0,0), QPoint(0,1), QPoint(1,1), QPoint(2,1) };
        case 1: return { QPoint(0,0), QPoint(1,0), QPoint(0,1), QPoint(0,2) };
        case 2: return { QPoint(0,0), QPoint(1,0), QPoint(2,0), QPoint(2,1) };
        case 3: return { QPoint(1,0), QPoint(1,1), QPoint(1,2), QPoint(0,2) };
        }
        break;

    case TetrominoType::L:
        switch (rotation) {
        case 0: return { QPoint(2,0), QPoint(0,1), QPoint(1,1), QPoint(2,1) };
        case 1: return { QPoint(0,0), QPoint(0,1), QPoint(0,2), QPoint(1,2) };
        case 2: return { QPoint(0,0), QPoint(1,0), QPoint(2,0), QPoint(0,1) };
        case 3: return { QPoint(0,0), QPoint(1,0), QPoint(1,1), QPoint(1,2) };
        }
        break;
    }
    return {};
}

QColor Tetromino::color(TetrominoType type)
{
    switch (type) {
    case TetrominoType::I: return QColor(0, 255, 255);
    case TetrominoType::O: return QColor(255, 255, 0);
    case TetrominoType::T: return QColor(160, 32, 240);
    case TetrominoType::S: return QColor(0, 255, 0);
    case TetrominoType::Z: return QColor(255, 0, 0);
    case TetrominoType::J: return QColor(0, 0, 255);
    case TetrominoType::L: return QColor(255, 165, 0);
    }
    return QColor(Qt::white);
}