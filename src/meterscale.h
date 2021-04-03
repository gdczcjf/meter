#ifndef METERSCALE_H
#define METERSCALE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

#include "metertype.h"


class MeterScale : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit MeterScale(QObject *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
    void setScaleInfo(MeterType meterType);
private:
    MeterScaleInfo *scaleInfo;
    int longStart,longEnd;
    int mediumStart,mediumEnd;
    int shortStart,shortEnd;
protected:
    void mousePressEvent ( QGraphicsSceneMouseEvent *);

signals:
    void mousePress();
};

#endif // METERSCALE_H
