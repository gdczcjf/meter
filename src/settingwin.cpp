#include "settingwin.h"
#include "ui_settingwin.h"

#include <QFile>
#include <QMessageBox>

MeterSetting SettingWin::setting;


SettingWin::SettingWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingWin)
{
    ui->setupUi(this);
}

SettingWin::~SettingWin()
{
    delete ui;
}



void SettingWin::loadSetting()
{
    QFile settingFile("MeterSetting");
    if(!settingFile.open(QIODevice::ReadOnly))
    {

        QMessageBox msgBox;
        msgBox.setWindowTitle("错误");
        msgBox.setText("读取设置数据时错误，将使用默认设置。");
        msgBox.exec();

        setInertance();
        setting.randomType=0;
        setting.ValueDispWay=0;
        saveSetting();
    }
    else
    {
        QDataStream settingIn(&settingFile);
        char *data;
        unsigned int len=(unsigned int)sizeof(setting);
        settingIn.readBytes(data,len);

        memcpy(&setting,data,sizeof(setting));

        delete data;  //maybe a bug
    }
    settingFile.close();
}

void SettingWin::saveSetting()
{
    QFile file("MeterSetting");
    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("错误");
        msgBox.setText("写入设置数据时错误");
        msgBox.exec();
    }
    else
    {
        QDataStream settingOut(&file);
        char *data;
        data=(char *)(&setting);
        settingOut.writeBytes(data,(uint)sizeof(setting));
    }
    file.close();
}


void  SettingWin::setInertance(int i)
{


    switch(i)
    {
    case 0:
        setting.inertance=0;
    break;
    case 1:
        setting.inertance=0.75;
    break;
    case 2:
        setting.inertance=0.85;
    break;
    case 3:
        setting.inertance=0.95;
    break;
    }
    setting.inertanceIndex = i;
}

void SettingWin::showEx()
{
    ui->comboBox->setCurrentIndex(setting.inertanceIndex);
    ui->comboBox_2->setCurrentIndex(setting.randomType);
    ui->comboBox_3->setCurrentIndex(setting.ValueDispWay);
    exec();
}


void SettingWin::on_pushButton_clicked()//确定
{
    setInertance(ui->comboBox->currentIndex());
    setting.randomType=ui->comboBox_2->currentIndex();
    setting.ValueDispWay=ui->comboBox_3->currentIndex();
    saveSetting();
    hide();
}


void SettingWin::on_pushButton_2_clicked()//取消
{
    hide();
}
