#include "calucwin.h"
#include "ui_calucwin.h"

CalucWin::CalucWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalucWin)
{
    ui->setupUi(this);
}

CalucWin::~CalucWin()
{
    delete ui;
}

void CalucWin::showEx(int columnCount)
{
    setFixedSize(width(),height());
    setWindowTitle("请选择");
    for(int i=1; i<=columnCount; i++)
    {
        QString str = "列"+ QString::number(i);
        ui->comboBox_2->addItem(str);
        ui->comboBox_3->addItem(str);
        ui->comboBox_4->addItem(str);
    }
    exec();
}

void CalucWin::on_pushButton_clicked()//确定
{
    emit dataCalcu(ui->comboBox_2->currentIndex(),ui->comboBox->currentIndex(),ui->comboBox_3->currentIndex(),ui->comboBox_4->currentIndex());
    hide();
}

void CalucWin::on_pushButton_2_clicked()//取消
{
    hide();
}

void CalucWin::on_comboBox_currentIndexChanged(int index)
{
    if(index >= 6)
    {
        ui->comboBox_3->setDisabled(true);
    }
    else
    {
        ui->comboBox_3->setDisabled(false);
    }
}
