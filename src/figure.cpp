#include <QMessageBox>
#include <QTextItem>
#include "math.h"

#include "figure.h"

//函数名和积分值显示位置
const int text_x = 35;
const int text_y = 373;

//画布大小
const int figure_width = 575;
const int Figure_height= 385;
//画图区域
const int xMin=20;
const int yMin=20;
const int xMax=500;
const int yMax=350;

Figure::Figure(QWidget *parent) :
    QWidget(parent)
{
    pFigure = new QPixmap(figure_width,Figure_height);

    cleanFigure();
    /***********************
    xMaxValue=5;
    xMinValue=5;
    yMaxValue=20;
    yMinValue=2;
    this->isDrawGrid = false;
    this->startFromNonzero = false;


    QPainter painter(pFigure);
     painter.setFont(QFont("wenquanyi",6));
    drawCooSys(&painter);

    ***********************/
}
Figure::~Figure()
{
    delete pFigure;
}


void Figure::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.drawPixmap(0,0,*pFigure);
}

void Figure::cleanFigure()
{
    pFigure->fill();
    update();
}

void Figure::drawFigure(QVector<double> *xValue,
                QVector<double> *yValue,
                int drawLineWay,
                bool isDrawGrid,
                bool showIntegral,
                bool startFromNonzero)
{
    if(check(xValue,yValue)==false)
        return;
    //
    this->drawLineWay = drawLineWay;
    this->isDrawGrid = isDrawGrid;
    this->showIntegral = showIntegral;
    this->startFromNonzero = startFromNonzero;
    //
    vectorMaxMin(xValue,&xMaxValue,&xMinValue);
    vectorMaxMin(yValue,&yMaxValue,&yMinValue);
    //
    pFigure->fill();
    QPainter painter(pFigure);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setFont(QFont("wenquanyi",6));
    drawCooSys(&painter);
    painter.setPen(Qt::blue);
    drawPoints(&painter,xValue,yValue);
    painter.setPen(Qt::black);
    painter.setFont(QFont("wenquanyi",9));
    painter.setPen(Qt::red);
    switch(drawLineWay)
    {
    case 0:
        break;
    case 1:
        drawLines(&painter);
        break;
    case 2:
        drawStraightLine(&painter);
        break;
    case 3:
        drawLine_2(&painter);
        break;
    case 4:
        drawLine_05(&painter);
        break;
    }


    this->update();

}


bool Figure::check(QVector<double> *xValue,QVector<double> *yValue)
{
    if(xValue==0 || yValue==0)
    {
        this->xValue=0;
        this->yValue=0;
        return false;
    }
    else if(xValue->count() != yValue->count())
    {
        QMessageBox msgBox;
        msgBox.setText("数据个数不相等");
        msgBox.exec();
        this->xValue=0;
        this->yValue=0;
        return false;
    }
    else if(xValue->count()==0 || xValue->count()==0)
    {
        QMessageBox msgBox;
        msgBox.setText("没有数据");
        msgBox.exec();
        this->xValue=0;
        this->yValue=0;
        return false;
    }
    this->xValue=xValue;
    this->yValue=yValue;
    return true;
}

void Figure::vectorMaxMin(QVector<double> *values,double *max,double *min)
{
    double maxTemp,minTemp;
    maxTemp = values->at(0);
    minTemp = values->at(0);
    for(int i=1; i<values->count(); i++)
    {
        if(values->at(i)>maxTemp)
        {
            maxTemp=values->at(i);
        }
        if(values->at(i)<minTemp)
        {
            minTemp=values->at(i);
        }
    }
    *max=maxTemp;
    *min=minTemp;
}


double Figure::calcGridValue(double max,double min,bool startFromNonZero)//把坐标等成最多13，最少5等分
{
    if(min>max)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("程序错误");
        msgBox.setText("Figure::calcGridValue max<min");
        msgBox.exec();
        return 0;
    }
    if(max==min)//特殊情况
    {
        if(max == 0)
            return 0.1;
        else if(max >0)
            return  max;
        else if(max <0)
            return -max;
    }

    double range,GridValue;
    if(startFromNonZero)
    {
        range = ( max-min );
    }
    else
    {
        if(max>0 && min>0)
            range = max;
        else if(max<0 && min<0)
            range = -min;
        else
            range = max -min;
    }
    GridValue=1;
    if(range >= 10.0)
    {
        while(range >= 10.0)
        {
            range /= 10.0;
            GridValue *= 10.0;
        }
    }
    else if(range < 1.0)
    {
        while(range < 1.0)
        {
            range *= 10.0;
            GridValue /= 10.0;
        }
    }


    if(range < 2.5)
    {
        GridValue /= 5.0;
    }
    else if(range < 5)
    {
        GridValue /= 2.0;
    }
    return GridValue;
}

