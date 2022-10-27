#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsItem>
#include <QBitmap>
#include <QTimer>
#include <QDebug>
#include <QPen>
#include <cmath>

void normalize(QPointF &point){
    qreal len=sqrt(point.x()*point.x()+point.y()*point.y());
    point/=len;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    ball = new Ball(scene);
    QPixmap pixCar("F:\\lab7_qt\\car.png");
    car=scene->addPixmap(pixCar.scaledToWidth(300));
    car->setPos(130,170);
    car->setFlags(QGraphicsItem::ItemIsMovable);
    car->setZValue(1);
    car->setData(0,"Car");
    car->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    QPixmap pixMan("F:\\lab7_qt\\man.png");
    man=scene->addPixmap(pixMan.scaled(100,75));
    man->setFlags(QGraphicsItem::ItemIsMovable);
    man->setPos(187,160);
    man->setData(0,"Man");
    wheel1 = scene->addEllipse(169,254,25,25,QPen(Qt::black),QBrush(Qt::black));
    wheel2 = scene->addEllipse(346,254,25,25,QPen(Qt::black),QBrush(Qt::black));
    wheel1->setFlags(QGraphicsItem::ItemIsMovable);
    wheel1->setData(0,"Wheel");
    wheel1->setData(1,"1");
    wheel2->setFlags(QGraphicsItem::ItemIsMovable);
    wheel2->setData(0,"Wheel");
    wheel2->setData(1,"2");

    float walls[4][4] = {{0,0,20,500},
                         {20,0,620,20},
                         {625,0,20,500},
                         {20,480,620,20}};
    QString dir[4]={"Left","Up","Right","Down"};
    for (int i =0; i < 4; i++){
        QGraphicsRectItem* pWall = scene->addRect(QRectF(walls[i][0],walls[i][1],walls[i][2],walls[i][3]),QPen(Qt::NoPen),QBrush(Qt::green));
        pWall->setData(0,"Wall");
        pWall->setData(1,dir[i]);
    }
    QTimer* timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()), this, SLOT(update()));
    timer->start(20);
}

void MainWindow::update(){
    ball->move();
    QList<QGraphicsItem*> collisions = scene->collidingItems(ball->model());
    foreach (QGraphicsItem* it, collisions) {
        if(it==ball->model()) continue;
        if(it->data(0)=="Wall") ball->handleCollisions(it->data(1).toString());
        else if(it->data(0)=="Wheel"){
            if(it->data(1)=="1") ball->handleCollisions(wheel1,QPointF(169,254));
            else if(it->data(1)=="2") ball->handleCollisions(wheel2,QPointF(346,254));
        }
        else if(it->data(0)=="Car") ball->handleCollisions(car);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
