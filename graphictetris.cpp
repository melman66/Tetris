#include "graphictetris.h"
#include "ui_graphictetris.h"

GraphicTetris::GraphicTetris(QWidget *parent) :
    QGraphicsView(parent),
    ui(new Ui::GraphicTetris)
{
    ui  ->setupUi(this);

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QPixmap cell("/cellTwo.jpg");

    scene             = new QGraphicsScene;
    this              ->setScene(scene);
    scene             ->setSceneRect(0 ,0 ,width(), height());
    scene             ->addPixmap(cell);

    score        = 0;
    pen          = QPen(Qt::white, 0);
    penline      = QPen(Qt::black, 3);
    timer        = new QTimer;
    timerDown    = new QTimer;

    timer        ->setSingleShot(true);
    timerDown    ->setSingleShot(true);
    timerDown    ->setInterval(1000);

    pause        = false;
    setMatrix();

    connect(timerDown, SIGNAL(timeout()),
            this,      SLOT(moveDown()));
    connect(this,      SIGNAL(shapeInMatrix()),
            this,      SLOT(checkLine()));
    connect(this,      SIGNAL(shapeIsStop()),
            this,      SLOT(insertShapeToMatrix()));
    connect(this,      SIGNAL(gameOver()),
            this,      SLOT(slotSetScreenGameOver()));
}

GraphicTetris::~GraphicTetris()
{
    delete ui;
}

void GraphicTetris::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        shapeToLeft();
        break;
    case Qt::Key_Right:
        shapeToRight();
        break;
    case Qt::Key_Up:
        shapeRotate();
        break;
    case Qt::Key_Down:
        shapeToDown();
        break;
    case Qt::Key_Space: {
        slotPause();
        break;
    }
    default:
        break;
    }
}
void GraphicTetris::emitIsCreated()
{
    emit tetrisIsCreated();
}

int  GraphicTetris::randomRotate()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0,3);

    return dist(gen);
}
int  GraphicTetris::randomShape()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0,6);

    int r = dist(gen);

    while(r == shapeRand)
        r = dist(gen);
    return r;
}

