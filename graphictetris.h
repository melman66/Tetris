#ifndef GRAPHICTETRIS_H
#define GRAPHICTETRIS_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QTimer>
#include <QVector>
#include <QKeyEvent>
#include <random>

namespace Ui {
class GraphicTetris;
}

class GraphicTetris : public QGraphicsView
{
    Q_OBJECT

public:
    explicit GraphicTetris(QWidget *parent = nullptr);
    ~GraphicTetris();
    Ui::GraphicTetris *ui;

    QGraphicsScene *scene;
    QGraphicsScene *sceneForNextShape;
    QGraphicsLineItem *lineDown;
    QPen pen, penline;
    QBrush brush;
    QImage cell;
    QPainter painter;
    QGraphicsItemGroup Grid;
    QTimer *timer;
    QTimer *timerDown;
    QTransform t;
    bool matrix[15][10];
    int shapeRand;
    int rotateRand;
    qreal posCollisingItemX;
    QPointF lastPos;
    bool flagNoMoveOrRotate;
    QVector<QGraphicsRectItem*>::const_iterator iter;
    QVector<QGraphicsRectItem*>::const_iterator iterend;
    QVector<QPointF> rectsChildPos;
    QList<QGraphicsItem*>::iterator iterChildLast;
    QList<QGraphicsItem*>::const_iterator iterChildBegin;
    QVector<QPointF>::iterator iterPointBegin;
    QVector<QPointF>::iterator iterPoinEnd;
    QGraphicsItemGroup *lastShape;
    int nextShape;
    QVector <QGraphicsRectItem*> sceneShapes;
    QVector <QGraphicsRectItem*>::iterator iterSceneShapesEnd;
    bool pause;
    bool flagToMaxShapeLeft;
    bool flagToMaxShapeRight;
    bool flagToMaxShapeDown;
    int  score;
    QGraphicsItemGroup *pauseWindow;

    void emitIsCreated();
    QGraphicsItemGroup *J();
    QGraphicsItemGroup *L();
    QGraphicsItemGroup *O();
    QGraphicsItemGroup *I();
    QGraphicsItemGroup *Z();
    QGraphicsItemGroup *S();
    QGraphicsItemGroup *T();
    void setMatrix();
    void printMatrix();
    void keyPressEvent(QKeyEvent *);
    void shapeToLeft();
    void shapeToRight();
    void shapeToDown();
    void removeItems(int);
    void removeMatrixLine(int);
    void moveItems(int);

    void shapeRotate();
    bool rotateSetPos();
    QPointF maxNearbyXpointRight();
    QPointF maxNearbyXpointLeft();
    QPointF maxNearbyYpoint();

    bool isCollisingRightForAll();
    bool isCollisingLeftForAll();
    bool isCollisingDownForAll();
    bool isFitsBetweenShapes(qreal, qreal);
    bool isFitsBetweenShapes(qreal);

    void incRotateRand();
    void rerecordVectors();
    void removeScreenPause();
    qreal centerOnSceneToThisItemX(qreal itemW);
    QBrush gradientBrush();
    QFont fontWindow();

protected:
    QGraphicsItemGroup *choiseShape(int numberShape);

    int  randomShape();
    int  randomRotate();

signals:
    void shapeIsStop();
    void shapeInMatrix();
    void LineIsRemoved();
    void lineCompleted();
    void gameOver();
    void GraphicTetrisToNextShapeView();
    int scoreChanged(int scoreSignal);
    void tetrisIsCreated();

public slots:
    void checkLine();
    void insertShapeToMatrix();
    void insertRectsChildPos();
    void moveDown();
    void paintShape(int);
    void slotPause();
    void slotSetScreenGameOver();
    void slotSetPauseScreen();   
};

#endif // GRAPHICTETRIS_H
