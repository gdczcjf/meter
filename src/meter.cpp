#include <stdlib.h>
#include <qmath.h>
#include <math.h>
#include <QFile>
#include <unistd.h>
#include <QTime>
#include <QApplication>
#include <QThread>

#include "qmessagebox.h"

#include "meter.h"
#include "choptwin.h"
#include "i_optionwin.h"
#include "u_optionwin.h"
#include "adjustwin.h"
#include "hardware.h"
#include "datacollection.h"
#include "progress.h"
#include "delreclect.h"
#include "settingwin.h"


const MeterTypeInfo metersTypeInfo[] =
{
    //OFF
    {
        "点击新建",


        0,
        0,
        0,
        0
    },
    {
        "200V",


        1,
        30,
        0,
        200
    },
    {
        "15V",


        0.1,
        60,
        -5,
        15
    },


    {
        "3V",


        0.01,
        60,
        -1,
        3
    },
    {
        "200mV",


        0.001,
        90,
        -0.2,
        0.2
    },
    {
        "3A",


        0.01,
        60,
        -1,
        3
    },
    {
        "0.6A",


        0.002,
        60,
        -0.2,
        0.6
    },
    {
        "50mA",


        0.0001,
        30,
        0,
        0.05
    },
    {
        "5mA",

        0.00001,
        30,
        0,
        0.005
    },
    {
        "300uA",

        0.000001,
        30.0,
        0.0,
        0.0003
    },
    {
        "50uA",

        0.0000002,
        90.0,
        -0.00005,
        0.00005
    }
};

/****校准值****/
AdjustData Meter::adjustDatas[21] =
{
    {0,             0.0          },//OFF
    //U1
    {488,        200.0/434.0},//U1_200V
    {488,        15.0/434.0},//U1_15V
    {488,        3.0/434.0},//U1_3V
    {488,        0.2/434.0},//U1_200mV
    //I1
    {485,        3.0/419.0},//I1_3A
    {485,        0.6/419.0},//I1_0A6
    {485,        0.05/419.0},//I1_50mA
    {485,        0.005/419.0},//I1_5mA
    {485,        0.0003/419.0}, //I1_300uA
    {485,        0.00005/419.0}, //I1_50uA
    //U2
    {488,        200.0/434.0},  //U2_200V
    {488,        15.0/434.0}, //U2_15V
    {488,        3.0/434.0},  //U2_3V
    {488,        0.2/434.0},//U2_200mV
    //I2
    {485,        3.0/419.0},//I2_3A
    {485,        0.6/419.0},//I2_0A6
    {485,        0.05/419.0},//I2_50mA
    {485,        0.005/419.0},//I2_5mA
    {485,        0.0003/419.0},//I2_300uA
    {485,        0.00005/419.0} //I2_50uA
};



const int meterNeedleX=400;
const int meterNeedleY=420;
const int adjustButtonX=400;
const int adjustButtonY=420;

int Meter::fd = -1;
int Meter::ID_Count=0;

Meter* Meter::meters[4]={NULL,NULL,NULL,NULL};
QPixmap* Meter::pPixmapMeterFrame;
QPixmap* Meter::pPixmapAdjustButton;

