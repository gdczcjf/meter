#include "meteroption.h"
#include "ui_meteroption.h"


MeterOption::MeterOption(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MeterOption)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground, true);//窗口背景透明
    //setStyleSheet("background-color:transparent");


}

MeterOption::~MeterOption()
{
    delete ui;
}



void MeterOption::on_pushButton_7_clicked()
{
    emit close();
}

void MeterOption::on_pushButton_3_clicked()
{
    if(ui->pushButton_3->isChecked())
    {
        //ui->pushButton_3->setText("关闭\n数显");
        emit dispValue(true);
    }
    else
    {
        //ui->pushButton_3->setText("打开\n数显");
        emit dispValue(false);
    }
}

void MeterOption::on_pushButton_clicked()
{
    emit changeRange();
}
void MeterOption::setFullscreen(bool fullscreen)
{
    ui->pushButton_4->setChecked(fullscreen);
    on_pushButton_4_clicked();
}
void MeterOption::on_pushButton_4_clicked()
{
    if(ui->pushButton_4->isChecked())
    {
        //ui->pushButton_4->setText("退出\n全屏");
        emit dispWay(true);
    }
    else
    {
        //ui->pushButton_4->setText("全屏");
        emit dispWay(false);
    }

}

void MeterOption::on_pushButton_5_clicked()
{
    emit record();
}

void MeterOption::on_pushButton_2_clicked()
{
    emit saveValue();
}

void MeterOption::on_pushButton_6_clicked()
{
    emit deleteRecord();
}