QGraphicsItemGroup* GraphicTetris::J()
{
    QGraphicsItemGroup *Shape_J = new QGraphicsItemGroup;
    brush = QBrush(Qt::red);
    pen.setColor(brush.color());

    switch (rotateRand) {
    case 0:
    {        
        Shape_J->addToGroup(scene->addRect(1.5, 1.5, 27, 27, pen, brush));
        Shape_J->addToGroup(scene->addRect(31.5, 1.5, 27, 27, pen, brush));
        Shape_J->addToGroup(scene->addRect(1.5, 31.5, 27, 27, pen, brush));
        Shape_J->addToGroup(scene->addRect(1.5, 61.5, 27, 27, pen, brush));

        break;
    }
    case 1:
    {        
        Shape_J->addToGroup(scene->addRect(1.5, 1.5, 27, 27, pen, brush));
        Shape_J->addToGroup(scene->addRect(31.5, 1.5, 27, 27, pen, brush));
        Shape_J->addToGroup(scene->addRect(61.5, 1.5, 27, 27, pen, brush));
        Shape_J->addToGroup(scene->addRect(61.5, 31.5, 27, 27, pen, brush));

        break;
    }
    case 2:
    {
        Shape_J->addToGroup(scene->addRect(31.5, 1.5, 27, 27, pen, brush));
        Shape_J->addToGroup(scene->addRect(31.5, 31.5, 27, 27, pen, brush));
        Shape_J->addToGroup(scene->addRect(31.5, 61.5, 27, 27, pen, brush));
        Shape_J->addToGroup(scene->addRect(1.5, 61.5, 27, 27, pen, brush));

        break;
    }
    case 3:
    {
        Shape_J->addToGroup(scene->addRect(1.5, 1.5, 27, 27, pen, brush));
        Shape_J->addToGroup(scene->addRect(1.5, 31.5, 27, 27, pen, brush));
        Shape_J->addToGroup(scene->addRect(31.5, 31.5, 27, 27, pen, brush));
        Shape_J->addToGroup(scene->addRect(61.5, 31.5, 27, 27, pen, brush));

        break;
    }
    default:
        break;
}
    return Shape_J;
}
QGraphicsItemGroup* GraphicTetris::L()
{
    QGraphicsItemGroup *Shape_L = new QGraphicsItemGroup;
    brush = QBrush(QColor(255, 150, 0));
    pen.setColor(brush.color());

    switch (rotateRand) {
    case 0:
    {
        Shape_L->addToGroup(scene->addRect(1.5, 1.5, 27, 27, pen, brush));
        Shape_L->addToGroup(scene->addRect(1.5, 31.5, 27, 27, pen, brush));
        Shape_L->addToGroup(scene->addRect(1.5, 61.5, 27, 27, pen, brush));
        Shape_L->addToGroup(scene->addRect(31.5, 61.5, 27, 27, pen, brush));

        break;
    }
    case 1:
    {
        Shape_L->addToGroup(scene->addRect(1.5, 1.5, 27, 27, pen, brush));
        Shape_L->addToGroup(scene->addRect(31.5, 1.5, 27, 27, pen, brush));
        Shape_L->addToGroup(scene->addRect(61.5, 1.5, 27, 27, pen, brush));
        Shape_L->addToGroup(scene->addRect(1.5, 31.5, 27, 27, pen, brush));

        break;
    }
    case 2:
    {
        Shape_L->addToGroup(scene->addRect(1.5, 1.5, 27, 27, pen, brush));
        Shape_L->addToGroup(scene->addRect(31.5, 1.5, 27, 27, pen, brush));
        Shape_L->addToGroup(scene->addRect(31.5, 31.5, 27, 27, pen, brush));
        Shape_L->addToGroup(scene->addRect(31.5, 61.5, 27, 27, pen, brush));

        break;
    }
    case 3:
    {
        Shape_L->addToGroup(scene->addRect(1.5, 31.5, 27, 27, pen, brush));
        Shape_L->addToGroup(scene->addRect(31.5, 31.5, 27, 27, pen, brush));
        Shape_L->addToGroup(scene->addRect(61.5, 31.5, 27, 27, pen, brush));
        Shape_L->addToGroup(scene->addRect(61.5, 1.5, 27, 27, pen, brush));

        break;
    }

    default:
        break;
    }
        return Shape_L;
}
QGraphicsItemGroup* GraphicTetris::O()
{
    QGraphicsItemGroup *Shape_O = new QGraphicsItemGroup;
    brush = QBrush(Qt::yellow);
    pen.setColor(brush.color());

    Shape_O->addToGroup(scene->addRect(1.5, 1.5, 27, 27, pen, brush));
    Shape_O->addToGroup(scene->addRect(31.5, 1.5, 27, 27, pen, brush));
    Shape_O->addToGroup(scene->addRect(1.5, 31.5, 27, 27, pen, brush));
    Shape_O->addToGroup(scene->addRect(31.5, 31.5, 27, 27, pen, brush));

    return Shape_O;
}
QGraphicsItemGroup* GraphicTetris::I()
{
    QGraphicsItemGroup *Shape_I = new QGraphicsItemGroup;
    brush = QBrush(Qt::green);
    pen.setColor(brush.color());

    switch (rotateRand) {
    case 0:
    {
        Shape_I->addToGroup(scene->addRect(1.5, 1.5, 27, 27, pen, brush));
        Shape_I->addToGroup(scene->addRect(1.5, 31.5, 27, 27, pen, brush));
        Shape_I->addToGroup(scene->addRect(1.5, 61.5, 27, 27, pen, brush));
        Shape_I->addToGroup(scene->addRect(1.5, 91.5, 27, 27, pen, brush));

        break;
    }
    case 1:
    {
        Shape_I->addToGroup(scene->addRect(1.5, 1.5, 27, 27, pen, brush));
        Shape_I->addToGroup(scene->addRect(31.5, 1.5, 27, 27, pen, brush));
        Shape_I->addToGroup(scene->addRect(61.5, 1.5, 27, 27, pen, brush));
        Shape_I->addToGroup(scene->addRect(91.5, 1.5, 27, 27, pen, brush));

        break;
    }
    case 2:
    {
        Shape_I->addToGroup(scene->addRect(1.5, 1.5, 27, 27, pen, brush));
        Shape_I->addToGroup(scene->addRect(1.5, 31.5, 27, 27, pen, brush));
        Shape_I->addToGroup(scene->addRect(1.5, 61.5, 27, 27, pen, brush));
        Shape_I->addToGroup(scene->addRect(1.5, 91.5, 27, 27, pen, brush));

        break;
    }
    case 3:
    {
        Shape_I->addToGroup(scene->addRect(1.5, 1.5, 27, 27, pen, brush));
        Shape_I->addToGroup(scene->addRect(31.5, 1.5, 27, 27, pen, brush));
        Shape_I->addToGroup(scene->addRect(61.5, 1.5, 27, 27, pen, brush));
        Shape_I->addToGroup(scene->addRect(91.5, 1.5, 27, 27, pen, brush));

        break;
    }

    default:
        break;
    }
    return Shape_I;
}
QGraphicsItemGroup* GraphicTetris::Z()
{
    QGraphicsItemGroup *Shape_Z = new QGraphicsItemGroup;
    brush = QBrush(QColor(255, 0, 150));
    pen.setColor(brush.color());

    switch (rotateRand) {
    case 0:
    {
        Shape_Z->addToGroup(scene->addRect(31.5, 1.5, 27, 27, pen, brush));
        Shape_Z->addToGroup(scene->addRect(31.5, 31.5, 27, 27, pen, brush));
        Shape_Z->addToGroup(scene->addRect(1.5, 31.5, 27, 27, pen, brush));
        Shape_Z->addToGroup(scene->addRect(1.5, 61.5, 27, 27, pen, brush));

        break;
    }
    case 1:
    {
        Shape_Z->addToGroup(scene->addRect(1.5, 1.5, 27, 27, pen, brush));
        Shape_Z->addToGroup(scene->addRect(31.5, 1.5, 27, 27, pen, brush));
        Shape_Z->addToGroup(scene->addRect(31.5, 31.5, 27, 27, pen, brush));
        Shape_Z->addToGroup(scene->addRect(61.5, 31.5, 27, 27, pen, brush));

        break;
    }
    case 2:
    {
        Shape_Z->addToGroup(scene->addRect(31.5, 1.5, 27, 27, pen, brush));
        Shape_Z->addToGroup(scene->addRect(31.5, 31.5, 27, 27, pen, brush));
        Shape_Z->addToGroup(scene->addRect(1.5, 31.5, 27, 27, pen, brush));
        Shape_Z->addToGroup(scene->addRect(1.5, 61.5, 27, 27, pen, brush));

        break;
    }
    case 3:
    {
        Shape_Z->addToGroup(scene->addRect(1.5, 1.5, 27, 27, pen, brush));
        Shape_Z->addToGroup(scene->addRect(31.5, 1.5, 27, 27, pen, brush));
        Shape_Z->addToGroup(scene->addRect(31.5, 31.5, 27, 27, pen, brush));
        Shape_Z->addToGroup(scene->addRect(61.5, 31.5, 27, 27, pen, brush));

        break;
    }
    default:
        break;
    }
    return Shape_Z;
}
QGraphicsItemGroup* GraphicTetris::S()
{
    QGraphicsItemGroup *Shape_S = new QGraphicsItemGroup;
    brush = QBrush(Qt::blue);
    pen.setColor(brush.color());

    switch (rotateRand) {
    case 0:
    {
        Shape_S->addToGroup(scene->addRect(1.5, 1.5, 27, 27, pen, brush));
        Shape_S->addToGroup(scene->addRect(1.5, 31.5, 27, 27, pen, brush));
        Shape_S->addToGroup(scene->addRect(31.5, 31.5, 27, 27, pen, brush));
        Shape_S->addToGroup(scene->addRect(31.5, 61.5, 27, 27, pen, brush));

        break;
    }
    case 1:
    {
        Shape_S->addToGroup(scene->addRect(31.5, 1.5, 27, 27, pen, brush));
        Shape_S->addToGroup(scene->addRect(61.5, 1.5, 27, 27, pen, brush));
        Shape_S->addToGroup(scene->addRect(1.5, 31.5, 27, 27, pen, brush));
        Shape_S->addToGroup(scene->addRect(31.5, 31.5, 27, 27, pen, brush));

        break;
    }
    case 2:
    {
        Shape_S->addToGroup(scene->addRect(1.5, 1.5, 27, 27, pen, brush));
        Shape_S->addToGroup(scene->addRect(1.5, 31.5, 27, 27, pen, brush));
        Shape_S->addToGroup(scene->addRect(31.5, 31.5, 27, 27, pen, brush));
        Shape_S->addToGroup(scene->addRect(31.5, 61.5, 27, 27, pen, brush));

        break;
    }
    case 3:
    {
        Shape_S->addToGroup(scene->addRect(31.5, 1.5, 27, 27, pen, brush));
        Shape_S->addToGroup(scene->addRect(61.5, 1.5, 27, 27, pen, brush));
        Shape_S->addToGroup(scene->addRect(1.5, 31.5, 27, 27, pen, brush));
        Shape_S->addToGroup(scene->addRect(31.5, 31.5, 27, 27, pen, brush));

        break;
    }
    default:
        break;
    }
    return Shape_S;
}
QGraphicsItemGroup* GraphicTetris::T()
{
    QGraphicsItemGroup *Shape_T = new QGraphicsItemGroup;
    brush = QBrush(QColor(170, 0, 255));
    pen.setColor(brush.color());

    switch (rotateRand) {
    case 0:
    {
        Shape_T->addToGroup(scene->addRect(31.5, 1.5, 27, 27, pen, brush));
        Shape_T->addToGroup(scene->addRect(31.5, 31.5, 27, 27, pen, brush));
        Shape_T->addToGroup(scene->addRect(31.5, 61.5, 27, 27, pen, brush));
        Shape_T->addToGroup(scene->addRect(1.5, 31.5, 27, 27, pen, brush));

        break;
    }
    case 1:
    {
        Shape_T->addToGroup(scene->addRect(31.5, 1.5, 27, 27, pen, brush));
        Shape_T->addToGroup(scene->addRect(61.5, 1.5, 27, 27, pen, brush));
        Shape_T->addToGroup(scene->addRect(1.5, 1.5, 27, 27, pen, brush));
        Shape_T->addToGroup(scene->addRect(31.5, 31.5, 27, 27, pen, brush));

        break;
    }
    case 2:
    {
        Shape_T->addToGroup(scene->addRect(1.5, 1.5, 27, 27, pen, brush));
        Shape_T->addToGroup(scene->addRect(1.5, 31.5, 27, 27, pen, brush));
        Shape_T->addToGroup(scene->addRect(1.5, 61.5, 27, 27, pen, brush));
        Shape_T->addToGroup(scene->addRect(31.5, 31.5, 27, 27, pen, brush));

        break;
    }
    case 3:
    {
        Shape_T->addToGroup(scene->addRect(31.5, 1.5, 27, 27, pen, brush));
        Shape_T->addToGroup(scene->addRect(1.5, 31.5, 27, 27, pen, brush));
        Shape_T->addToGroup(scene->addRect(31.5, 31.5, 27, 27, pen, brush));
        Shape_T->addToGroup(scene->addRect(61.5, 31.5, 27, 27, pen, brush));

        break;
    }
    default:
        break;
    }
    return Shape_T;
}
QGraphicsItemGroup* GraphicTetris::choiseShape(int numberShape)
{
    rotateRand          = randomRotate();

    switch (numberShape) {

    case 0: return J();
    case 1: return L();
    case 2: return O();
    case 3: return I();
    case 4: return Z();
    case 5: return S();
    case 6: return T();

    default:
        break;
    }
    return nullptr;
}
void GraphicTetris::removeItems(int lineI)
{    
    iterPointBegin = rectsChildPos.begin();
    iterPoinEnd    = rectsChildPos.end();

    while (iterPointBegin != iterPoinEnd) {
        if(((*iterPointBegin).y() -1.5 ) ==  lineI*30) {
            rectsChildPos.erase(iterPointBegin);

            iterPointBegin = rectsChildPos.begin();
            iterPoinEnd    = rectsChildPos.end();
        }
        else {
            *iterPointBegin++;
        }
    }
    iterPointBegin = rectsChildPos.begin();
    iterPoinEnd    = rectsChildPos.end();

    while (iterPointBegin != iterPoinEnd) {
        if((*iterPointBegin).y() < (lineI*30))
            (*iterPointBegin).setY((*iterPointBegin).y()+30);

        *iterPointBegin++;
    }

    for(int x=0; x<10; x++)
        scene->removeItem(scene->itemAt(x*30+3, lineI*30+3, t));

    iter    = sceneShapes.constBegin();
    iterend = sceneShapes.constEnd();

    while(iter!=iterend) {
        if((*iter)->y() < (lineI * 30))
            (*iter)->setY((*iter)->y()+30);

        iter++;
    }
    timer->start();
}
void GraphicTetris::removeMatrixLine(int lineM)
{
    for (lineM; lineM>0; lineM--) {
        for(int x=0; x<10; x++)
            matrix[lineM][x] = matrix[lineM-1][x];
    }
    printMatrix();
}
void GraphicTetris::setMatrix()
{
    for(int i = 0; i < 15; i++) {
        for (int j = 0; j < 10; j++)
            matrix[i][j]=false;
    }
}
void GraphicTetris::printMatrix()
{
    for(int i = 0; i < 15; i++) {
    qDebug()
        << matrix[i][0]
        << matrix[i][1]
        << matrix[i][2]
        << matrix[i][3]
        << matrix[i][4]
        << matrix[i][5]
        << matrix[i][6]
        << matrix[i][7]
        << matrix[i][8]
        << matrix[i][9];
    }
}
//-----поворот и перемещение------
void GraphicTetris::shapeToLeft()
{
    if (isCollisingLeftForAll() == false
        && (flagNoMoveOrRotate == false))
            lastShape->setX(lastShape->x()-30);
}
void GraphicTetris::shapeToRight()
{
    if ((isCollisingRightForAll() == false)
        && (flagNoMoveOrRotate == false))
            lastShape->setX(lastShape->x()+30);
}
void GraphicTetris::shapeToDown()
{
    if (!isCollisingDownForAll())
        lastShape->setY(lastShape->y()+30);
}
void GraphicTetris::shapeRotate()
{
    if (flagNoMoveOrRotate == false) {
        if (rotateSetPos())
            incRotateRand();
        else
            return;

        lastPos = lastShape->scenePos();
        scene->removeItem(lastShape);
        lastShape = new QGraphicsItemGroup;
        switch (shapeRand)
        {
        case 0: lastShape = J(); break;
        case 1: lastShape =  L(); break;
        case 2: lastShape =  O(); break;
        case 3: lastShape =  I(); break;
        case 4: lastShape =  Z(); break;
        case 5: lastShape =  S(); break;
        case 6: lastShape =  T(); break;

            break;
        default:
            break;
        }
        lastShape->setPos(lastPos);
        scene->addItem(lastShape);
    }
}

