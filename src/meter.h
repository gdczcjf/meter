#ifndef METER_H
#define METER_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsProxyWidget>
#include <QTimer>

#include "metertype.h"
#include "graphicsitem.h"
#include "needle.h"
#include "meteroption.h"
#include "meterscale.h"

struct AdjustData
{
    int ADzero;
    double ADFactor;
};


class Meter : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    int ID;
    int ADIndex;
    static Meter *meters[4];
    double sampleCycle;
    QVector<double> ValueSamples;

    Meter();
    ~Meter()
    {
       menu.setWidget(0);
    }
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);

    QString getChannelName();
    QString getValueText(double value);
    QString getValueText();

    double getValue(int adValue);
    double getValue();
    void getAngle();
    bool isOutOfRange();
    MeterType getType();


signals:
    void sampleProgress(int percent);
    
public slots:
    void showAndHideMenu();
    void turnOff();
    void setShowWay(bool fullScreen);
    void choiceCh();
    void choiceRange();
    void showAdjustWin();
    void dispValue(bool disp);
    void sample();
    void recordValue();
    void recordAllMetersValue();
    void deleteRecord();

protected:
    void advance(int step);
    void mousePressEvent ( QGraphicsSceneMouseEvent * event );

private:

    static int fd;
    static int ID_Count;
    static QPixmap *pPixmapMeterFrame;
    static QPixmap *pPixmapAdjustButton;
    /****校准值****/
    static AdjustData adjustDatas[21];



    QRectF rectF;
    MeterScale scale;
    GraphicsItem frame;
    GraphicsItem adjustButton;
    Needle needle;
    QGraphicsProxyWidget menu;
    MeterOption meterOption;
    QGraphicsTextItem channelText;
    QGraphicsTextItem rangeText;
    QGraphicsTextItem valueText;



    MeterType type;
    QString channelName;
    QString meterName;

    bool isDisplayValue;

    int *pADValue;
    double valueFactor;
    double valueMin;
    double valueMax;
    double valueMax2Min;
    double *pADFactor; //
    int *pADzero;


    double value;
    qreal angleTrue;
    qreal angle;//


    void setType(MeterType type);

    void saveSetting();
    void readSetting();
    void recoverSetting();

    void setADzero();
    void setADfactor();

    void setRandomZero();

private slots:

    
};

#endif // METER_H
