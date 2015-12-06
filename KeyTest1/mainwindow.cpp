#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::showMaximized();

    timer = new QTimer(this);

    connect(timer, SIGNAL( timeout() ), this, SLOT( update()) );

    timer->start(millisec);

    scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(scene);

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    QRectF rectScene(-200,-200,400,800);

    QPen bluePen(Qt::blue);
    QPen blackPen(Qt::red);

    QBrush yellowBrush(Qt::CrossPattern);
    QBrush blackBrush(Qt::darkCyan);

    scene->addRect(rectScene);

    deltaX = 0;
    deltaY = 0;

    QLineF TopLine(scene->sceneRect().topLeft(),scene->sceneRect().topRight());
    //QLineF

    scene->addLine(TopLine,blackPen);


    bluePen.setWidth(lineWidth);
    blackPen.setWidth(lineWidth+2);


    yellowBrush.setColor(Qt::yellow);

    yelEllipse = scene->addEllipse(scene->sceneRect().center().x(),scene->sceneRect().center().y(),100,100,bluePen,yellowBrush);

    grayLine =  scene->addLine(100,100,0,0,bluePen);
    blackLine = scene->addLine(-100,-100,0,0, blackPen);


     //create map

    scene->addEllipse(-20,-20,40,40,blackPen, blackBrush);


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
   // blackLine->setRotation( (qrand() % 360) );

}

void MainWindow::update()
{
    grayLine->setRotation( angle++ );
    blackLine->setRotation(angle);
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

void MainWindow::dragMoveEvent(QGraphicsSceneDragDropEvent* event)
{
    qDebug() << "pos: " << event->pos();
    qDebug() << "scene pos: " << event->scenePos();
}
