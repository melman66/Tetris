#pragma once

#include <QWidget>
#include "../core/gameengine.h"

class BoardView : public QWidget
{
    Q_OBJECT

public:
    explicit BoardView(GameEngine *engine, QWidget *parent = nullptr);

    QSize sizeHint() const override;

public slots:
    void onGameOver();      // вызывается при окончании игры
    void onGameStarted();   // вызывается при старте новой игры
    void onPause();         // вызывается при паузе

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void drawGrid(QPainter &painter);
    void drawLockedCells(QPainter &painter);
    void drawCurrentPiece(QPainter &painter);
    void drawGameOverOverlay(QPainter &painter);
    void drawPauseOverlay(QPainter &painter);

    GameEngine *m_engine;
    bool m_gameOver;
    bool m_pause;
    static constexpr int CELL_SIZE = 30;
};