Meter::Meter()
{
    if(ID_Count==0)
    {
        pPixmapMeterFrame = new QPixmap(":/pic/frame.png");
        pPixmapAdjustButton = new QPixmap(":/pic/adjustButton.png");


        readSetting();
        SettingWin::loadSetting();
        if(SettingWin::setting.randomType == 1)
        {
            setRandomZero();
        }
    }
    ID=ID_Count;
    meters[ID]=this;
    ID_Count++;
    rectF.setRect(0,0,800,480);
    type = U1_200V;
    isDisplayValue=false;
    setType(OFF);


    frame.setPic(pPixmapMeterFrame);
    adjustButton.setPic(pPixmapAdjustButton,pPixmapAdjustButton->width()/2,pPixmapAdjustButton->height()/2);
    adjustButton.setX(adjustButtonX);
    adjustButton.setY(adjustButtonY);

    scale.setX(meterNeedleX);
    scale.setY(meterNeedleY);
    needle.setX(meterNeedleX);
    needle.setY(meterNeedleY);

    menu.setWidget(&meterOption);
    menu.setY(480-120);
    menu.setX(0);
   // menu.setOpacity(1);//透明度
    menu.hide();

    QFont font;
    font.setPixelSize(30);
    channelText.setFont(font);
    channelText.setX(20);
    channelText.setY(20);
    rangeText.setFont(font);
    rangeText.setX(20);
    rangeText.setY(50);
    font.setPixelSize(40);
    valueText.setFont(font);
    valueText.setX(20);
    valueText.setY(80);
    valueText.setDefaultTextColor(Qt::green);

    scale.setParentItem(this);

    needle.setParentItem(this);
    channelText.setParentItem(this);
    rangeText.setParentItem(this);
    valueText.setParentItem(this);
    frame.setParentItem(this);
    adjustButton.setParentItem(this);
    menu.setParentItem(this);


    QObject::connect(&frame,SIGNAL(mousePress()),this,SLOT(showAndHideMenu()));
    QObject::connect(&meterOption,SIGNAL(changeRange()),this,SLOT(choiceRange()));
    QObject::connect(&meterOption,SIGNAL(dispValue(bool)),this,SLOT(dispValue(bool)));
    QObject::connect(&meterOption,SIGNAL(close()),this,SLOT(turnOff()));
    QObject::connect(&meterOption,SIGNAL(dispWay(bool)),this,SLOT(setShowWay(bool)));
    QObject::connect(&meterOption,SIGNAL(record()),this,SLOT(sample()));
    QObject::connect(&meterOption,SIGNAL(saveValue()),this,SLOT(recordAllMetersValue()));
    QObject::connect(&meterOption,SIGNAL(deleteRecord()),this,SLOT(deleteRecord()));
    QObject::connect(&scale,SIGNAL(mousePress()),this,SLOT(choiceCh()));
    QObject::connect(&adjustButton,SIGNAL(mousePress()),this,SLOT(showAdjustWin()));



    setShowWay(false);

}



QRectF Meter::boundingRect() const
{
    return rectF;
}

void Meter::paint(QPainter *, const QStyleOptionGraphicsItem *,QWidget *)
{
}

void Meter::setType(MeterType type)
{
    if(this->type==type)
        return;
    int typeInt;
    HardWare::connectChannel(this->type,type);
    this->type = type;
    typeInt=(int)type;




    if(typeInt==0)
    {
        channelName = "未打开通道";
        pADValue=0;
        frame.hide();
        adjustButton.hide();
        needle.hide();
        menu.hide();
        valueText.hide();
        sampleCycle=0;
        ValueSamples.clear();
    }
    else
    {
        if(typeInt <= 4)
        {
            channelName = "电压通道一";
            pADValue=&HardWare::AD[3];//AD3 pin-22 U1
            ADIndex=3;
        }
        else if(typeInt <= 10)
        {
            channelName = "电流通道一";
            pADValue = &HardWare::AD[1];//AD pin-10 I1
            ADIndex=1;
        }
        else if(typeInt <= 14)
        {
            channelName = "电压通道二";
            pADValue=&HardWare::AD[2];//AD2 pin-21 U2
            ADIndex=2;
        }
        else if(typeInt <= 20)
        {
            channelName = "电流通道二";
            pADValue = &HardWare::AD[0];//AD pin-9 I2
            ADIndex=0;
        }
        frame.show();
        adjustButton.show();
        needle.show();
        dispValue(isDisplayValue);
    }

    pADzero = &(adjustDatas[typeInt].ADzero);
    pADFactor = &(adjustDatas[typeInt].ADFactor);


    int temp;
    if(typeInt <= 10)
    {
        temp = typeInt;
    }
    else if(typeInt <= 20)
    {
        temp = typeInt -10;
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("typeInt 值异常");
        msgBox.exec();
        return;
    }

    meterName = metersTypeInfo[temp].name;
    valueFactor = metersTypeInfo[temp].valuefactor;
    valueMin = metersTypeInfo[temp].valueMin;
    valueMax = metersTypeInfo[temp].valueMax;
    valueMax2Min = valueMax - valueMin;
    angleTrue = metersTypeInfo[temp].zeroAngle;
    scale.setScaleInfo(type);



    channelText.setPlainText(channelName);
    rangeText.setPlainText("量程:"+meterName);


    angle=angleTrue;
    needle.setRotation(angleTrue);
}