void  Figure::calculateScale(double max,double min,double *GridValue,double *start,int *posNum,int *nagNum,bool startFromNonZero)
{
    if(min>max)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("程序错误");
        msgBox.setText("Figure::calculateScale() max<min");
        msgBox.exec();
        return;
    }

    if(min == max)//特殊情况
    {

        *start =0.0f;
        (*GridValue) = calcGridValue(max,min,startFromNonZero);
        if(min==0)
        {
            *posNum = 1;
            *nagNum = 1;
        }
        else if(min>0)
        {
            *posNum = 2;
            *nagNum = 0;
        }
        else
        {
            *posNum = 0;
            *nagNum = 2;
        }
        return;
    }

    //是否从零开始
    bool startNonZero = false;
    if(startFromNonZero == true)
    {
        if((min > 0 && max >0 && min/max > 1.0/4.0)||
            (min <0 && max<0 && max/min > 1.0/4.0 ))
        {
            startNonZero = true;
        }
    }
    //计算每格值
    *GridValue = calcGridValue(max,min,startNonZero);
    //正负格数据
    if(startNonZero)//从非零开始
    {
        if(min>0)
        {
            *start =  ((int)(min/(*GridValue))) * (*GridValue);
            *posNum = (int)ceil((max-*start)/(*GridValue));
            *nagNum = 0;
        }
        else if(max<0)
        {
            *start =  ((int)(max/(*GridValue))) * (*GridValue);
            *posNum = 0;
            *nagNum = (int)ceil((*start-min)/(*GridValue));
        }
    }
    else//从零开始
    {
        *start = 0.0f;
        if(min<0 && max>0)
         {
             *posNum = (int)ceil(max/(*GridValue));
             *nagNum = (int)ceil(-min/(*GridValue));
         }
        else if(min >=0)
        {
            *posNum = (int)ceil(max/(*GridValue));
            *nagNum = 0;
        }
        else if(max <= 0)
        {
            *posNum = 0;
            *nagNum = (int)ceil(-min/(*GridValue));
        }
    }
}
QString Figure::numberToText(double num)
{
    if(num >= 0.1 || num<= -0.1)
        return QString::number(num);
    else if(num >=0.001 || num <= -0.001)
        return QString::number(num*1000)+"m";
    else
        return QString::number(num*1000000)+"u";
}


