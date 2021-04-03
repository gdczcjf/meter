#include "i_optionwin.h"
#include "ui_i_optionwin.h"



I_OptionWin::I_OptionWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::I_OptionWin)
{
    ui->setupUi(this);
    this->setModal(true);

}

I_OptionWin::~I_OptionWin()
{
    delete ui;
}

void I_OptionWin::on_pushButton_clicked()//3A
{
    buttonNum = 0;
    this->hide();
}

void I_OptionWin::on_pushButton_2_clicked()//0.6A
{  
    buttonNum = 1;
    this->hide();
}

void I_OptionWin::on_pushButton_3_clicked()//50mA
{
    buttonNum = 2;
    this->hide();
}

void I_OptionWin::on_pushButton_4_clicked()//5mA
{
    buttonNum = 3;
    this->hide();
}

void I_OptionWin::on_pushButton_5_clicked()//300uA
{
    buttonNum = 4;
    this->hide();
}

void I_OptionWin::on_pushButton_6_clicked()//50uA
{
    buttonNum = 5;
    this->hide();
}

int I_OptionWin::showEx()
{
    setWindowTitle("请选择量程");
    setFixedSize(width(),height());
    buttonNum = -1;
    exec();
    return buttonNum;
}
