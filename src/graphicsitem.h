#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H


#include <QGraphicsItem>
#include <QPainter>
#include <QObject>

class GraphicsItem :public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    GraphicsItem(QPixmap* pNewPixmap = 0,qreal centreX=0,qreal centreY=0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
    void setPic(QPixmap* pPixmapBottom,qreal centreX=0,qreal centreY=0);

protected:
    void mousePressEvent ( QGraphicsSceneMouseEvent *);

private:
    QPixmap* pPixmap;

    QRectF picRect;
    QRectF dispRect;

signals:
    void mousePress();
};

#endif // GRAPHICSITEM_H
