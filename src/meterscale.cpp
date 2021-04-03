#include "meterscale.h"


const int radius=320;

const int longLine=30;
const int mediumLine=16;
const int shortLine=9;



MeterScaleInfo meterScaleInfo[]=
{
    /*
    bigScaleCount;//最大刻度包括多少个最小刻度
    mediumScaleCount;//中等刻度包括多少个最小刻度
    smallScaleCount;//最小刻度数

    minAbove;
    scaleValueAbove;
    minUnder;
    scaleValueUnder;

    symble;
    */
    {10,    5,      40,     0.0,    5.0,    0.0,    0.0,    "V",    -30},   //U1_200V =   1,
    {10,    5,      40,     -5.0,   0.5,    -1.0,   0.1,    "V",    -30},   //U1_15V  =   2,
    {10,    5,      40,     -5.0,   0.5,    -1.0,   0.1,    "V",    -30},   //U1_3V   =   3,
    {10,    5,      40,     -200.0, 10.0,   0.0,    0.0,    "mV",   20},  //U1_200mV=   4,
    {10,    5,      40,     -1.0,   0.1,    -0.2,   0.02,   "A",    -30},   //I1_3A  =   5,
    {10,    5,      40,     -1.0,   0.1,    -0.2,   0.02,   "A",    -30},   //I1_0A6  =   6,
    {10,    5,      50,     0.0,    1.0,    0.0,    0.1,    "mA",   20},  //I1_50mA =   7,
    {10,    5,      50,     0.0,    1.0,    0.0,    0.1,    "mA",   20},  //I1_5mA  =   8,
    {10,    5,      60,     0.0,    5.0,    0.0,    0.0,    "G",    -30},  //I1_300uA=   9,
    {5,     5,      50,     -50.0,  2.0,    0.0,    0.0,    "uA",   6},  //I1_50uA =   10,
};






MeterScale::MeterScale(QObject *parent) :
    QObject(parent)
{
    scaleInfo=0;
}

QRectF MeterScale::boundingRect() const
{
    return QRect(-400,-420,800,480);
}

void MeterScale::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPen pen;
    pen.setWidth(2);
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing);
    if(scaleInfo==0)
    {
        pen.setWidth(4);
        painter->setPen(pen);
        painter->drawRoundedRect(-390,-410,780,460,30,30);
        painter->drawRoundedRect(-100,-240,200,120,20,20);
        pen.setWidth(6);
        painter->setPen(pen);
        painter->drawLine(0,-220,0,-140);
        painter->drawLine(-40,-180,40,-180);
    }
    else
    {
        QFont font;
        font.setPointSize(72);
        painter->setFont(font);
        painter->drawText(-100,-220,200,100,Qt::AlignCenter,scaleInfo->symble);

        pen.setWidth(4);
        painter->setPen(pen);
        painter->drawLine(scaleInfo->lineStartX,-120,scaleInfo->lineStartX+60,-120);
        pen.setStyle(Qt::DashLine);
        pen.setWidth(4);
        painter->setPen(pen);
        painter->drawLine(scaleInfo->lineStartX,-110,scaleInfo->lineStartX+60,-110);
        pen.setStyle(Qt::SolidLine);
        pen.setWidth(2);
        painter->setPen(pen);

        font.setPointSize(18);
        painter->setFont(font);
        //////////////////////////
        painter->drawArc(-radius,-radius,radius*2,radius*2,30*16,120*16);
        painter->rotate(-60);
        painter->drawLine(0,longStart,0,longEnd);

        for(int i=0; i <= scaleInfo->smallScaleCount ;i++ )
        {

            if(i%scaleInfo->bigScaleCount==0)
            {
                painter->drawLine(0,longStart,0,longEnd);
                //上
                if(scaleInfo->scaleValueAbove!=0)
                    painter->drawText(-30,longStart-25,60,20,Qt::AlignCenter,QString::number(scaleInfo->minAbove+i*scaleInfo->scaleValueAbove));
                //下
                if(scaleInfo->scaleValueUnder!=0)
                    painter->drawText(-30,longEnd+8,60,20,Qt::AlignCenter,QString::number(scaleInfo->minUnder+i*scaleInfo->scaleValueUnder));
            }
            else if(i%scaleInfo->mediumScaleCount==0)
                painter->drawLine(0,mediumStart,0,mediumEnd);
            else
                painter->drawLine(0,shortStart,0,shortEnd);


            painter->rotate(120.0/(double)scaleInfo->smallScaleCount);
        }



    }

}

void MeterScale::mousePressEvent ( QGraphicsSceneMouseEvent *)
{
   emit mousePress();
}

void MeterScale::setScaleInfo(MeterType meterType)
{
    if(meterType==OFF)
        scaleInfo=0;
    else
    {
        int typeNum = (int)meterType;
        if(typeNum<11)
        {
            scaleInfo = &meterScaleInfo[typeNum-1];
        }
        else if(typeNum<21)
        {
            scaleInfo = &meterScaleInfo[typeNum-11];
        }

    }

    if(scaleInfo !=0 )
    {
        if(scaleInfo->scaleValueAbove==0)
        {
           longStart = mediumStart = shortStart = -radius;
        }
        else
        {
             longStart = -radius-longLine;
             mediumStart = -radius-mediumLine;
             shortStart = -radius-shortLine;
        }
        if(scaleInfo->scaleValueUnder ==0)
        {
            longEnd = mediumEnd = shortEnd = -radius;
        }
        else
        {
            longEnd = -radius +longLine;
            mediumEnd = -radius + mediumLine;
            shortEnd = -radius + shortLine;
        }
    }
}
