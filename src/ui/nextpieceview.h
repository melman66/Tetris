#pragma once

#include <QWidget>
#include "../core/piece.h"

class NextPieceView : public QWidget
{
    Q_OBJECT

public:
    explicit NextPieceView(QWidget *parent = nullptr);
    void setPiece(const Piece *piece);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    const Piece *m_piece;
    static constexpr int CELL_SIZE = 20;
};