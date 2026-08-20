#include "gameengine.h"
#include <QRandomGenerator>
#include <QDebug>

GameEngine::GameEngine(QObject *parent)
    : QObject(parent)
    , m_score(0)
    , m_gameOver(false)
    , m_paused(false)
    , m_level(1)
{
    connect(&m_timer, &QTimer::timeout, this, &GameEngine::tick);
}

void GameEngine::start()
{
    m_board.clear();
    m_score = 0;
    m_gameOver = false;
    m_paused = false;
    m_timer.stop();

    // Создаём первую следующую фигуру
    TetrominoType type = static_cast<TetrominoType>(
        QRandomGenerator::global()->bounded(7));
    m_nextPiece = std::make_unique<Piece>(type);

    spawnNewPiece();

    emit scoreChanged(m_score);
    emit nextPieceChanged();
    emit boardChanged();
    emit gameStarted();   // уведомляем о старте новой игры

    m_timer.start(newTime());   // интервал падения
}

void GameEngine::pause()
{
    if (!m_gameOver && !m_paused) {
        m_paused = true;
        m_timer.stop();
        emit pauseChanged();
    }
}

void GameEngine::resume()
{
    if (!m_gameOver && m_paused) {
        m_paused = false;
        m_timer.start(newTime());
        emit pauseChanged();
    }
}

void GameEngine::moveLeft()
{
    if (!m_gameOver && !m_paused && m_currentPiece) {
        if (canPlacePiece(*m_currentPiece, -1, 0)) {
            m_currentPiece->move(-1, 0);
            emit boardChanged();
        }
    }
}

void GameEngine::moveRight()
{
    if (!m_gameOver && !m_paused && m_currentPiece) {
        if (canPlacePiece(*m_currentPiece, 1, 0)) {
            m_currentPiece->move(1, 0);
            emit boardChanged();
        }
    }
}

void GameEngine::rotate()
{
    if (!m_gameOver && !m_paused && m_currentPiece) {
        Piece temp = *m_currentPiece;
        temp.rotateRight();
        if (canPlacePiece(temp)) {
            m_currentPiece->rotateRight();
            emit boardChanged();
        }
    }
}

void GameEngine::drop()
{
    if (!m_gameOver && !m_paused && m_currentPiece) {
        while (canPlacePiece(*m_currentPiece, 0, 1)) {
            m_currentPiece->move(0, 1);
        }
        lockCurrentPiece();
    }
}

void GameEngine::tick()
{
    if (m_gameOver || m_paused || !m_currentPiece)
        return;

    if (canPlacePiece(*m_currentPiece, 0, 1)) {
        m_currentPiece->move(0, 1);
        emit boardChanged();
    } else {
        lockCurrentPiece();
    }
}

Board* GameEngine::board() const
{
    return const_cast<Board*>(&m_board);
}

Piece* GameEngine::currentPiece() const
{
    return m_currentPiece.get();
}

Piece* GameEngine::nextPiece() const
{
    return m_nextPiece.get();
}

int GameEngine::score() const
{
    return m_score;
}

bool GameEngine::isGameOver() const
{
    return m_gameOver;
}

bool GameEngine::isPaused() const
{
    return m_paused;
}

void GameEngine::spawnNewPiece()
{
    // Перемещаем следующую фигуру в текущую
    m_currentPiece = std::move(m_nextPiece);
    if (!m_currentPiece)
        return;

    // Создаём новую следующую фигуру
    TetrominoType type = static_cast<TetrominoType>(
        QRandomGenerator::global()->bounded(7));
    m_nextPiece = std::make_unique<Piece>(type);

    // Начальная позиция: по центру сверху
    int startX = (BOARD_WIDTH - m_currentPiece->width()) / 2;
    int startY = 0;
    m_currentPiece->setPosition(startX, startY);

    if (!canPlacePiece(*m_currentPiece)) {
        m_gameOver = true;
        m_timer.stop();
        emit gameOver();
        emit boardChanged();  // чтобы BoardView отрисовал оверлей
    }

    emit nextPieceChanged();
}

bool GameEngine::canPlacePiece(const Piece &piece, int dx, int dy) const
{
    const auto &cells = piece.cells();
    for (const QPoint &cell : cells) {
        int nx = piece.x() + cell.x() + dx;
        int ny = piece.y() + cell.y() + dy;

        if (nx < 0 || nx >= BOARD_WIDTH)       // горизонтальные границы
            return false;
        if (ny >= BOARD_HEIGHT)                // нижняя граница
            return false;

        // Проверка столкновения с зафиксированными ячейками
        if (ny >= 0 && !m_board.isCellEmpty(nx, ny))
            return false;
    }
    return true;
}

void GameEngine::lockCurrentPiece()
{
    if (!m_currentPiece)
        return;

    // Фиксируем фигуру на доске
    const auto &cells = m_currentPiece->cells();
    for (const QPoint &cell : cells) {
        int nx = m_currentPiece->x() + cell.x();
        int ny = m_currentPiece->y() + cell.y();
        if (ny >= 0 && ny < BOARD_HEIGHT && nx >= 0 && nx < BOARD_WIDTH)
            m_board.setCell(nx, ny, Tetromino::color(m_currentPiece->type()));
    }

    clearFullLines();
    spawnNewPiece();

    emit boardChanged();
}

void GameEngine::clearFullLines()
{
    int linesCleared = 0;
    for (int y = BOARD_HEIGHT - 1; y >= 0; --y) {
        if (m_board.isLineFull(y)) {
            m_board.clearLine(y);
            linesCleared++;
            // После сдвига проверяем ту же строку ещё раз
            y++;
        }
    }

    if (linesCleared > 0) {
        // Начисление очков: 1 линия = 100, 2 = 300, 3 = 500, 4 = 800
        int points[] = {0, 1, 3, 5, 8};
        m_score += points[std::min(linesCleared, 4)];
        if(m_level < 10) {
            m_level = m_score / 5 + 1;
            m_timer.setInterval(newTime());
        }
        emit scoreChanged(m_score);
        emit levelChanged(m_level);
    }
}

int GameEngine::newTime()
{
    return 1200 - m_level * 100;
}