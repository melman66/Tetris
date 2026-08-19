#pragma once

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include "../core/gameengine.h"
#include "boardview.h"
#include "nextpieceview.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void updateScoreLabel(int score);
    void updateLevelLabel(int level);
    void restartGame();

private:
    void setupUi();
    void applyStyles();
    void connectSignals();

    QWidget *m_centralWidget;
    GameEngine *m_engine;
    BoardView *m_boardView;
    NextPieceView *m_nextPieceView;
    QLabel *m_scoreLabel;
    QLabel *m_levelLabel;
    QPushButton *m_pauseButton;
    QPushButton *m_restartButton;
};