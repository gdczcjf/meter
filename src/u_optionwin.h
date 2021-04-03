#ifndef U_OPTIONWIN_H
#define U_OPTIONWIN_H

#include <QDialog>

class Meter;
namespace Ui {
class U_OptionWin;
}

class U_OptionWin : public QDialog
{
    Q_OBJECT
    
public:
    explicit U_OptionWin(QWidget *parent = 0);
    ~U_OptionWin();

    int showEx();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::U_OptionWin *ui;
    int buttonNum;
};

#endif // U_OPTIONWIN_H