void Figure::drawCooSys(QPainter *painter)
{
    int xPNum; //x正半轴刻度数
    int xNNum; //x负半轴刻度数
    int yPNum; //y正半轴刻度数
    int yNNum; //y负半轴刻度数
    double xGridValue;//一格刻度数值
    double yGridValue;//一格刻度数值
    int xGridPix;
    int yGridPix;

    calculateScale(xMaxValue,xMinValue,&xGridValue,&x_start,&xPNum,&xNNum,startFromNonzero);
    calculateScale(yMaxValue,yMinValue,&yGridValue,&y_start,&yPNum,&yNNum,startFromNonzero);

    xGridPix = (xMax-xMin-30)/(xPNum+xNNum);
    yGridPix = (yMax-yMin-30)/(yPNum+yNNum);

    xfactor=xGridValue/xGridPix;
    yfactor=yGridValue/yGridPix;

    origin_x = xMin+xGridPix*xNNum+10;
    origin_y = yMax-yGridPix*yNNum-10;
    /******x箭头*******/
    painter->drawLine(xMin,origin_y,xMax,origin_y);
    painter->drawLine(xMax,origin_y,xMax-5,origin_y+5);
    painter->drawLine(xMax,origin_y,xMax-5,origin_y-5);
    painter->drawText(xMax+2,origin_y,"X");
    /**y箭头**/
    painter->drawLine(origin_x,yMax,origin_x,yMin);
    painter->drawLine(origin_x,yMin,origin_x-5,yMin+5);
    painter->drawLine(origin_x,yMin,origin_x+5,yMin+5);
    painter->drawText(origin_x,yMin-5,"Y");


    //原点和刻度

    if(x_start==0 && y_start==0)
    {
        painter->drawText(origin_x+2,origin_y+10,"0");

    }
    else
    {                                                 
        //x起点
        painter->drawText(origin_x-15,origin_y+10+2,30,10,Qt::AlignHCenter,numberToText(x_start));
        //Y起点
        painter->drawText(origin_x-40-10,origin_y-5,40,10,Qt::AlignRight,numberToText(y_start));

    }

    if(isDrawGrid)//网格
    {


        for(int i=1;i<=xPNum;i++)
        {
            //y方向网格
            //painter->setPen(Qt::darkGray);
            painter->setPen(Qt::DotLine);
            painter->drawLine(origin_x+i*xGridPix,origin_y-yPNum*yGridPix,origin_x+i*xGridPix,origin_y+yNNum*yGridPix);
            //x轴刻度
            //painter->setPen(Qt::black);
            painter->setPen(Qt::SolidLine);
            painter->drawText(origin_x+i*xGridPix+2,origin_y+2,30,10,Qt::AlignLeft,numberToText(x_start+xGridValue*i));

        }
        for(int i=1;i<=xNNum;i++)
        {
            //painter->setPen(Qt::darkGray);
            painter->setPen(Qt::DotLine);
            painter->drawLine(origin_x-i*xGridPix,origin_y-yPNum*yGridPix,origin_x-i*xGridPix,origin_y+yNNum*yGridPix);
            //painter->setPen(Qt::black);
            painter->setPen(Qt::SolidLine);
            painter->drawText(origin_x-i*xGridPix+2,origin_y+2,30,10,Qt::AlignLeft,numberToText(x_start-xGridValue*i));
        }
        for(int i=1;i<=yPNum;i++)
        {
            //x方向网格
            //painter->setPen(Qt::darkGray);
            painter->setPen(Qt::DotLine);
            painter->drawLine(origin_x-xNNum*xGridPix,origin_y-i*yGridPix,origin_x+xPNum*xGridPix,origin_y-i*yGridPix);
            //y轴刻度
            //painter->setPen(Qt::black);
            painter->setPen(Qt::SolidLine);
            painter->drawText(origin_x-40-2,origin_y-i*yGridPix-10-2,40,10,Qt::AlignRight,numberToText(y_start+yGridValue*i));

        }
        for(int i=1;i<=yNNum;i++)
        {
            //painter->setPen(Qt::darkGray);
            painter->setPen(Qt::DotLine);
            painter->drawLine(origin_x-xNNum*xGridPix,origin_y+i*yGridPix,origin_x+xPNum*xGridPix,origin_y+i*yGridPix);
            //painter->setPen(Qt::black);
            painter->setPen(Qt::SolidLine);
            painter->drawText(origin_x-40-2,origin_y+i*yGridPix-10-2,40,10,Qt::AlignRight,numberToText(y_start-yGridValue*i));
        }
        painter->setPen(Qt::SolidLine);
    }
    else//无网格
    {

        /*******************x************/

        /***刻度***/
        for(int i=1;i<=xPNum;i++)
        {
            painter->drawLine(origin_x+i*xGridPix,origin_y,origin_x+i*xGridPix,origin_y-3);
            painter->drawText(origin_x+i*xGridPix-15,origin_y+2,30,10,Qt::AlignHCenter,numberToText(x_start+xGridValue*i));

        }
        for(int i=1;i<=xNNum;i++)
        {
            painter->drawLine(origin_x-i*xGridPix,origin_y,origin_x-i*xGridPix,origin_y-3);
            painter->drawText(origin_x-i*xGridPix-15,origin_y+2,30,10,Qt::AlignHCenter,numberToText(x_start-xGridValue*i));
        }


        /*****y*********/

        /***刻度****/
        for(int i=1;i<=yPNum;i++)
        {
            painter->drawLine(origin_x,origin_y-i*yGridPix,origin_x+3,origin_y-i*yGridPix);
            painter->drawText(origin_x-40-2,origin_y-i*yGridPix-5,40,10,Qt::AlignRight,numberToText(y_start+yGridValue*i));

        }
        for(int i=1;i<=yNNum;i++)
        {
            painter->drawLine(origin_x,origin_y+i*yGridPix,origin_x+3,origin_y+i*yGridPix);
            painter->drawText(origin_x-40-2,origin_y+i*yGridPix-5,40,10,Qt::AlignRight,numberToText(y_start-yGridValue*i));
        }
    }
}

