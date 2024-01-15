
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::setFixedSize(680, 500);
    MainWindow::setWindowTitle("TETRIS");
    MainWindow::setWindowIcon(QIcon("/back_four.png"));

    centerDisplay(0,0);

    createTetris();
    createNextShapeView();

    connects();

    nextShape->sendNextShapeNum();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::createTetris()
{
    tetris    = new GraphicTetris;

    ui->pauseButton     ->setGeometry(20, 20, 150, 50);
    ui->restartButton   ->setGeometry(20, 90, 150, 50);
    ui->scoreText       ->setGeometry(20, 160, 150, 50);

    ui->scoreText->setText(QString("score: 0"));
    ui->scoreText->setAlignment(Qt::AlignCenter);

    tetris            ->setGeometry(190, 20, 303, 453);
    ui->verticalLayoutWidget->setGeometry(tetris->geometry());
    ui->verticalLayout->addWidget(tetris);

    tetris->setFocus();
}
void MainWindow::slotRestart()
{
    delete []tetris;
    delete []nextShape;
    createTetris();
    createNextShapeView();
    connects();
    tetris->emitIsCreated();
}
void MainWindow::setScore(int score)
{
    ui->scoreText->setText(QString("score: %1").arg(score));
    ui->scoreText->setAlignment(Qt::AlignCenter);
}
void MainWindow::createNextShapeView()
{
    nextShape = new NextShapeView;

    nextShape           ->setGeometry((tetris->x()+tetris->width()+20),
                           20, 150, 190);
    ui->verticalLayoutWidget_2->setGeometry(nextShape->geometry());
    ui->laynext->addWidget(nextShape);

    connect(tetris,        SIGNAL(gameOver()),
            nextShape,     SLOT(clearScene()));

}
void MainWindow::connects()
{
    connect(ui->pauseButton, SIGNAL(released()),
            tetris, SLOT(slotPause()));
    connect(ui->restartButton, SIGNAL(released()),
            this, SLOT(slotRestart()));
    connect(tetris, SIGNAL(scoreChanged(int)),
            this, SLOT(setScore(int)));

    connect(tetris, SIGNAL(GraphicTetrisToNextShapeView()),
            nextShape, SLOT(sendNextShapeNum()));
    connect(nextShape, SIGNAL(nextShapeToGraphicTetris(int)),
            tetris, SLOT(paintShape(int)));
    connect(tetris, SIGNAL(tetrisIsCreated()),
            nextShape, SLOT(sendNextShapeNum()));
}
QPointF MainWindow::centerDisplay(qreal itemW, qreal itemH)
{
    qDebug() << ui->centralwidget->geometry();
    return QPointF(0, 0);
}