//-----для поворота и перемещения------

//максимально близкая фигура или стена
QPointF GraphicTetris::maxNearbyXpointLeft()
{
    qreal   maxBr, x, y;
    QPointF maxPoint    = QPointF(-1, -1);
    QPointF maxX        = QPointF(300, -1);
    int iterBrHeight    = 0;
    flagToMaxShapeLeft  = false;

    if ((rotateRand == 0) || (rotateRand == 2))
        maxBr = -(lastShape->boundingRect().height() + 3);
    else
        maxBr = -(lastShape->boundingRect().width() + 3);

    while (iterBrHeight >= maxBr) {
        int i = 0;
        while (i < 4) {
            x = lastShape->childItems().takeAt(i)->boundingRect().x()
                + lastShape->scenePos().x() + iterBrHeight;
            y = lastShape->childItems().takeAt(i)->boundingRect().y()
                + lastShape->scenePos().y();
            if (x < maxX.x())
                maxX = QPointF(x, y);
            if (rectsChildPos.contains(QPointF(x, y))) {
                if ((maxPoint.x() < x) || (maxPoint.x() == -1)) {
                    maxPoint.setX(x);
                    maxPoint.setY(y);
                    flagToMaxShapeLeft = true;
                }
            }
            else {
                if (flagToMaxShapeLeft == false) {
                    maxPoint.setX(-28.5);
                    maxPoint.setY(maxX.y());
                }
            }
            i++;
        }
        iterBrHeight -= 30;
    }
    return maxPoint;
}
QPointF GraphicTetris::maxNearbyXpointRight()
{
    qreal x, y;
    flagToMaxShapeRight = false;
    QPointF maxPoint    = QPointF(-1, -1);
    QPointF maxX        = QPointF(-1, -1);

    int iterBrHeight    = 30;
    int maxBr;

    if ((rotateRand == 0) || (rotateRand == 2))
        maxBr = lastShape->boundingRect().height() + 3;
    else
        maxBr = lastShape->boundingRect().width() + 3;

    while (iterBrHeight <= maxBr) {
        int i = 0;

        while (i < 4) {

            x = lastShape->childItems().takeAt(i)->boundingRect().x()
                + lastShape->scenePos().x() + iterBrHeight;
            y = lastShape->childItems().takeAt(i)->boundingRect().y()
                + lastShape->scenePos().y();
            if (x > maxX.x())
                maxX = QPointF(x, y);

            if (rectsChildPos.contains(QPointF(x, y))) {
                if ((maxPoint.x() > x) || (maxPoint.x() == -1)) {
                    maxPoint.setX(x);
                    maxPoint.setY(y);

                    flagToMaxShapeRight = true;
                }
            }
            else {
                if (flagToMaxShapeRight == false) {
                    maxPoint.setX(301.5);
                    maxPoint.setY(maxX.y());
                }
            }
            i++;
        }
        iterBrHeight += 30;
    }
    return maxPoint;
}
QPointF GraphicTetris::maxNearbyYpoint()
{
    flagToMaxShapeDown = false;

    qreal x, y, maxBr;
    QPointF maxPoint = QPointF(-1, -1);
    int iterBrHeight = 30;

    if ((rotateRand == 0) || (rotateRand == 2))
        maxBr = lastShape->boundingRect().height() + 3;
    else
        maxBr = lastShape->boundingRect().width() + 3;

    while (iterBrHeight <= maxBr) {
        int i = 0;

        while (i < 4) {

            x = lastShape->childItems().takeAt(i)->boundingRect().x()
                + lastShape->x();
            y = lastShape->childItems().takeAt(i)->boundingRect().y()
                + lastShape->y() + iterBrHeight;

            if (rectsChildPos.contains(QPointF(x, y))) {
                if ((maxPoint.y() > y) || (maxPoint.y() == -1)) {
                    maxPoint.setX(x);
                    maxPoint.setY(y);
                    flagToMaxShapeDown = true;
                }
            }
            else {
                if (flagToMaxShapeDown == false) {
                    maxPoint.setX(lastShape->x() + 1.5);
                    maxPoint.setY(451.5);
                }
            }
            i++;
        }
        iterBrHeight += 30;
    }
    return maxPoint;
}
//есть ли рядом фигура
bool GraphicTetris::isCollisingRightForAll()
{
    qreal x, y;

    for (int i = 0; i < 4; i++) {
            x = lastShape->childItems().takeAt(i)->boundingRect().x()
                + lastShape->x() + 30;
            y = lastShape->childItems().takeAt(i)->boundingRect().y()
                + lastShape->y();

            qDebug() << "child right coll x y" << x << y;

            if (   (x == maxNearbyXpointRight().x())
                && (y == maxNearbyXpointRight().y())) {
            qDebug() << "true";
            return true;
        }
    }
    return false;
}
bool GraphicTetris::isCollisingLeftForAll()
{
    qreal x, y;

    for (int i = 0; i < 4; i++) {
        x = lastShape->childItems().takeAt(i)->boundingRect().x()
            + lastShape->x() - 30;
        y = lastShape->childItems().takeAt(i)->boundingRect().y()
            + lastShape->y();

        if ((maxNearbyXpointLeft().x() == x)
            && (maxNearbyXpointLeft().y() == y)) {
            return true;
        }
    }
    return false;
}
bool GraphicTetris::isCollisingDownForAll()
{
    bool flagIsCollising = false;
    qreal x, y;

    for (int i = 0; i < 4; i++) {
        x = lastShape->childItems().takeAt(i)->boundingRect().x()
            + lastShape->x();
        y = lastShape->childItems().takeAt(i)->boundingRect().y()
            + lastShape->y() + 30;

        if (maxNearbyYpoint() == QPointF(x, y)) {
            flagIsCollising = true;
            flagNoMoveOrRotate = true;
        }
        else if (y == 451.5) {
            flagNoMoveOrRotate = true;
            return true;
        }
    }
    return flagIsCollising;
}
//влезает ли при повороте между фигурами или стенами
bool GraphicTetris::isFitsBetweenShapes(qreal leftX, qreal rightX)
{
    if(((rightX - leftX - 30)
         >= lastShape->boundingRect().height() + 3)
        && ((rightX != -1) || (leftX != -1))
        && ((rotateRand == 0) || (rotateRand == 2))) {
        return true;
    }
    else
        return false;
}
bool GraphicTetris::isFitsBetweenShapes(qreal DownY)
{
    bool flagBetween = false;
    for(int i = 0; i < 4; i++) {
        if (((DownY - (lastShape->y() + lastShape->childItems().takeAt(i)->y()))
             >= (lastShape->boundingRect().width() + 3))
            && ((DownY != -1))
            && ((rotateRand == 1) || (rotateRand == 3)))
            flagBetween = true;
        else
            return false;
    }
    return flagBetween;
}
//уствноыка позиций фигуры для последующего поворота
bool GraphicTetris::rotateSetPos()
{
    qreal shapeBrect = lastShape->boundingRect().height() + 3 + 1.5;

    if ((rotateRand == 0) || (rotateRand == 2)) {
        if (isFitsBetweenShapes(maxNearbyXpointLeft().x(), maxNearbyXpointRight().x())) {
            if ((maxNearbyXpointRight().x() - maxNearbyXpointLeft().x()) == shapeBrect) {
                lastShape->setX(maxNearbyXpointLeft().x() + 30);
                return true;
            }
            else if (isCollisingRightForAll()
                     || ((lastShape->x())
                         > (maxNearbyXpointRight().x() - shapeBrect - 30))) {
                lastShape->setX(maxNearbyXpointRight().x() - shapeBrect);
                return true;
            }
            else {
                return true;
            }
        }
    }
    else if ((rotateRand == 1) || (rotateRand == 3)) {
        if (isFitsBetweenShapes(maxNearbyYpoint().y())) {
            return true;
        }
    }
    return false;
}
void GraphicTetris::incRotateRand()
{
    if (rotateRand < 3)
        rotateRand++;
    else
        rotateRand = 0;
}

