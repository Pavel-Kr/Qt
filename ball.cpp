#include "ball.h"
#include <QDebug>

Ball::Ball()
{

}

Ball::Ball(QGraphicsScene *scene)
{
    _model=scene->addEllipse(0,0,20,20,QPen(Qt::black),QBrush(Qt::red));
    _model->moveBy(50,50);
    qDebug()<<_model->pos();
    velocity = new QVector2D(5,3);
    scale=velocity->length();
    velocity->normalize();
}

void Ball::move()
{
    _model->moveBy(velocity->x()*scale,velocity->y()*scale);
}

void Ball::handleCollisions(QGraphicsEllipseItem *wheel)
{
    _model->moveBy(-velocity->x()*scale, -velocity->y()*scale);
    QPointF ballcenter = _model->pos();
    QPointF wheelcenter = wheel->pos();
    ballcenter.setX(ballcenter.x() + _model->boundingRect().width()/2);
    ballcenter.setY(ballcenter.y() + _model->boundingRect().width()/2);
    wheelcenter.setX(wheelcenter.x() + wheel->boundingRect().width()/2);
    wheelcenter.setY(wheelcenter.y() + wheel->boundingRect().width()/2);
    QVector2D centerVec(ballcenter - wheelcenter);
    qreal dot = QVector2D::dotProduct(*velocity, centerVec);
    qreal len = centerVec.lengthSquared();
    QVector2D newVel = *velocity - centerVec * (dot / len);
    *velocity = newVel.normalized();
    move();
}

void Ball::handleCollisions(QGraphicsPixmapItem *car)
{
    velocity->setX(-velocity->x());
    velocity->setY(-velocity->y());
}

QGraphicsEllipseItem *Ball::model()
{
    return _model;
}

void Ball::handleCollisions(QString wall)
{
    if(wall=="Left") velocity->setX(-velocity->x());
    else if(wall=="Up") velocity->setY(-velocity->y());
    else if(wall=="Right") velocity->setX(-velocity->x());
    else if(wall=="Down") velocity->setY(-velocity->y());
}
