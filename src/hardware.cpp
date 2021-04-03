#include "hardware.h"

#include <stdio.h>
#include <fcntl.h>
#if IO_EN || ADC_EN
#include <sys/ioctl.h>
#endif

#include <QMessageBox>




#define IO_ON       0
#define IO_OFF      1

#define IO_U1_200V      3
#define IO_U1_15V       2
#define IO_U1_3V        1
#define IO_U1_200mV     0

#define IO_U2_200V      7
#define IO_U2_15V       6
#define IO_U2_3V        5
#define IO_U2_200mV     4


#define IO_I1_0A6       12
#define IO_I1_50mA      11
#define IO_I1_5mA       8
#define IO_I1_300uA     9
#define IO_I1_50uA      10

#define IO_I2_0A6       13
#define IO_I2_50mA      14
#define IO_I2_5mA       15
#define IO_I2_300uA     16
#define IO_I2_50uA      17


#define IO_U1   18
#define IO_U2   19
#define IO_I1   20
#define IO_I2   21



HardWare *HardWare::pHardWare=0;
QTimer *HardWare::pTimer;
int HardWare::iofd=-1;
int HardWare::adcfd=-1;
int HardWare::AD[4];
bool HardWare::U1_used = false;
bool HardWare::I1_used = false;
bool HardWare::U2_used = false;
bool HardWare::I2_used = false;

HardWare::HardWare(QObject *parent) :
    QObject(parent)
{
}



bool HardWare::isChUsed(int adIndex)
{
    switch(adIndex)
    {
    case 0:
        return I2_used;
    case 1:
        return I1_used;
    case 2:
        return U2_used;
    case 3:
        return U1_used;
    }
    return false;
}

void HardWare::setADCycle(int ms)
{
    if(ms <= 0)
    {
        pTimer->stop();
    }
    else if(ms < 2000)
    {
        pTimer->start(500);
    }
    else
        pTimer->start(ms/4);
}

void HardWare::init()
{

    if(pHardWare==0)
    {
        iofd=-1;
        adcfd=-1;
        HardWare::openIODev();
        HardWare::openADCDev();
        pHardWare = new HardWare();
        pTimer = new QTimer;
        QObject::connect(pTimer,SIGNAL(timeout()),pHardWare,SLOT(getADValue()));
    }
    setADCycle(1000);


#if IO_EN
    ioctl(iofd,IO_OFF,IO_U1_15V);
    ioctl(iofd,IO_OFF,IO_U1_3V);
    ioctl(iofd,IO_OFF,IO_U1_200mV);

    ioctl(iofd,IO_OFF,IO_U2_15V );
    ioctl(iofd,IO_OFF,IO_U2_3V);
    ioctl(iofd,IO_OFF,IO_U2_200mV);

    ioctl(iofd,IO_OFF,IO_I1_0A6);
    ioctl(iofd,IO_OFF,IO_I1_50mA);
    ioctl(iofd,IO_OFF,IO_I1_5mA);
    ioctl(iofd,IO_OFF,IO_I1_300uA);
    ioctl(iofd,IO_OFF,IO_I1_50uA);

    ioctl(iofd,IO_OFF,IO_I2_0A6);
    ioctl(iofd,IO_OFF,IO_I2_50mA);
    ioctl(iofd,IO_OFF,IO_I2_5mA);
    ioctl(iofd,IO_OFF,IO_I2_300uA);
    ioctl(iofd,IO_OFF,IO_I2_50uA);

    ioctl(iofd, IO_ON,IO_U1_200V);
    ioctl(iofd, IO_ON,IO_U2_200V);

    ioctl(iofd,IO_OFF,IO_U1);
    ioctl(iofd,IO_OFF,IO_U2);
    ioctl(iofd,IO_OFF,IO_I1);
    ioctl(iofd,IO_OFF,IO_I1);
#endif
}

