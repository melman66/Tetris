#include "mainwindow.h"
#include <QKeyEvent>
#include <QFont>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_centralWidget (new QWidget(this))
    , m_engine      (new GameEngine(this))
    , m_boardView   (new BoardView(m_engine, m_centralWidget))
    , m_nextPieceView(new NextPieceView(m_centralWidget))
    , m_pauseButton (new QPushButton("pause", m_centralWidget))
    , m_restartButton(new QPushButton("restart", m_centralWidget))
    , m_scoreLabel   (new QLabel("Score: 0", m_centralWidget))
    , m_levelLabel   (new QLabel("Level: 1", m_centralWidget))

{
    setupUi();
    applyStyles();
    connectSignals();

    // Запуск игры
    m_engine->start();
    m_nextPieceView->setPiece(m_engine->nextPiece());

    setFocusPolicy(Qt::StrongFocus);
    setFocus();
}

void MainWindow::setupUi()
{
    // Основные свойства окна
    setWindowTitle("TETRIS");
    setFixedSize(680, 500);

    // Центральный виджет с градиентным фоном
    m_centralWidget->setObjectName("centralWidget");
    setCentralWidget(m_centralWidget);

    // Игровое поле (BoardView)
    m_boardView->setObjectName("boardView");
    m_boardView->move(190, 20);

    // Виджет следующей фигуры
    m_nextPieceView->setObjectName("nextPieceView");
    m_nextPieceView->move(520, 20);

    // Кнопка "pause"
    m_pauseButton->setObjectName("pauseButton");
    m_pauseButton->setGeometry(20, 50, 151, 41);
    m_pauseButton->setFocusPolicy(Qt::NoFocus);

    // Кнопка "restart"
    m_restartButton->setObjectName("restartButton");
    m_restartButton->setGeometry(20, 110, 151, 41);
    m_restartButton->setFocusPolicy(Qt::NoFocus);

    // Надпись для счёта
    m_scoreLabel->setObjectName("scoreLabel");
    m_scoreLabel->setGeometry(20, 200, 151, 51);
    m_scoreLabel->setAlignment(Qt::AlignCenter);
    m_scoreLabel->setFocusPolicy(Qt::NoFocus);

    // Надпись для уровня
    m_levelLabel->setObjectName("levelLabel");
    m_levelLabel->setGeometry(20, 270, 151, 51);
    m_levelLabel->setAlignment(Qt::AlignCenter);
    m_levelLabel->setFocusPolicy(Qt::NoFocus);
}

void MainWindow::applyStyles()
{
    // Стиль центрального виджета
    QWidget *central = centralWidget();
    if (central) {
        central->setStyleSheet(
            "background-color: qlineargradient(spread:pad, x1:0.512, y1:0.00568182, x2:0.517, y2:1, "
            "stop:0 rgba(170, 85, 255, 255), stop:1 rgba(145, 165, 255, 255));"
        );
    }

    // Стиль кнопок
    const QString buttonStyle = QString(
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
    m_pauseButton->setStyleSheet(buttonStyle);
    m_restartButton->setStyleSheet(buttonStyle);

    // Шрифт для кнопок
    QFont buttonFont("Yu Gothic Light", 18, QFont::Bold);
    m_pauseButton->setFont(buttonFont);
    m_restartButton->setFont(buttonFont);

    // Стиль надписи счёта и уровня
    const QString scoreAndLevelStyle(
                "QLabel {"
                "  background-color: rgba(255, 255, 255, 180);"
                "  border: none;"
                "  border-radius: 8px;"
                "  color: #1a1a2e;"
                "}"
                );

    m_scoreLabel->setStyleSheet(scoreAndLevelStyle);
    m_levelLabel->setStyleSheet(scoreAndLevelStyle);

    QFont scoreAndLevelFont("Yu Gothic UI Light", 18, QFont::Bold);
    m_scoreLabel->setFont(scoreAndLevelFont);
    m_levelLabel->setFont(scoreAndLevelFont);
}

void MainWindow::connectSignals()
{
    // Обновление поля при изменении состояния игры
    connect(m_engine, &GameEngine::boardChanged,
            m_boardView, qOverload<>(&QWidget::update));

    // Обновление счёта
    connect(m_engine, &GameEngine::scoreChanged,
            this, &MainWindow::updateScoreLabel);

    // Обновление уровня
    connect(m_engine, &GameEngine::levelChanged,
            this, &MainWindow::updateLevelLabel);

    // Обновление виджета следующей фигуры
    connect(m_engine, &GameEngine::nextPieceChanged, this, [this]() {
        m_nextPieceView->setPiece(m_engine->nextPiece());
    });

    // Оверлей Game Over
    connect(m_engine, &GameEngine::gameOver,
            m_boardView, &BoardView::onGameOver);
    connect(m_engine, &GameEngine::gameStarted,
            m_boardView, &BoardView::onGameStarted);

    // Кнопки
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

void MainWindow::updateScoreLabel(int score)
{
    m_scoreLabel->setText(QString("Score: %1").arg(score));
}

void MainWindow::updateLevelLabel(int level)
{
    m_levelLabel->setText(QString("Level: %1").arg(level));
}

void MainWindow::restartGame()
{
    m_engine->start();
    m_nextPieceView->setPiece(m_engine->nextPiece());
    m_pauseButton->setText("pause");
    updateScoreLabel(m_engine->score());
}