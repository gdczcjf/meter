#include "keyboard.h"
#include "ui_keyboard.h"

Keyboard::Keyboard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Keyboard)
{
    ui->setupUi(this);
}

Keyboard::~Keyboard()
{
    delete ui;
}

void Keyboard::showEx(TableWidgetItem *item)
{
    this->setFixedSize(width(),height());
    changeItem(item);
    this->setWindowTitle("数字键盘");
    this->setModal(true);
    exec();
}

void Keyboard::changeItem(TableWidgetItem *item)
{
    bool isNum;
    this->item=item;

    (void)(item->text().toDouble(&isNum));
    if(isNum)
    {
        text=item->text();
    }
    else
    {
        text=QString::number(item->getValue());
    }
}

void Keyboard::on_pushButton_0_clicked()
{
    if(text != "0")
        text += "0";
    item->setValueAndText(text);
}

void Keyboard::on_pushButton_1_clicked()
{

    if(text != "0")
        text += "1";
    else
        text = "1";
    item->setValueAndText(text);
}

void Keyboard::on_pushButton_2_clicked()
{
    if(text != "0")
        text += "2";
    else
        text = "2";

    item->setValueAndText(text);
}

void Keyboard::on_pushButton_3_clicked()
{
    if(text != "0")
        text += "3";
    else
        text = "3";

    item->setValueAndText(text);
}

void Keyboard::on_pushButton_4_clicked()
{
    if(text != "0")
        text += "4";
    else
        text = "4";

    item->setValueAndText(text);
}

void Keyboard::on_pushButton_5_clicked()
{
    if(text != "0")
        text += "5";
    else
        text = "5";

    item->setValueAndText(text);
}

void Keyboard::on_pushButton_6_clicked()
{
    if(text != "0")
        text += "6";
    else
        text = "6";
    item->setValueAndText(text);
}

void Keyboard::on_pushButton_7_clicked()
{
    if(text != "0")
        text += "7";
    else
        text = "7";

    item->setValueAndText(text);
}

void Keyboard::on_pushButton_8_clicked()
{

    if(text != "0")
        text += "8";
    else
        text = "8";

    item->setValueAndText(text);
}

void Keyboard::on_pushButton_9_clicked()
{
    if(text != "0")
        text += "9";
    else
        text = "9";

    item->setValueAndText(text);
}

void Keyboard::on_pushButton_dot_clicked()
{
    if(text == "")
        text = "0.";
    else if (!text.contains("."))
        text += ".";

    item->setValueAndText(text);
}

void Keyboard::on_pushButton_del_clicked()
{
    text.chop(1);
    item->setValueAndText(text);
}

void Keyboard::on_pushButton_sign_clicked()
{
    double value = text.toDouble();
    if (value > 0.0) {
        text.prepend("-");
    } else if (value < 0.0) {
        text.remove(0, 1);
    }
    item->setValueAndText(text);
}

void Keyboard::closeEvent(QCloseEvent *)
{
    emit editFinish();
}

void Keyboard::on_pushButton_Enter_clicked()
{
    emit enter(this);
}
