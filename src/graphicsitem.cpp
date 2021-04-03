#include "graphicsitem.h"

GraphicsItem::GraphicsItem(QPixmap* pNewPixmap,qreal centreX, qreal centreY)
{
    setPic(pNewPixmap,centreX,centreY);
}



QRectF GraphicsItem::boundingRect() const
{
    return dispRect;
}
void GraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(dispRect,*pPixmap,picRect);
}

void GraphicsItem::setPic(QPixmap* pNewPixmap,qreal centreX,qreal centreY)
{
    pPixmap=pNewPixmap;
    if(pPixmap != 0)
    {
        picRect.setRect(0.0 , 0.0 ,pPixmap->width() ,  pPixmap->height() );
        dispRect.setRect(-centreX , -centreY ,pPixmap->width() ,  pPixmap->height() );
    }
    update();
}

void GraphicsItem::mousePressEvent ( QGraphicsSceneMouseEvent *)
{
   emit mousePress();
}


