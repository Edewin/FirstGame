#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QtCore>
#include <QKeyEvent>
#include <QDebug>
#include <QGraphicsItem>
#include <QTimer>
#include <QGraphicsSceneDragDropEvent>
#include <QMessageBox>
#include <QTime>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void update();
    void update2();
    void count();


private:
    //my vars
    QTimer *timer;
    QTimer *advTimer;
    QTimer *stimer;

    QTimer *counter;
    QTime *time;

    QBrush *yellowBrush;

    int remLife;

    QGraphicsScene *scene;
    QGraphicsLineItem *grayLine;
    QGraphicsLineItem *blackLine;
    QGraphicsEllipseItem *yelEllipse;
    QRectF *rect;

    qreal angle;

    qreal deltaX;
    qreal deltaY;

    static const qreal offset = 25;
    static const int millisec = 300;
    static const int lineWidth = 6;

protected:
    void keyPressEvent(QKeyEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent* event);
    void advance(int phase);
private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