QPoint Figure::pixPoint(double x,double y)
{
    QPoint point;
    point.setX( (int)(origin_x + (x - x_start)/xfactor + 0.5) );
    point.setY( (int)(origin_y - (y - y_start)/yfactor + 0.5) );

    return point;
}

void Figure::drawPoint(QPainter *painter,double x,double y)
{
    int centre_x;
    int centre_y;
    centre_x = origin_x + (int)((x - x_start) / xfactor+0.5);
    centre_y = origin_y - (int)((y - y_start) / yfactor+0.5);

    /*//debug
    QMessageBox msgbox;
    QString str="x:"+QString::number(centre_x)+" y:"+QString::number(centre_y);
    msgbox.setText(str);
    msgbox.exec();
    */

    painter->drawLine(centre_x-4,centre_y-4,centre_x+4,centre_y+4);
    painter->drawLine(centre_x+4,centre_y-4,centre_x-4,centre_y+4);

}

void Figure::drawPoints(QPainter *painter,QVector<double> *xValue,QVector<double> *yValue)
{
    if(xValue== NULL || yValue==NULL)
        return;//error

    for(int i=0;i<xValue->count();i++)
    {
        drawPoint(painter,xValue->at(i),yValue->at(i));

    }
}

void Figure::drawLines(QPainter *painter)
{
    QPoint point_1,point_2;
    point_1=pixPoint(xValue->at(0),yValue->at(0) );

    for(int i=1; i<xValue->count(); i++)
    {
       point_2=pixPoint(xValue->at(i),yValue->at(i) );
       painter->drawLine(point_1,point_2);
       point_1=point_2;
    }

}


void Figure::drawStraightLine(QPainter *painter,double a,double b)//y=ax+b
{
    QPoint point_1,point_2;
    point_1=pixPoint(xMinValue, a*xMinValue + b);
    point_2=pixPoint(xMaxValue, a*xMaxValue + b);

    painter->drawLine(point_1,point_2);

}
void Figure::drawStraightLine(QPainter *painter)
{
    double a,b;

    if( linearAnaly(xValue,yValue,&a,&b) )
    {
        drawStraightLine(painter,a,b);
    }

    QPoint point;
    point.setX(text_x);
    point.setY(text_y);
    QString str= "函数：  y = " + QString::number(a)+" x + " + QString::number(b);
    if(showIntegral)
        str += "   积分值：" + QString::number((a/2.0*xMaxValue*xMaxValue + b *xMaxValue) - (a/2.0*xMinValue*xMinValue + b *xMinValue));
    painter->drawText(point,str);

}
bool Figure::linearAnaly(QVector<double> *x,QVector<double> *y,double *a, double *b)
{
    double mx,my,mxx,mxy;
    mx=0;
    my=0;
    mxx=0;
    mxy=0;

    if(x==NULL || y==NULL)
        return false;
    if(x->count()!=y->count())
        return false;

    for (int i=0;i<x->count();i++)
    {
        mx+=x->at(i);
        my+=y->at(i);
        mxx+=x->at(i)*x->at(i);
        mxy+=x->at(i)*y->at(i);
    }
    if(mx*mx-mxx*x->count()==0)
        return false;
    *a=(my*mx-mxy*x->count())/(mx*mx-mxx*x->count());
    *b=(my-mx*(*a))/x->count();
    return true;

}
bool Figure::linearAnaly_2(QVector<double> *x,QVector<double> *y,double *a, double *b, double *c)//y=a*x*x+b*x+c
{
    int i,j;
    double d[3][4];

    //对数组数据的初始化
    for (i = 0; i < 3; ++i)
        for (j = 0; j < 4; ++j)
            d[i][j] = 0.0;

        //算法的实现
        for (i = 0; i < x->count(); ++i)
        {
            d[0][0] = x->count();
            d[0][1] += x->at(i);
            d[0][2] += x->at(i) * x->at(i);
            d[0][3] += y->at(i);

            d[1][0] = d[0][1];
            d[1][1] = d[0][2];
            d[1][2] += x->at(i) * x->at(i) * x->at(i);
            d[1][3] += y->at(i) * x->at(i);

            d[2][0] = d[1][1];
            d[2][1] = d[1][2];
            d[2][2] += x->at(i) * x->at(i) * x->at(i) * x->at(i);
            d[2][3] += y->at(i) * x->at(i) * x->at(i);
        }

        for (i = 1; i < 3; ++i)
            for (j = 1; j < 4; ++j)
                d[i][j] -= d[0][j] * d[i][0] / d[0][0];

        //解三元线性方程组
        *b = (d[1][3] * d[2][2] - d[2][3] * d[1][2]) / (d[1][1] * d[2][2] - d[2][1] * d[1][2]);
        *a = (d[1][3] * d[2][1] - d[2][3] * d[1][1]) / (d[1][2] * d[2][1] - d[2][2] * d[1][1]);
        *c = (d[0][3] - d[0][1] * (*b) - d[0][2] * (*a)) / d[0][0];
    return true;
}


