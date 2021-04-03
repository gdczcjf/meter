#ifndef HARDWARE_H
#define HARDWARE_H

#include <QObject>
#include <QTimer>
#include "metertype.h"

class HardWare : public QObject
{
    Q_OBJECT
public:
    explicit HardWare(QObject *parent = 0);
    

    static HardWare *pHardWare;
    static QTimer *pTimer;
    static int iofd;
    static int adcfd;
    static int AD[4];
    static bool U1_used;
    static bool I1_used;
    static bool U2_used;
    static bool I2_used;

    static void init();
    static void selcetRelay(int adIndex);
    static bool isChUsed(int adIndex);
    static void setADCycle(int ms);
    static void openADCDev();
    static void closeADCDev();
    static void openIODev();
    static void closeIODev();

    static void closeChanle(MeterType oldType);
    static void connectChannel(MeterType oldType,MeterType newType);

    //static int getADValueOnce();

signals:
    
public slots:
    static void getADValue();    
};
#endif // HARDWARE_H