void Meter::advance(int step)
{
    static qreal angleTrueOld;
    if (!step || type ==OFF)
        return;

    value=getValue();
    getAngle();




    angleTrueOld=angleTrue;
    angleTrue=angleTrue*(SettingWin::setting.inertance)+(1-SettingWin::setting.inertance)*angle;
    //angleTrue=angleTrue*0.85+0.15*angle;



    if(angleTrue < 25 )
    {
        angleTrue = 25;
    }
    else if(angleTrue > 155)
    {
        angleTrue = 155;

    }

    if(value<valueMin || value>valueMin+valueMax2Min)
    {
         needle.glitter();
         valueText.setPlainText("超量程");
    }
    else
    {
        needle.setOpacity(1.0);
        if(qAbs(angle-angleTrue)>0.8 && SettingWin::setting.ValueDispWay == 0)
        {
           valueText.setPlainText("........");
        }
        else
        {
            valueText.setPlainText(getValueText());
        }
    }

    if(qAbs(angleTrueOld-angleTrue)>0.01)
    {
       needle.setRotation(angleTrue);

    }


}

void Meter::showAndHideMenu()
{
    if(menu.isVisible())
        menu.hide();
    else
        menu.show();
}

void Meter::choiceCh()
{
    MeterType t;
    ChOptWin chWin;
    t = chWin.showEx(HardWare::U1_used,HardWare::U2_used,HardWare::I1_used,HardWare::I2_used);
    setType(t);
}
void Meter::choiceRange()
{

    int typeInt;


    if(type >= I2_3A)
    {
        I_OptionWin iWin;
        typeInt = iWin.showEx();
        if(typeInt != -1)
        {
            setType( (MeterType)(typeInt + I2_3A) );
        }
        else
            return;
    }
    else if(type >= U2_200V)
    {
        U_OptionWin uWin;
        typeInt = uWin.showEx();
        if(typeInt != -1)
        {
            setType((MeterType)( typeInt + U2_200V));
        }
        else
            return;
    }
    else if(type >= I1_3A)
    {
        I_OptionWin iWin;
        typeInt = iWin.showEx();
        if(typeInt != -1)
        {
            setType((MeterType) (typeInt + I1_3A) );
        }
        else
            return;
    }
    else if(type >= U1_200V)
    {
        U_OptionWin uWin;
        typeInt = uWin.showEx();
        if(typeInt != -1)
        {
            setType((MeterType)( typeInt + U1_200V));
        }
        else
            return;
    }

}
void Meter::turnOff()
{
    meterOption.setFullscreen(false);
    setType(OFF);
}

void Meter::setShowWay(bool fullScreen)
{
    if(fullScreen)
    {
        int i;
        for (i=0;i<4;i++)
        {
            if(meters[i]!=NULL)
            {
                if(i!=ID)
                {

                    meters[i]->hide();
                }
                else
                {
                    this->setScale(1.0);
                    this->setX(0);
                    this->setY(0);
                }
            }
        }
    }
    else
    {
        int i;
        for (i=0;i<4;i++)
        {
            if(meters[i]!=NULL)
            {
                meters[i]->setScale(0.5);
                switch(i)
                {
                case 0:
                    meters[i]->setX(0);
                    meters[i]->setY(0);
                    break;
                case 1:
                    meters[i]->setX(400);
                    meters[i]->setY(0);
                    break;
                case 2:
                    meters[i]->setX(0);
                    meters[i]->setY(240);
                    break;
                case 3:
                    meters[i]->setX(400);
                    meters[i]->setY(240);
                    break;
                }
                meters[i]->show();
            }
        }

    }
}

void Meter::mousePressEvent ( QGraphicsSceneMouseEvent *)
{
}

double Meter::getValue(int adValue)
{
    if(type==OFF)
    {
        return 10000;
    }
    else
    {
        return round((double)((adValue) - (*pADzero)) * (*pADFactor)/(valueFactor))*valueFactor;//估读
    }
}

double Meter::getValue()
{
    if(type==OFF)
    {
        return 10000;
    }
    else
    {
        return round(    (double)((*pADValue)-(*pADzero))   *    (*pADFactor)   /   valueFactor    ) * valueFactor;//估读
        //return (double)(*pADValue)/1024.0*valueMax2Min+valueMin;
    }
}

