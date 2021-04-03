#include "delreclect.h"
#include "ui_delreclect.h"

DelRecLect::DelRecLect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DelRecLect)
{
    ui->setupUi(this);
}

DelRecLect::~DelRecLect()
{
    delete ui;
}


int DelRecLect::showEx()
{
    selection=0;
    setWindowTitle("清除数据");
    setFixedSize(this->width(),this->height());
    this->exec();
    return selection;
}
void DelRecLect::on_pushButton_3_clicked()
{
    hide();
}

void DelRecLect::on_pushButton_clicked()
{
    selection=1;
    hide();
}

void DelRecLect::on_pushButton_2_clicked()
{
    selection=2;
    hide();
}

void DelRecLect::on_pushButton_4_clicked()
{
    selection=3;
    hide();
}
