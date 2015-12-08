#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::showMaximized();

    scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(scene);

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

//    QPixmap pim("./imgs/programIcon.png");
//    scene->setBackgroundBrush(pim);
//    //ui->graphicsView->setBackgroundBrush();


    //start with full health
    remLife = ui->progressBar->maximum();

    timer = new QTimer(this);
    advTimer = new QTimer(this);
    stimer = new QTimer(this);


    counter = new QTimer(this);

    time = new QTime(0,0,0,0);

    connect(counter, SIGNAL(timeout()),this, SLOT(count()));

    connect(timer, SIGNAL( timeout() ), this, SLOT( update()) );
    connect(advTimer,SIGNAL(timeout()), scene, SLOT( advance() ) );

    connect(stimer,SIGNAL(timeout()),this,SLOT(update2()));

    counter->start(50);
    time->start();

    stimer->start(10);

    timer->start(millisec);
    advTimer->start(100);

    QRectF rectScene(-200,-200,400,400);

    QPen bluePen(Qt::blue);
    QPen blackPen(Qt::red);

    //QBrush yellowBrush(Qt::CrossPattern);
    yellowBrush = new QBrush(Qt::CrossPattern);
    QBrush blackBrush(Qt::darkCyan);

    scene->addRect(rectScene);

    /*************************************************************/
    //init vars

    changingAngle = 0;

    deltaX = 0;
    deltaY = 0;

    /**************************************************************/
    TopLine = new QLineF(scene->sceneRect().topLeft(),scene->sceneRect().topRight());
    LeftLine = new QLineF(scene->sceneRect().topLeft(),scene->sceneRect().bottomLeft());
    RightLine =  new QLineF(scene->sceneRect().topRight(),scene->sceneRect().bottomRight());
    BottomLine = new QLineF(scene->sceneRect().bottomLeft(),scene->sceneRect().bottomRight());

    topB = scene->addLine(*TopLine,blackPen);
    leftB = scene->addLine(*LeftLine,blackPen);
    rightB = scene->addLine(*RightLine,blackPen);
    botB = scene->addLine(*BottomLine,blackPen);


    bluePen.setWidth(lineWidth);
    blackPen.setWidth(lineWidth+2);


    yellowBrush->setColor(Qt::yellow);

    yelEllipse = scene->addEllipse(18,37,100,100,bluePen,*yellowBrush);
    grayLine =  scene->addLine(150,150,0,0,bluePen);
    blackLine = scene->addLine(-150,-150,0,0, blackPen);



     //create map

    centerEll = scene->addEllipse(-20,-20,40,40,blackPen, blackBrush);


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
    angle += 5;
    grayLine->setRotation(angle);
    blackLine->setRotation(angle);

//    changingAngle++;

//    if(changingAngle == 2500)
//    {
//        changingAngle = 0;
//        grayLine->setRotation(qrand() % 360);
//    }

}

void MainWindow::update2()
{
    ui->label->setText(QString::number(yelEllipse->pos().x()) + ", "  + QString::number(yelEllipse->pos().y()));

    //remove keyboard bug
    deltaX = yelEllipse->pos().x();
    deltaY = yelEllipse->pos().y();

    ui->lcdNumber->display((double)time->elapsed() * 0.22 );

    if(yelEllipse->collidesWithItem(centerEll) )
    {
        gameOver();
    }

    if(yelEllipse->collidesWithItem(topB))
    {
        gameOver();
    }
    if(yelEllipse->collidesWithItem(leftB))
    {
        gameOver();
    }

    if(yelEllipse->collidesWithItem(rightB))
    {
        gameOver();
    }

    if(yelEllipse->collidesWithItem(botB))
    {
        gameOver();
    }

    if(!yelEllipse->collidesWithItem(grayLine))
    {
        ui->label->setText("Collision!!!");
        yellowBrush->setColor(Qt::red);
        yellowBrush->setStyle(Qt::SolidPattern);
        yelEllipse->setBrush(*yellowBrush);
        ui->progressBar->setValue(remLife--);

        if(remLife <= ui->progressBar->minimum())
        {
          gameOver();
        }
    }
    else
    {
        yellowBrush->setColor(Qt::yellow);
        yellowBrush->setStyle(Qt::CrossPattern);
        yelEllipse->setBrush(*yellowBrush);
    }
}

void MainWindow::count()
{
    ui->labelCounter->setText(QString::number(time->elapsed()));

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

void MainWindow::gameOver()
{
    QMessageBox msg;

    yelEllipse->setPos(18,37);

    msg.setText("Game Over!!!");
    msg.setWindowIcon(QIcon("imgs/programIcon.png"));
    msg.setWindowTitle("Game Over my Friend!!!!");
    msg.setIcon(QMessageBox::Information);
    msg.setInformativeText("you`ve got: " + QString::number( ( (double)time->elapsed() * 0.22) ) + " points");

    msg.exec();

    //restore full health
    remLife = ui->progressBar->maximum();
    ui->progressBar->setValue(remLife);

    time->restart();

}