void Meter::getAngle()
{

    const float angleMin=30;
    const float angleMax2Min=120;


    if(type==OFF)
    {
        angle = 0;
    }
    else
    {
       angle = (value-valueMin)/valueMax2Min*angleMax2Min+angleMin;
    }
}

bool Meter::isOutOfRange()
{
    if(value<valueMin || value>valueMin+valueMax2Min)
        return true;
    else
        return false;
}

MeterType Meter::getType()
{
    return type;
}
void Meter::saveSetting()
{

    QFile settingFile("MeterData");
    if(!settingFile.open(QIODevice::WriteOnly))
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("错误");
        msgBox.setText("写入校正数据时错误");
        msgBox.exec();
    }
    else
    {
        QDataStream settingOut(&settingFile);
        char *data;
        data=(char *)(&adjustDatas);
        settingOut.writeBytes(data,(uint)sizeof(adjustDatas));

    }
    settingFile.close();
}
void Meter::readSetting()
{
    QFile settingFile("MeterData");
    if(!settingFile.open(QIODevice::ReadOnly))
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("错误");
        msgBox.setText("读取校正数据时错误");
        msgBox.exec();
    }
    else
    {
        QDataStream settingIn(&settingFile);
        char *data;
        unsigned int len=(unsigned int)sizeof(adjustDatas);
        settingIn.readBytes(data,len);

        memcpy(&adjustDatas[0],data,sizeof(adjustDatas));

        delete data;  //maybe a bug
    }
    settingFile.close();
}
void Meter::recoverSetting()
{
    int error;
    error = ::system("cp MeterData.bak MeterData");
    if(error)
    {
        QString str=QString::number(error);
        QMessageBox msgBox;
        msgBox.setWindowTitle("错误");
        msgBox.setText("恢复出厂校正数据时错误:"+str);
        msgBox.exec();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("提示");
        msgBox.setText("恢复出厂校正数据成功！");
        msgBox.exec();
    }
    readSetting();
}

void Meter::setADzero()
{
    (*pADzero)=(*pADValue);
    if(SettingWin::setting.randomType==0)
        saveSetting();
}

void Meter::setADfactor()
{
    if(qAbs((*pADValue)-(*pADzero))<1024/4)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("错误");
        msgBox.setText("输入电压异常，请确保操作正确！");
        msgBox.exec();
    }
    else
    {
        (*pADFactor)= (valueMin+valueMax2Min)/(float)(*pADValue - (*pADzero));
    }
    saveSetting();
}

void Meter::showAdjustWin()
{
    AdjustWin adjustWin;
    switch(adjustWin.showEx())
    {
    case 1:
        setADzero();
        break;
    case 2:
        setADfactor();
        break;
    case 3:
        recoverSetting();
        break;
    default:
        return;
        break;
    }
    saveSetting();
}
void Meter::dispValue(bool disp)
{
    isDisplayValue = disp;
    if(disp)
    {
    valueText.show();
    }
    else
        valueText.hide();
}

void Meter::sample()
{
    int n,s;
    QVector<int> adVales[4];
    DataCollection dataCollectWin;
    dataCollectWin.showEx(&s,&n);
    if(n!=0 && s!=0)
    {
        QMessageBox msgBox;
        sampleCycle=s;
        msgBox.setWindowTitle("重要提示");
        msgBox.setText("为了确保数据采集的实时性，\n在数据采集的过程中请不要触摸屏幕！\n请耐心等侍采集结束！");
        msgBox.exec();
        Progress progress;
        progress.showEx();
        QObject::connect(this,SIGNAL(sampleProgress(int)),&progress,SLOT(setProgress(int)));

        //HardWare::setADCycle(0);
        for(int i=0;i<n;i++)
        {
            //HardWare::getADValueOnce();
            adVales[0].append(HardWare::AD[0]);
            adVales[1].append(HardWare::AD[1]);
            adVales[2].append(HardWare::AD[2]);
            adVales[3].append(HardWare::AD[3]);
            emit(sampleProgress((i+1)*100/n));
            QApplication::processEvents();
            QThread::sleep(s);
        }
        //HardWare::setADCycle(1000);
        /**/
        for(int i=0;i<4;i++)
        {
            if(meters[i]->type!=OFF)
            {
                meters[i]->ValueSamples.resize(0);
                for(int j=0;j<n;j++)
                {   
                    meters[i]->ValueSamples.append( meters[i]->getValue( adVales[meters[i]->ADIndex][j]) );
                }

            }
        }
        msgBox.setWindowTitle("提示");
        msgBox.setText("数据采集结束");
        msgBox.exec();
    }
}
void Meter::recordValue()
{
    sampleCycle=0;
    if(this->type == OFF)
        return;
    else if(isOutOfRange()==true)
    {
        QMessageBox msgbox;
        msgbox.setWindowTitle("手动记录数据");
        QString str;
        str = channelName + "超过量程，无法读数。";
        msgbox.setText(str);
        msgbox.exec();
    }
    else
        ValueSamples.append(value);

}

