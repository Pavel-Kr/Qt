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
    qreal radius;
public:
    Ball();
    Ball(QGraphicsScene *scene);
    void move();
    void handleCollisions(QString wall);
    void handleCollisions(QGraphicsEllipseItem *wheel);
    void handleCollisions(QGraphicsPixmapItem *pix);
    QGraphicsEllipseItem* model();
};

#endif // BALL_H
