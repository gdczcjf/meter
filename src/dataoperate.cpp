#include "dataoperate.h"
#include "ui_dataoperate.h"

DataOperate::DataOperate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataOperate)
{
    ui->setupUi(this);
}

DataOperate::~DataOperate()
{
    delete ui;
}

int DataOperate::showEx(/*bool readOnly*/)
{
    returnValue=0;
    setFixedSize(width(),height());
    setWindowTitle("请选择");
    /*
    if(readOnly)
    {
        ui->pushButton->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_7->setEnabled(false);
        ui->pushButton_9->setEnabled(false);
    }*/
    exec();
    return returnValue;
}
void DataOperate::on_pushButton_3_clicked()
{
    returnValue = 1;
    hide();
}

void DataOperate::on_pushButton_4_clicked()
{
    returnValue = 2;
    hide();
}

void DataOperate::on_pushButton_5_clicked()
{
    returnValue = 3;
    hide();
}

void DataOperate::on_pushButton_6_clicked()
{
    returnValue = 4;
    hide();
}

void DataOperate::on_pushButton_clicked()
{
    returnValue = 5;
    hide();
}

void DataOperate::on_pushButton_2_clicked()
{
    returnValue = 6;
    hide();
}

void DataOperate::on_pushButton_9_clicked()
{
    returnValue = 7;
    hide();
}

void DataOperate::on_pushButton_10_clicked()
{
    returnValue = 8;
    hide();
}

void DataOperate::on_pushButton_7_clicked()
{
    returnValue = 9;
    hide();
}

void DataOperate::on_pushButton_8_clicked()
{
    returnValue = 10;
    hide();
}
