#ifndef FIGURE_H
#define FIGURE_H

#include <QWidget>

class Figure : public QWidget
{
    Q_OBJECT
public:
    explicit Figure(QWidget *parent = 0);
    ~Figure();

    void drawFigure(QVector<double> *xValue,
                    QVector<double> *yValue,
                    int drawLineWay,
                    bool isDrawGrid=false,
                    bool showIntegral=false,
                    bool startFromNonzero=false
            );
    void cleanFigure();
    
signals:
    
public slots:


protected:
    void paintEvent(QPaintEvent *);
private:
    QPixmap *pFigure;
    //设置
    int drawLineWay;
    bool isDrawGrid;
    bool showIntegral;
    bool startFromNonzero;

    //数据
    QVector<double> *xValue,*yValue;
    double xMaxValue,xMinValue,yMaxValue,yMinValue;
    double xfactor; //每像素长度对应值
    double yfactor; //每像素长度对应值
    double x_start; //坐标原点处x值
    double y_start; //坐标原点y值



    //坐标轴
    int origin_x; //原点像素坐标
    int origin_y;//原点像素坐标

    //分析
    bool check(QVector<double> *xValue,QVector<double> *yValue);
    void vectorMaxMin(QVector<double> *values,double *max,double *min);
    double calcGridValue(double max,double min,bool startFromNonZero);
    void calculateScale(double max,double min,double *GridValue,double *start,int *posNum,int *nagNum,bool startFromNonZero);

    //画图
    QString numberToText(double num);
    void drawCooSys(QPainter *painter);

    QPoint pixPoint(double x,double y);
    void drawPoint(QPainter *painter,double x,double y);
    void drawPoints(QPainter *painter,QVector<double> *xValue,QVector<double> *yValue);



    double pixValueX(int x); //从像素点得到对应值
    double pixValueY(int y);
    void drawLines(QPainter *painter);
    void drawStraightLine(QPainter *painter,double a,double b);//y=ax+b;
    void drawStraightLine(QPainter *painter);//拟合画直线
    void drawLine_05(QPainter *painter,double a);//画反比例曲线y=a/x;
    void drawLine_05(QPainter *painte);//拟合画反比例曲线
    void drawLine_2(QPainter *painter,double a , double b, double c);//画抛物线y=a*x*x + b*x + c;
    void drawLine_2(QPainter *painte);//拟合画抛物线
    bool linearAnaly(QVector<double> *x,QVector<double> *y,double *a, double *b);//y=ax+b
    bool linearAnaly_2(QVector<double> *x,QVector<double> *y,double *a, double *b, double *c);//y=ax2+bx+c
    bool linearAnaly_05(QVector<double> *x,QVector<double> *y,double *a);//y=a/x
    bool isPointInDrawArea(int x, int y);


    
};

#endif // FIGURE_H
