#include "mainwindow.h"
#include <QPushButton>
#include <QLabel>
#include <QKeyEvent>
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>
#include <QFont>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Установка основных свойств окна
    setWindowTitle("TETRIS");
    setFixedSize(680, 700);

    // Центральный виджет с градиентным фоном (как в .ui)
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setStyleSheet(
        "background-color: qlineargradient(spread:pad, x1:0.512, y1:0.00568182, x2:0.517, y2:1, "
        "stop:0 rgba(170, 85, 255, 255), stop:1 rgba(145, 165, 255, 255));"
    );
    setCentralWidget(centralWidget);

    // Создание движка игры
    m_engine = new GameEngine(this);

    // Создание игрового поля и виджета следующей фигуры
    m_boardView = new BoardView(m_engine, centralWidget);
    m_boardView->setGeometry(230, 20, 300, 450); // 10x15 поле с ячейкой 30px

    m_nextPieceView = new NextPieceView(centralWidget);
    m_nextPieceView->setGeometry(550, 20, 110, 110);

    // Создание кнопки "pause"
    m_pauseButton = new QPushButton("pause", centralWidget);
    m_pauseButton->setGeometry(50, 50, 151, 41);
    QFont buttonFont("Yu Gothic Light", 18, QFont::Bold);
    m_pauseButton->setFont(buttonFont);
    m_pauseButton->setFocusPolicy(Qt::NoFocus);
    m_pauseButton->setStyleSheet(
        "QPushButton {"
        "  background-color: rgba(255, 255, 255, 200);"
        "  border: 2px solid #5c3a9e;"
        "  border-radius: 10px;"
        "  color: #2c1a4d;"
        "}"
        "QPushButton:hover {"
        "  background-color: rgba(255, 255, 255, 240);"
        "}"
        "QPushButton:pressed {"
        "  background-color: rgba(230, 230, 250, 255);"
        "}"
    );

    // Создание кнопки "restart"
    m_restartButton = new QPushButton("restart", centralWidget);
    m_restartButton->setGeometry(50, 110, 151, 41);
    m_restartButton->setFont(buttonFont);
    m_restartButton->setFocusPolicy(Qt::NoFocus);
    m_restartButton->setStyleSheet(m_pauseButton->styleSheet()); // тот же стиль

    // Создание надписи для счёта (замена QTextEdit на QLabel для удобства)
    m_scoreLabel = new QLabel("Score: 0", centralWidget);
    m_scoreLabel->setGeometry(50, 200, 151, 51);
    QFont scoreFont("Yu Gothic UI Light", 18, QFont::Bold);
    m_scoreLabel->setFont(scoreFont);
    m_scoreLabel->setAlignment(Qt::AlignCenter);
    m_scoreLabel->setFocusPolicy(Qt::NoFocus);
    m_scoreLabel->setStyleSheet(
        "QLabel {"
        "  background-color: rgba(255, 255, 255, 180);"
        "  border: none;"
        "  border-radius: 8px;"
        "  color: #1a1a2e;"
        "}"
    );

    // Настройка соединений сигналов и слотов
    connect(m_engine, &GameEngine::boardChanged,
            m_boardView, qOverload<>(&QWidget::update));
    connect(m_engine, &GameEngine::scoreChanged,
            this, &MainWindow::updateScoreLabel);
    connect(m_engine, &GameEngine::nextPieceChanged, this, [this]() {
        m_nextPieceView->setPiece(m_engine->nextPiece());
    });
    // connect(m_engine, &GameEngine::gameOver,
    //         this, &MainWindow::handleGameOver);

    connect(m_pauseButton, &QPushButton::clicked, this, [this]() {
        if (m_engine->isPaused()) {
            m_engine->resume();
            m_pauseButton->setText("pause");
        } else {
            m_engine->pause();
            m_pauseButton->setText("resume");
        }
    });

    connect(m_restartButton, &QPushButton::clicked,
            this, &MainWindow::restartGame);
    connect(m_engine, &GameEngine::gameOver,
            m_boardView, &BoardView::onGameOver);
    connect(m_engine, &GameEngine::gameStarted,
            m_boardView, &BoardView::onGameStarted);

    // Фокус для перехвата клавиш
    setFocusPolicy(Qt::StrongFocus);
    setFocus();

    // Запуск игры
    m_engine->start();
    m_nextPieceView->setPiece(m_engine->nextPiece());
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (m_engine->isGameOver())
        return;

    switch (event->key()) {
    case Qt::Key_Left:
        m_engine->moveLeft();
        break;
    case Qt::Key_Right:
        m_engine->moveRight();
        break;
    case Qt::Key_Up:
        m_engine->rotate();
        break;
    case Qt::Key_Down:
        m_engine->tick();
        break;
    case Qt::Key_Space:
        m_engine->drop();
        break;
    case Qt::Key_P:
        if (m_engine->isPaused()) {
            m_engine->resume();
            m_pauseButton->setText("pause");
        } else {
            m_engine->pause();
            m_pauseButton->setText("resume");
        }
        break;
    default:
        QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::handleGameOver()
{
    QMessageBox::information(this, "Game Over",
                             QString("Your score: %1").arg(m_engine->score()));
}

void MainWindow::updateScoreLabel(int score)
{
    m_scoreLabel->setText(QString("Score: %1").arg(score));
}

void MainWindow::restartGame()
{
    m_engine->start();
    m_nextPieceView->setPiece(m_engine->nextPiece());
    m_pauseButton->setText("pause");
    updateScoreLabel(m_engine->score());
}