//перезапись вектора rectsChildPos в вектрор sceneShapes
void GraphicTetris::rerecordVectors()
{
    iterPoinEnd = rectsChildPos.end();

    for (int i = 0; i < 4; i++) {
        iterPoinEnd--;

        QGraphicsRectItem *sceneRect = new QGraphicsRectItem;

        sceneRect->setRect(0, 0, 27, 27);
        sceneRect->setBrush(brush);
        sceneRect->setPen(pen);
        sceneRect->setX((*iterPoinEnd).x());
        sceneRect->setY((*iterPoinEnd).y());

        sceneShapes.push_back(sceneRect);
    }
    scene->removeItem(lastShape);
    for (int i = 0; i < 4; i++)
        scene->addItem(sceneShapes.at(sceneShapes.count()-i-1));

}
qreal GraphicTetris::centerOnSceneToThisItemX(qreal itemW)
{
    return (scene->width()/2 - itemW/2);
}
//--------для "красоты"---------
QBrush GraphicTetris::gradientBrush()
{
    QLinearGradient grad(0, 303, 0, 200);

    grad.setColorAt(1, QColor(255, 120, 0));
    grad.setColorAt(0, QColor(255, 220, 0));

    QBrush brushRect(grad);
    return brushRect;
}
QFont GraphicTetris::fontWindow()
{
    QFont fontItem("Yu Gothic UI Semibold");
    fontItem.setPointSize(40);
    fontItem.setBold(true);

    return fontItem;
}
void GraphicTetris::removeScreenPause()
{
    delete pauseWindow;
    pause = false;
}
//------------------------------
//------------SLOTS-------------
//проверить заполненность линии
void GraphicTetris::checkLine()
{
    bool line = false;
    for (int i = 0; i < 15; i++) {
        for (int j = 1; j < 9; j++) {
            if ((matrix[i][j-1] == true) &&
                (matrix[i][j] == true) &&
                (matrix[i][j+1] == true)) {
                line = true;
            }
            else {
                line = false;
                break;
            }
        }
        if (line==true) {
            timer->stop();
            removeMatrixLine(i);
            removeItems(i);
            score++;
            emit scoreChanged(score);
        }
    }
    emit GraphicTetrisToNextShapeView();
}
//записать конечные позиции квадратов фигуры
void GraphicTetris::insertRectsChildPos()
{
    QPointF buff;
    for (int i = 0; i < 4; i++) {

        buff.setX(lastShape->childItems().takeAt(i)->boundingRect().x()
                  + lastShape->scenePos().x());
        buff.setY(lastShape->childItems().takeAt(i)->boundingRect().y()
                  + lastShape->scenePos().y());

        rectsChildPos.push_back(buff);
    }
}
//записать фигуру в бинарную матрицу
void GraphicTetris::insertShapeToMatrix()
{
    int yj = -1;
    int xi = -1;

    iterSceneShapesEnd = sceneShapes.end();

    for (int i = 0; i < 4; i++) {
        iterSceneShapesEnd--;

        xi = ((*iterSceneShapesEnd)->scenePos().x() + 1.5) / 30;
        yj = ((*iterSceneShapesEnd)->scenePos().y() + 1.5) / 30;

        matrix[yj][xi] = true;
    }
    printMatrix();
    emit shapeInMatrix();//goto checkLine
}
//ронять фигуру
void GraphicTetris::moveDown()
{
    if (isCollisingDownForAll()==true) {
        if (lastShape->y() <= 60) {
            timerDown->stop();
            emit gameOver();//slotSetScreenGameOver
        }
        else {
            timerDown->stop();
            insertRectsChildPos();
            rerecordVectors();

            emit shapeIsStop();//slot insertShapeToMatrix
        }
    }
    else {
        lastShape->setY(lastShape->y()+30);
        isCollisingDownForAll();//set flag noMove
        timerDown->start();
    }
}
//нарисовать новую фигуру
void GraphicTetris::paintShape(int nextShapeNumS)
{
    shapeRand = nextShapeNumS;
    lastShape = choiseShape(nextShapeNumS);

    lastPos.setX(120);
    lastPos.setY(-30);

    flagNoMoveOrRotate  = false;

    lastShape->setPos(lastPos);
    scene->addItem(lastShape);

    if (pause == false)
        moveDown();
}
//записать позиции квадратов последней фигуры
//в вектор rectsChildPos
void GraphicTetris::slotPause()
{
    if (pause == false) {
        timerDown->stop();
        slotSetPauseScreen();
    }
    else {
        removeScreenPause();
        timerDown->start();
    }
}
//слот установки заставки gameover
void GraphicTetris::slotSetScreenGameOver()
{
    QRect rectGaneOver(0, 0, 303, 453);

    scene->addRect(rectGaneOver, QPen(Qt::white), gradientBrush());

    QGraphicsTextItem *textItem = scene->addText("GAME\nOVER");
    textItem->setDefaultTextColor(Qt::yellow);
    textItem->setFont(fontWindow());
    textItem->setX(centerOnSceneToThisItemX(textItem->boundingRect().width()));

    QGraphicsTextItem *textScore = scene->addText(QString("SCORE: %1").arg(score));

    QFont fontItem("Yu Gothic UI Semibold");
    fontItem.setPointSize(40);
    fontItem.setBold(true);

    fontItem .setPointSize(30);
    textScore   ->setFont(fontItem);
    textScore   ->setX(centerOnSceneToThisItemX(textScore->boundingRect().width()));
    textScore   ->setY(40 + scene->height() - textScore->boundingRect().height() - 40);
    textScore   ->setDefaultTextColor(Qt::red);
}
//слот кнопки паузы и установки заставки
void GraphicTetris::slotSetPauseScreen()
{
    QRect rectPause(0, 0, 303, 453);

    pauseWindow = new QGraphicsItemGroup;
    pauseWindow->addToGroup(
        scene->addRect(rectPause, QPen(Qt::white), gradientBrush()));

    QGraphicsTextItem *textPause = scene->addText("PAUSE");

    textPause->setDefaultTextColor(Qt::yellow);
    textPause->setFont(fontWindow());
    textPause->setX(centerOnSceneToThisItemX(textPause->boundingRect().width()));
    textPause->setY(40);

    pauseWindow->addToGroup(textPause);

    scene->addItem(pauseWindow);

    pause = true;
}
//------------------------------

