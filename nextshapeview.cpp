#include "nextshapeview.h"
#include "ui_nextshapeview.h"

NextShapeView::NextShapeView(GraphicTetris *parent) :
    GraphicTetris(parent),
    ui(new Ui::NextShapeView)
{
    ui->setupUi(this);

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    nextShapeScene = new QGraphicsScene;
    nextShapeScene->setSceneRect(0, 0, width(), height());
    this->setScene(nextShapeScene);
    nextShapeNum = randomShape();
}

NextShapeView::~NextShapeView()
{
    delete ui;
}
void NextShapeView::createNextShape()
{
    nextShapeScene->clear();
    nextShapeScene->addRect(0, 0, width(), height(), QPen(),
                            QBrush(QColor(255, 255, 255, 100)));

    nextShapeItem = new QGraphicsItemGroup;

    nextShapeNum  = randomShape();

    nextShapeItem = choiseShape(nextShapeNum);
    nextShapeItem ->setPos(setCenterPos(nextShapeItem->boundingRect().width(),
                                       nextShapeItem->boundingRect().height()));

    nextShapeScene->addItem(nextShapeItem);
}
QPointF NextShapeView::setCenterPos(qreal wItem, qreal hItem)
{
    return QPoint((nextShapeScene->width()/2 - (wItem/2)),
                  (nextShapeScene->height()/2 - (hItem/2)));
}
void NextShapeView::sendNextShapeNum()
{
    emit nextShapeToGraphicTetris(nextShapeNum);
    createNextShape();
}
void NextShapeView::clearScene()
{
    nextShapeScene->clear();
}