void Meter::recordAllMetersValue()
{
    bool flag=false;
    for(int i=0; i < 4 && !flag; i++)
    {
        if(Meter::meters[i]->getType() != OFF)
            flag=Meter::meters[i]->isOutOfRange();
    }
    if(flag)
    {
        QMessageBox msgbox;
        QString str;
        msgbox.setWindowTitle("手动记录数据");
        str = "有电表超量程。";
        msgbox.setText(str);
        msgbox.exec();
        return;
    }
    for(int i= 0; i < 4; i++)
    {
            Meter::meters[i]->recordValue();
    }
    QMessageBox msgbox;
    QString str;
    msgbox.setWindowTitle("手动记录数据");
    str = "完成记录。";
    msgbox.setText(str);
    msgbox.exec();
}

void Meter::deleteRecord()
{
    int select;
    DelRecLect delWin;
    QMessageBox msgbox;
    QString str;

    select=delWin.showEx();
    msgbox.setWindowTitle("删除数据");

    switch(select)
    {
    case 1:
        ValueSamples.clear();
        sampleCycle=0;
        str = getChannelName()+":数据已清空。";
        msgbox.setText(str);
        msgbox.exec();
        break;
    case 2:
        if(!ValueSamples.isEmpty())
        {
            (void)ValueSamples.pop_back();
            str = "剩下"+QString::number(ValueSamples.count()) +"个数据。";
        }
        else
        {
            str = "没有数据";
        }
        msgbox.setText(str);
        msgbox.exec();
        break;
    case 3:
        meters[0]->ValueSamples.clear();
        meters[1]->ValueSamples.clear();
        meters[2]->ValueSamples.clear();
        meters[3]->ValueSamples.clear();

        meters[0]->sampleCycle=0;
        meters[1]->sampleCycle=0;
        meters[2]->sampleCycle=0;
        meters[3]->sampleCycle=0;
        str = "所有数据已清空";
        msgbox.setText(str);
        msgbox.exec();
        break;
    }   
}

QString Meter::getChannelName()
{
    return channelName;
}

QString Meter::getValueText(double value)
{
    QString string;
    switch(type)
    {
    case OFF:
        string = "";
        break;

    case U1_200V:
    case U2_200V:
            string = QString::number(value)+"V";
        break;
    case U1_15V:
    case U2_15V:
        string = QString::number(value,'f',1)+"V";
        break;
    case U1_3V:
        case U2_3V:
        string = QString::number(value,'f',2)+"V";
        break;
    case U1_200mV:
    case U2_200mV:
        string = QString::number(value*1000)+"mV";
        break;

    case I1_3A:
    case I2_3A:
        string = QString::number(value,'f',2)+"A";
        break;
    case I1_0A6:
    case I2_0A6:
        string = QString::number(value,'f',3)+"A";
        break;
    case I1_50mA:
    case I2_50mA:
        string = QString::number(value*1000,'f',1)+"mA";
        break;
    case I1_5mA:
    case I2_5mA:
        string = QString::number(value*1000,'f',2)+"mA";
        break;

    case I1_300uA:
    case I2_300uA:
        string = QString::number(value*1000000)+"uA";
        break;
    case I1_50uA:
    case I2_50uA:
        string = QString::number(value*1000000,'f',1)+"uA";
        break;
    }
    return string;
}

QString Meter::getValueText()
{
   return getValueText(value);
}


void Meter::setRandomZero()
{
    QTime time;
    time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    for(int i=0;i<21;i++)
    {
        adjustDatas[i].ADzero += qrand()%120 - 60;
    }
}
