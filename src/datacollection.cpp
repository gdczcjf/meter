#include "datacollection.h"
#include "ui_datacollection.h"
#include "meter.h"
DataCollection::DataCollection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataCollection)
{
    ui->setupUi(this);
}

DataCollection::~DataCollection()
{
    delete ui;
}

int DataCollection::showEx(int *s,int *n)
{
    this->setWindowTitle("数据采集");
    this->s=s;
    this->n=n;
    *s=0;
    *n=0;
    exec();
    return 0;
}

void DataCollection::on_buttonBox_accepted()
{
    switch(ui->comboBox->currentIndex())
    {
    case 0:
        *n=5;
    break;
    case 1:
        *n=10;
    break;
    case 2:
        *n=15;
    break;
    case 3:
        *n=20;
    break;
    case 4:
        *n=25;
    break;
    case 5:
        *n=30;
    break;
    case 6:
        *n=50;
    break;
    }

    switch(ui->comboBox_3->currentIndex())
    {
    case 0:
        *s=2;
    break;
    case 1:
        *s=3;
    break;
    case 2:
        *s=4;
    break;
    case 3:
        *s=5;
    break;
    }
    hide();
}

void DataCollection::on_buttonBox_rejected()
{
    hide();
}