void HardWare::openADCDev()
{

#if ADC_EN //打开ADC设备
        int retry=5;
        adcfd=-1;
        while((retry--)>0 && adcfd<0)
        {
            adcfd = ::open("/dev/adc", 0);
            if(adcfd<0)
            {
                sleep(1);
            }
        }
        if(adcfd<0)
        {       
            QMessageBox msg;
            msg.setText("打开ADC设备出错");
            msg.exec();
        }

 #endif
}
void HardWare::openIODev()
{
#if IO_EN
        /*********io***************************/
        iofd = open("/dev/leds0", 0);
        if (iofd < 0)
        {
            iofd = open("/dev/leds", 0);
        }
        if (iofd < 0)
        {
            QMessageBox msg;
            msg.setText("打开IO设备出错");
            msg.exec();
        }
        else
        {
            usleep(5000);
            closeChanle(U1_200V);
            closeChanle(U2_200V);
            closeChanle(I1_3A);
            closeChanle(I2_3A);
        }
#endif
}

void HardWare::closeADCDev()
{
#if ADC_EN 
    if (adcfd>0)
    {
        ::close(adcfd);
    }
#endif
}
void HardWare::closeIODev()
{
#if IO_EN
    if(iofd>0)
    {
        ::close(iofd);
    }
#endif
}


void HardWare::selcetRelay(int adIndex)
{

    static int oldAdIndex=4;
    static int oldIONum=IO_U1;
    if(oldAdIndex != adIndex)
    {
        if(adIndex>=0 && adIndex<=3 && iofd>0)
        {
#if IO_EN
            ioctl(iofd,IO_OFF,oldIONum);
#endif
            switch(adIndex)
            {
            case 0:
                oldIONum=IO_I2;
                break;
            case 1:
                oldIONum=IO_I1;
                break;
            case 2:
                oldIONum=IO_U2;
                break;
            case 3:
                oldIONum=IO_U1;
                break;
            }
            oldAdIndex=adIndex;
#if IO_EN
            ioctl(iofd,IO_ON,oldIONum);
#endif // IO_EN
            //usleep(500000);
        }
    }

}
/*
int  HardWare::getADValueOnce()
{
    int errorNum = 0;
#if ADC_EN

#else
    errorNum = 0;
    AD[0]=1040;
    AD[1]=512;
    AD[2]=256;
    AD[3]=128;
#endif
    return errorNum;
}
*/
void HardWare::getADValue()
{
#if ADC_EN

    static int isOdd=0;
    static int adNum=0;
    if(adcfd > 0)
    {
        if(isOdd==0)
        {

            for(int i=0;i<4;i++)
            {
                if(isChUsed(adNum)==true)
                    break;
                else
                {
                    adNum++;
                    if(adNum>3)
                    {
                        adNum=0;
                    }
                }
            }
            if(isChUsed(adNum)==true)
            {
              selcetRelay(adNum);
            }

            isOdd=1;
        }
        else
        {

            if(isChUsed(adNum)==true)
            {
               int max,min,sum;
               int dat[7];
               int num;
               num=0;


               ioctl(adcfd,0,adNum);

               for(int i=0; i<7;i++ )
               {
                   char buffer[30];
                   int len=0;
                   len = read(adcfd, buffer, sizeof buffer -1);
                   if(len>0)
                   {
                       int temp;
                       buffer[len] = '\0';
                       sscanf(buffer, "%d", &temp);
                       if(temp >0)
                       {
                           dat[num]= temp;
                           num++;
                       }
                   }
                   usleep(1000);

               }
               if(num!=0)
               {

                   sum=dat[0];
                   max=dat[0];
                   min=dat[0];

                   for(int i=1;i<7;i++)
                   {
                           if(dat[i]>max)
                                   max=dat[i];
                           if(dat[i]<min)
                                   min=dat[i];
                           sum+=dat[i];
                   }

                   AD[adNum]=(sum-max-min)/5;
               }
               adNum++;
               if(adNum>3)
               {
                   adNum=0;
               }
            }
            isOdd=0;
        }


    }
#else
    AD[0]=500;
    AD[1]=700;
    AD[2]=306;
    AD[3]=408;
#endif
}
void  HardWare::closeChanle(MeterType oldType)
{
    //关闭原通道
    if(oldType == 0)
    {
    }
    else if(oldType <= 4)
    {
#if IO_EN
        ioctl(iofd, 0,IO_U1_200V);
        ioctl(iofd, 1,IO_U1_15V);
        ioctl(iofd, 1,IO_U1_3V);
        ioctl(iofd, 1,IO_U1_200mV);
#endif //IO_EN
        U1_used = false;
    }
    else if(oldType <= 10)
    {
#if IO_EN
        ioctl(iofd, 1,IO_I1_0A6);
        ioctl(iofd, 1,IO_I1_50mA);
        ioctl(iofd, 1,IO_I1_5mA);
        ioctl(iofd, 1,IO_I1_300uA);
        ioctl(iofd, 1,IO_I1_50uA);
#endif //IO_EN
        I1_used = false;
    }
    else if(oldType <= 14)
    {
#if IO_EN
        ioctl(iofd, 0,IO_U2_200V);
        ioctl(iofd, 1,IO_U2_15V);
        ioctl(iofd, 1,IO_U2_3V);
        ioctl(iofd, 1,IO_U2_200mV);
#endif //IO_EN
        U2_used = false;
    }
    else if(oldType <= 20)
    {
#if IO_EN
        ioctl(iofd, 1,IO_I2_0A6);
        ioctl(iofd, 1,IO_I2_50mA);
        ioctl(iofd, 1,IO_I2_5mA);
        ioctl(iofd, 1,IO_I2_300uA);
        ioctl(iofd, 1,IO_I2_50uA);
#endif //IO_EN
        I2_used = false;
    }
    else
    {
        //error
        QMessageBox msg;
        msg.setText("内部错误，HardWare::closeChanle!");
        msg.exec();
    }
}


