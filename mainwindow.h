
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore5Compat>
#include <graphictetris.h>
#include <QtWidgets>
#include "nextshapeview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    Ui::MainWindow *ui;

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    GraphicTetris *tetris;
    NextShapeView *nextShape;

    QPointF centerDisplay(qreal itemW, qreal itemH);

public slots:
    void createTetris();
    void createNextShapeView();
    void slotRestart();
    void setScore(int score);
    void connects();
};

#endif // MAINWINDOW_H
