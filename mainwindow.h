#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPixmap>
#include <QVector2D>
#include "ball.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Ball *ball;
    QGraphicsEllipseItem *wheel1, *wheel2;
    QGraphicsPixmapItem *car;
    QGraphicsPixmapItem *man;

private slots:
    void update();
};

#endif // MAINWINDOW_H
