#include "u_optionwin.h"
#include "ui_u_optionwin.h"



U_OptionWin::U_OptionWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::U_OptionWin)
{
    ui->setupUi(this);
    setModal(true);

}

U_OptionWin::~U_OptionWin()
{
    delete ui;
}

void U_OptionWin::on_pushButton_clicked()//200V
{
    buttonNum = 0;
    this->hide();
}

void U_OptionWin::on_pushButton_2_clicked()//15V
{
    buttonNum = 1;
    this->hide();
}

void U_OptionWin::on_pushButton_3_clicked()//3V
{
     buttonNum = 2;
    this->hide();
}

void U_OptionWin::on_pushButton_4_clicked()//200mV
{
    buttonNum = 3;
    this->hide();
}

int U_OptionWin::showEx()
{
    setWindowTitle("请选择量程");
    setFixedSize(width(),height());
    buttonNum = -1;
    exec();
    return buttonNum;
}

