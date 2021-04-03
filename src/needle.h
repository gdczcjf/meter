#ifndef NEEDLE_H
#define NEEDLE_H

#include <QGraphicsItem>

class Needle : public QGraphicsItem
{
public:
    Needle();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    void glitter();

};

#endif // NEEDLE_H
