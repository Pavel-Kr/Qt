#include "ball.h"
#include <QDebug>

Ball::Ball()
{

}

Ball::Ball(QGraphicsScene *scene)
{
    _model=scene->addEllipse(0,0,20,20,QPen(Qt::black),QBrush(Qt::red));
    _model->moveBy(50,50);
    velocity = new QVector2D(5,3);
    scale=velocity->length();
    velocity->normalize();
    radius = 10;
}

void Ball::move()
{
    _model->moveBy(velocity->x()*scale,velocity->y()*scale);
}

QPointF getCenter(QGraphicsEllipseItem *circle)
{
    QPointF center = circle->pos();
    center.setX(center.x() + circle->boundingRect().width()/2);
    center.setY(center.y() + circle->boundingRect().width()/2);
    return center;
}

void Ball::handleCollisions(QGraphicsEllipseItem *wheel)
{
    _model->moveBy(-velocity->x()*scale, -velocity->y()*scale);
    QPointF ballcenter = getCenter(_model);
    QPointF wheelcenter = getCenter(wheel);
    QVector2D centerVec(ballcenter - wheelcenter);
    qreal dot = QVector2D::dotProduct(*velocity, centerVec);
    qreal len = centerVec.lengthSquared();
    QVector2D newVel = *velocity - centerVec * (dot / len);
    *velocity = newVel.normalized();
    move();
}

bool intersects(QPointF ballCenter, qreal radius, QPointF lineBegin, QPointF lineEnd){
    qreal a = (lineEnd.x()-lineBegin.x())*(lineEnd.x()-lineBegin.x())+(lineEnd.y()-lineBegin.y())*(lineEnd.y()-lineBegin.y());
    qreal b = (lineEnd.x()-lineBegin.x())*(lineBegin.x()-ballCenter.x()) + (lineEnd.y()-lineBegin.y())*(lineBegin.y()-ballCenter.y());
    qreal c = (lineBegin.x()-ballCenter.x())*(lineBegin.x()-ballCenter.x()) + (lineBegin.y()-ballCenter.y())* (lineBegin.y()-ballCenter.y()) - radius*radius;
    qreal d = 4*b*b - 4*a*c;
    if(d<0) return false;
    qreal t1 = (-2*b + sqrt(d)) / (2*a);
    qreal t2 = (-2*b - sqrt(d)) / (2*a);
    if(t1>=0 && t1<=1 || t2>=0 &&t2<=1) return true;
    return false;
}

void Ball::handleCollisions(QGraphicsPixmapItem *pix)
{
    QPointF ballcenter = getCenter(_model);
    QPointF pixCenter = pix->boundingRect().center()+pix->pos();
    QPointF topleft=pix->boundingRect().topLeft()+pix->pos();
    QPointF bottomleft=pix->boundingRect().bottomLeft()+pix->pos();
    QPointF bottomright=pix->boundingRect().bottomRight()+pix->pos();
    QPointF topright=pix->boundingRect().topRight()+pix->pos();
    if(ballcenter.x()<=pixCenter.x() && ballcenter.y()>=pixCenter.y()){
        //BottomLeft
        if(intersects(ballcenter,radius,topleft,bottomleft)){
            _model->moveBy(-velocity->x()*scale, -velocity->y()*scale);
            velocity->setX(-velocity->x());
        }
        else if(intersects(ballcenter,radius,bottomleft,bottomright)){
            _model->moveBy(-velocity->x()*scale, -velocity->y()*scale);
            velocity->setY(-velocity->y());
        }
    }
    else if(ballcenter.x()<=pixCenter.x() && ballcenter.y()<=pixCenter.y()){
        //TopLeft
        if(intersects(ballcenter,radius,topleft,bottomleft)){
            _model->moveBy(-velocity->x()*scale, -velocity->y()*scale);
            velocity->setX(-velocity->x());
        }
        else if(intersects(ballcenter,radius,topleft,topright)){
            _model->moveBy(-velocity->x()*scale, -velocity->y()*scale);
            velocity->setY(-velocity->y());
        }
    }
    else if(ballcenter.x()>=pixCenter.x() && ballcenter.y()<=pixCenter.y()){
        //TopRight
        if(intersects(ballcenter,radius,topright,bottomright)){
            _model->moveBy(-velocity->x()*scale, -velocity->y()*scale);
            velocity->setX(-velocity->x());
        }
        else if(intersects(ballcenter,radius,topleft,topright)){
            _model->moveBy(-velocity->x()*scale, -velocity->y()*scale);
            velocity->setY(-velocity->y());
        }
    }
    else if(ballcenter.x()>=pixCenter.x() && ballcenter.y()>=pixCenter.y()){
        //BottomRight
        if(intersects(ballcenter,radius,topright,bottomright)){
            _model->moveBy(-velocity->x()*scale, -velocity->y()*scale);
            velocity->setX(-velocity->x());
        }
        else if(intersects(ballcenter,radius,bottomleft,bottomright)){
            _model->moveBy(-velocity->x()*scale, -velocity->y()*scale);
            velocity->setY(-velocity->y());
        }
    }
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
