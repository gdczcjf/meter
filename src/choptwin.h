#ifndef CHOPTWIN_H
#define CHOPTWIN_H

#include <QDialog>
#include "metertype.h"



namespace Ui {
class ChOptWin;
}



class ChOptWin : public QDialog
{
    Q_OBJECT
    
public:

    explicit ChOptWin(QWidget *parent = 0);
    ~ChOptWin();

    MeterType showEx(bool U1_used,bool U2_used,bool I1_used,bool I2_used);
    
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::ChOptWin *ui;

    int meterType;

};

#endif // CHOPTWIN_H
