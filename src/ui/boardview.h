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

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    GameEngine *m_engine;
    bool m_gameOver;
    static constexpr int CELL_SIZE = 30;
};