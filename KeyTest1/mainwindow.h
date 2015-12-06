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

private:
    //my vars
    QTimer *timer;

    QGraphicsScene *scene;
    QGraphicsLineItem *grayLine;
    QGraphicsLineItem *blackLine;
    QGraphicsEllipseItem *yelEllipse;
    QRectF *rect;

    qreal angle;

    qreal deltaX;
    qreal deltaY;

    static const qreal offset = 25;
    static const int millisec = 20;
    static const int lineWidth = 6;

protected:
    void keyPressEvent(QKeyEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent* event);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
