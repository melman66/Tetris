#ifndef NEXTSHAPEVIEW_H
#define NEXTSHAPEVIEW_H

#include <QWidget>
#include "graphictetris.h"

namespace Ui {
class NextShapeView;
}

class NextShapeView : public GraphicTetris
{
    Q_OBJECT

public:
    explicit NextShapeView(GraphicTetris *parent = nullptr);
    ~NextShapeView();

    QGraphicsScene *nextShapeScene;
    QGraphicsItemGroup *nextShapeItem;
    int nextShapeNum;

    QPointF setCenterPos(qreal wItem, qreal hItem);
public slots:
    void createNextShape();
    void sendNextShapeNum();
    void clearScene();

signals:
    int nextShapeToGraphicTetris(int);

private:
    Ui::NextShapeView *ui;
};

#endif // NEXTSHAPEVIEW_H
