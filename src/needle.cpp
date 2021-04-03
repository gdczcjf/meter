#include <QPainter>
#include <QStyleOption>
#include <QtGui>

#include "needle.h"
/*
const QPointF point[4]={
    QPointF(-360,-1),
    QPointF(-360,1),
    QPointF(0,3),
    QPointF(0,-3),
};*/

//指针根部
const QPointF shape_1[4]={
    QPointF(-240,-5/3),
    QPointF(-240,5/3),
    QPointF(-60,3),
    QPointF(-60,-3),
};
//指针尖部
const QPointF shape_2[4]={
    QPointF(-345,-1),
    QPointF(-345,1),
    QPointF(-240,5/3),
    QPointF(-240,-5/3),
};

Needle::Needle()
{
}


QRectF Needle::boundingRect() const
{
    const qreal adjust = 0.5;
    return QRectF(-360 -
                  adjust, -3 - adjust,
                 360 + adjust, 6 + adjust);

}

void Needle::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QColor color;


   painter->setRenderHint(QPainter::Antialiasing);

   color.setRgb(0xEA/2,0xE8/2,0xFA/2);
   painter->setPen(QPen(color));
   painter->setBrush(QBrush(color));
   painter->drawPolygon(shape_1,4,Qt::OddEvenFill);

   color.setRgb(155,0,0);
   painter->setPen(QPen(color));
   painter->setBrush(QBrush(color));
   painter->drawPolygon(shape_2,4,Qt::OddEvenFill);

}

void Needle::glitter()
{
    static qreal scale=1;
    scale *= 0.7;
    if(scale < 0.05)
        scale=1;
   this->setOpacity(scale);
}