void  HardWare::connectChannel(MeterType oldType,MeterType newType)
{
    closeChanle(oldType);
#if IO_EN
    switch(newType)
    {
    case OFF:
        break;
    case U1_200V:
        ioctl(iofd, 1,IO_U1_15V);
        ioctl(iofd, 1,IO_U1_3V);
        ioctl(iofd, 1,IO_U1_200mV);
        ioctl(iofd, 0,IO_U1_200V);
        break;
    case U1_15V:
        ioctl(iofd, 1,IO_U1_200V);
        ioctl(iofd, 1,IO_U1_3V);
        ioctl(iofd, 1,IO_U1_200mV);
        ioctl(iofd, 0,IO_U1_15V);
        break;
    case U1_3V:
        ioctl(iofd, 1,IO_U1_200V);
        ioctl(iofd, 1,IO_U1_15V);
        ioctl(iofd, 1,IO_U1_200mV);
        ioctl(iofd, 0,IO_U1_3V);
        break;
    case U1_200mV:
        ioctl(iofd, 1,IO_U1_200V);
        ioctl(iofd, 1,IO_U1_15V);
        ioctl(iofd, 1,IO_U1_3V);
        ioctl(iofd, 0,IO_U1_200mV);
        break;
    case I1_3A:
        ioctl(iofd, 1,IO_I1_0A6);
        ioctl(iofd, 1,IO_I1_50mA);
        ioctl(iofd, 1,IO_I1_5mA);
        ioctl(iofd, 1,IO_I1_300uA);
        ioctl(iofd, 1,IO_I1_50uA);
        break;
    case I1_0A6:
        ioctl(iofd, 1,IO_I1_50mA);
        ioctl(iofd, 1,IO_I1_5mA);
        ioctl(iofd, 1,IO_I1_300uA);
        ioctl(iofd, 1,IO_I1_50uA);
        ioctl(iofd, 0,IO_I1_0A6);
        break;
    case I1_50mA:
        ioctl(iofd, 1,IO_I1_0A6);
        ioctl(iofd, 1,IO_I1_5mA);
        ioctl(iofd, 1,IO_I1_300uA);
        ioctl(iofd, 1,IO_I1_50uA);
        ioctl(iofd, 0,IO_I1_50mA);
        break;
    case I1_5mA:
        ioctl(iofd, 1,IO_I1_0A6);
        ioctl(iofd, 1,IO_I1_50mA);
        ioctl(iofd, 1,IO_I1_300uA);
        ioctl(iofd, 1,IO_I1_50uA);
        ioctl(iofd, 0,IO_I1_5mA);
        break;
    case I1_300uA:
        ioctl(iofd, 1,IO_I1_0A6);
        ioctl(iofd, 1,IO_I1_50mA);
        ioctl(iofd, 1,IO_I1_5mA);
        ioctl(iofd, 1,IO_I1_50uA);
        ioctl(iofd, 0,IO_I1_300uA);
        break;
    case I1_50uA:
        ioctl(iofd, 1,IO_I1_0A6);
        ioctl(iofd, 1,IO_I1_50mA);
        ioctl(iofd, 1,IO_I1_5mA);
        ioctl(iofd, 1,IO_I1_300uA);
        ioctl(iofd, 0,IO_I1_50uA);
        break;
    case U2_200V:
        ioctl(iofd, 1,IO_U2_15V);
        ioctl(iofd, 1,IO_U2_3V);
        ioctl(iofd, 1,IO_U2_200mV);
        ioctl(iofd, 0,IO_U2_200V);
        break;
    case U2_15V:
        ioctl(iofd, 1,IO_U2_200V);
        ioctl(iofd, 1,IO_U2_3V);
        ioctl(iofd, 1,IO_U2_200mV);
        ioctl(iofd, 0,IO_U2_15V);
        break;
    case U2_3V:
        ioctl(iofd, 1,IO_U2_200V);
        ioctl(iofd, 1,IO_U2_15V);
        ioctl(iofd, 1,IO_U2_200mV);
        ioctl(iofd, 0,IO_U2_3V);
        break;
    case U2_200mV:
        ioctl(iofd, 1,IO_U2_200V);
        ioctl(iofd, 1,IO_U2_15V);
        ioctl(iofd, 1,IO_U2_3V);
        ioctl(iofd, 0,IO_U2_200mV);
        break;
    case I2_3A:
        ioctl(iofd, 1,IO_I2_0A6);
        ioctl(iofd, 1,IO_I2_50mA);
        ioctl(iofd, 1,IO_I2_5mA);
        ioctl(iofd, 1,IO_I2_300uA);
        ioctl(iofd, 1,IO_I2_50uA);
        break;
    case I2_0A6:
        ioctl(iofd, 1,IO_I2_50mA);
        ioctl(iofd, 1,IO_I2_5mA);
        ioctl(iofd, 1,IO_I2_300uA);
        ioctl(iofd, 1,IO_I2_50uA);
        ioctl(iofd, 0,IO_I2_0A6);
        break;
    case I2_50mA:
        ioctl(iofd, 1,IO_I2_0A6);
        ioctl(iofd, 1,IO_I2_5mA);
        ioctl(iofd, 1,IO_I2_300uA);
        ioctl(iofd, 1,IO_I2_50uA);
        ioctl(iofd, 0,IO_I2_50mA);
        break;
    case I2_5mA:
        ioctl(iofd, 1,IO_I2_0A6);
        ioctl(iofd, 1,IO_I2_50mA);
        ioctl(iofd, 1,IO_I2_300uA);
        ioctl(iofd, 1,IO_I2_50uA);
        ioctl(iofd, 0,IO_I2_5mA);
        break;
    case I2_300uA:
        ioctl(iofd, 1,IO_I2_0A6);
        ioctl(iofd, 1,IO_I2_50mA);
        ioctl(iofd, 1,IO_I2_5mA);
        ioctl(iofd, 1,IO_I2_50uA);
        ioctl(iofd, 0,IO_I2_300uA);
        break;
    case I2_50uA:
        ioctl(iofd, 1,IO_I2_0A6);
        ioctl(iofd, 1,IO_I2_50mA);
        ioctl(iofd, 1,IO_I2_5mA);
        ioctl(iofd, 1,IO_I2_300uA);
        ioctl(iofd, 0,IO_I2_50uA);
        break;
    }
#endif // IO_EN
    if(newType==0)
    {
    }
    else if(newType <= 4)
    {
        U1_used = true;
    }
    else if(newType <= 10)
    {
        I1_used = true;
    }
    else if(newType <= 14)
    {
        U2_used = true;
    }
    else if(newType <= 20)
    {
        I2_used = true;
    }

}

