#include "adjustwin.h"
#include "ui_adjustwin.h"





AdjustWin::AdjustWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdjustWin)
{
    ui->setupUi(this);
    advance=false;
}

AdjustWin::~AdjustWin()
{
    delete ui;
}

void AdjustWin::changeShowWay()
{
    if(advance)
    {
        setFixedSize(631,290);
        ui->groupBox_2->move(10,110);
        ui->pushButton_3->move(490,240);
        ui->pushButton_5->move(20,240);
        ui->pushButton_5->setText("基本<<");

    }
    else
    {
        setFixedSize(631,160);
        ui->groupBox_2->move(10,160);
        ui->pushButton_3->move(490,110);
        ui->pushButton_5->move(20,110);
        ui->pushButton_5->setText("高级>>");
    }
}

int AdjustWin::showEx()
{
    returnValue = 0;
    advance = false;
    changeShowWay();
    exec();
    return returnValue;
}

void AdjustWin::on_pushButton_5_clicked()
{
    advance = !advance;
    changeShowWay();
}

void AdjustWin::on_pushButton_clicked() //调零
{
    returnValue = 1;
    hide();
}


void AdjustWin::on_pushButton_2_clicked()//校正
{
    returnValue = 2;
    hide();
}


void AdjustWin::on_pushButton_3_clicked()//取消
{
    hide();
}

void AdjustWin::closeEvent ( QCloseEvent * )
{
    hide();
}


void AdjustWin::on_pushButton_4_clicked()
{
    returnValue = 3;
    hide();
}
