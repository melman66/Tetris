#pragma once

#include <QObject>
#include <QTimer>
#include <memory>
#include "board.h"
#include "piece.h"
#include "tetromino.h"

class GameEngine : public QObject
{
    Q_OBJECT

public:
    explicit GameEngine(QObject *parent = nullptr);

    void start();
    void pause();
    void resume();

    void moveLeft();
    void moveRight();
    void rotate();
    void drop();
    void tick();  // один шаг вниз

    Board* board() const;
    Piece* currentPiece() const;
    Piece* nextPiece() const;
    int score() const;
    bool isGameOver() const;
    bool isPaused() const;

signals:
    void boardChanged();             // требуется перерисовка поля
    void scoreChanged(int score);    // изменился счёт
    void levelChanged(int level);    // изменился уровень
    void nextPieceChanged();         // изменилась следующая фигура
    void gameOver();                 // игра окончена
    void gameStarted();              // новая игра началась

private:
    void spawnNewPiece();
    bool canPlacePiece(const Piece &piece, int dx = 0, int dy = 0) const;
    void lockCurrentPiece();
    void clearFullLines();
    int newTime();

    Board m_board;
    std::unique_ptr<Piece> m_currentPiece;
    std::unique_ptr<Piece> m_nextPiece;
    int m_score;
    bool m_gameOver;
    bool m_paused;
    QTimer m_timer;
    int m_level;
};