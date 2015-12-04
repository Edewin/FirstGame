#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);

    connect(timer, SIGNAL( timeout() ), this, SLOT( update()) );

    timer->start(millisec);

    scene = new QGraphicsScene(this);

    deltaX = 0;
    deltaY = 0;

    ui->graphicsView->setScene(scene);

    QPen bluePen(Qt::blue);

    bluePen.setWidth(lineWidth);

    QBrush yellowBrush(Qt::CrossPattern);

    rect = new QRectF();

    rect->setX(10);
    rect->setY(10);
    rect->setHeight(100);
    rect->setWidth(100);

    yellowBrush.setColor(Qt::yellow);

    yelEllipse = scene->addEllipse(10,10,100,100,bluePen,yellowBrush);

    grayLine =  scene->addLine(0,0,150,150,bluePen);

    yelEllipse->setFlag(QGraphicsItem::ItemIsMovable);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    // to do
    grayLine->setRotation(90);

}

void MainWindow::update()
{
    grayLine->setRotation( angle++ );
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
   // qDebug() << event->key();
    switch (event->key())
    {
    case Qt::Key_Left:
        ui->label->setText("Left Key Pressed");
        break;
    case Qt::Key_Right:
        ui->label->setText("Right Key Pressed");
        break;

    case Qt::Key_W:

        deltaY -= offset;
        yelEllipse->setY(deltaY);

        ui->label->setText("w pressed " + QString::number(yelEllipse->x()) + ", " + QString::number(yelEllipse->y()));

        break;

    case Qt::Key_S:

        deltaY += offset;
        yelEllipse->setY(deltaY);

        ui->label->setText("s pressed " + QString::number(yelEllipse->x()) + ", " + QString::number(yelEllipse->y()));
        break;

    case Qt::Key_A:

        deltaX -= offset;
        yelEllipse->setX(deltaX);

        ui->label->setText("a pressed " + QString::number(yelEllipse->x()) + ", " + QString::number(yelEllipse->y()) );
        break;

    case Qt::Key_D:

        deltaX += offset;

        yelEllipse->setX(deltaX);

        ui->label->setText("d pressed " + QString::number(yelEllipse->x()) + ", " + QString::number(yelEllipse->y()));

        break;

    case Qt::Key_E:

        deltaX += offset;    // same as D
        deltaY -= offset;    // same as W
        yelEllipse->setPos(deltaX,deltaY);

        ui->label->setText("e pressed " + QString::number(yelEllipse->x()) + ", " + QString::number(yelEllipse->y()) );
        break;

    case Qt::Key_Q:

        deltaX -= offset;    //same as A
        deltaY -= offset;    // same as W
        yelEllipse->setPos(deltaX,deltaY);

        ui->label->setText("q pressed " + QString::number(yelEllipse->x()) + ", " + QString::number(yelEllipse->y()) );
        break;

    case Qt::Key_Z:

        deltaX -= offset;    //same as A
        deltaY += offset;    // same as S
        yelEllipse->setPos(deltaX,deltaY);

        ui->label->setText("z pressed " + QString::number(yelEllipse->x()) + ", " + QString::number(yelEllipse->y()) );
        break;

    case Qt::Key_X:

        deltaX += offset;    //same as D
        deltaY += offset;    // same as S
        yelEllipse->setPos(deltaX,deltaY);

        ui->label->setText("x pressed " + QString::number(yelEllipse->x()) + ", " + QString::number(yelEllipse->y()) );
        break;

    case Qt::Key_R:

        ui->label->setText("Restart Game ;)");

        deltaX = deltaY = 0;

        yelEllipse->setPos( deltaX, deltaY );

        break;

    default:
        ui->label->setText("Another key pressed");
        break;
    }
}