#ifndef I_OPTIONWIN_H
#define I_OPTIONWIN_H

#include <QDialog>

class Meter;

namespace Ui {
class I_OptionWin;
}

class I_OptionWin : public QDialog
{
    Q_OBJECT
    
public:
    explicit I_OptionWin(QWidget *parent = 0);
    ~I_OptionWin();

    int showEx();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::I_OptionWin *ui;
    int buttonNum;
};

#endif // I_OPTIONWIN_H
