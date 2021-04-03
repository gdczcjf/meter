#include "choptwin.h"
#include "ui_choptwin.h"

#include "i_optionwin.h"
#include "u_optionwin.h"








ChOptWin::ChOptWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChOptWin)
{
    ui->setupUi(this);
}

ChOptWin::~ChOptWin()
{
    delete ui;
}

void ChOptWin::on_pushButton_2_clicked()//U1
{
    int offSet;
    U_OptionWin win;
    offSet = win.showEx();
    if(offSet != -1)
    {
        meterType = U1_200V + offSet;
        hide();
    }
}

void ChOptWin::on_pushButton_4_clicked()//U2
{
    int offSet;
    U_OptionWin win;
    offSet = win.showEx();
    if(offSet != -1)
    {
        meterType = U2_200V + offSet;
        hide();
    }
}

void ChOptWin::on_pushButton_clicked()//I1
{
    int offSet;
    I_OptionWin win;
    offSet = win.showEx();
    if(offSet != -1)
    {
        meterType =  I1_3A + offSet;
        hide();
    }
}


void ChOptWin::on_pushButton_3_clicked()//I2
{
    int offSet;
    I_OptionWin win;
    offSet = win.showEx();
    if(offSet != -1)
    {
        meterType =  I2_3A + offSet;
        hide();
    }
}

MeterType ChOptWin::showEx(bool U1_used,bool U2_used,bool I1_used,bool I2_used)
{

    setFixedSize(width(),height());
    setWindowTitle("请选择通道");

    ui->pushButton_2->setEnabled(!U1_used);
    ui->pushButton_4->setEnabled(!U2_used);
    ui->pushButton->setEnabled(!I1_used);
    ui->pushButton_3->setEnabled(!I2_used);

    meterType = OFF;
    exec();
    return (MeterType)meterType;

}


