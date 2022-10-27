#ifndef BALL_H
#define BALL_H

#include <QGraphicsItem>
#include <QVector2D>
#include <QGraphicsScene>

class Ball
{
    QGraphicsEllipseItem* _model;
    QVector2D *velocity;
    qreal scale;
public:
    Ball();
    Ball(QGraphicsScene *scene);
    void move();
    void handleCollisions(QString wall);
    void handleCollisions(QGraphicsEllipseItem *wheel);
    void handleCollisions(QGraphicsPixmapItem *car);
    QGraphicsEllipseItem* model();
};

#endif // BALL_H