bool Figure::linearAnaly_05(QVector<double> *x,QVector<double> *y,double *a)//y=a/x
{
    int n;
    double sum;
    n = x->count();
    sum=0;
    for(int i=0;i<n;i++)
    {
        sum += x->at(i) * y->at(i);
    }
    *a=sum/n;
    return true;
}

void Figure::drawLine_05(QPainter *painter,double a)
{
    int x0,x1;
    QPoint point1,point2;
    point1 = pixPoint(xMinValue,0);
    point2 = pixPoint(xMaxValue,0);
    x0=point1.x();
    x1=point2.x();

    double x_temp;
    x_temp=pixValueX(x0);
    point1=pixPoint(x_temp,a/x_temp);
    for(int i=x0+1; i<=x1; i++)
    {
        x_temp=pixValueX(i);
        point2=pixPoint(x_temp,a/x_temp);
        painter->drawLine(point1,point2);
        point1=point2;
    }


    QPoint point;
    point.setX(text_x);
    point.setY(text_y);
    QString str= "函数：y = " + QString::number(a)+"/x";
    if(showIntegral)
        str += "   积分值："+QString::number(::log(xMaxValue)*a - ::log(xMinValue)*a);
    painter->drawText(point,str);

}


void Figure::drawLine_05(QPainter *painter)
{
    double a;
    if(linearAnaly_05(xValue,yValue,&a)==true)
    {
        drawLine_05(painter,a);
    }


}

void Figure::drawLine_2(QPainter *painter,double a,double b,double c)
{
    int x0,x1;
    QPoint point1,point2;
    point1 = pixPoint(xMinValue,0);
    point2 = pixPoint(xMaxValue,0);
    x0=point1.x();
    x1=point2.x();

    double x_temp;
    x_temp=pixValueX(x0);
    point1=pixPoint(x_temp,a*x_temp*x_temp + b*x_temp + c);
    for(int i=x0+1; i<=x1; i++)
    {
        x_temp=pixValueX(i);
        point2=pixPoint(x_temp,a*x_temp*x_temp + b*x_temp + c);
        painter->drawLine(point1,point2);
        point1=point2;
    }


    QPoint point;
    point.setX(text_x);
    point.setY(text_y);
    QString str= "函数： y = " + QString::number(a)+" x^2 +" + QString::number(b) + "x +" + QString::number(c);
    if(showIntegral)
        str += "   积分值："+QString::number((a/3.0*xMaxValue*xMaxValue*xMaxValue + b/2.0*xMaxValue*xMaxValue + c *xMaxValue) - (a/3.0*xMinValue*xMinValue*xMinValue +b/2.0*xMinValue*xMinValue + c *xMinValue));

    painter->drawText(point,str);

}

void Figure::drawLine_2(QPainter *painter)
{
    double a,b,c;
    if(linearAnaly_2(xValue,yValue,&a,&b,&c)==true)
    {
        drawLine_2(painter,a,b,c);
    }


}


double Figure::pixValueX(int x)
{

    return (x-origin_x)*xfactor+x_start;

}
double Figure::pixValueY(int y)
{
    return (origin_y-y)*yfactor+y_start;
}

bool isPointInDrawArea(int x, int y)
{
    if(x>xMin && x<xMax && y>yMin && y<yMax)
        return true;
    else
        return false;
}
