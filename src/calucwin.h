#ifndef CALUCWIN_H
#define CALUCWIN_H

#include <QDialog>

namespace Ui {
class CalucWin;
}

class CalucWin : public QDialog
{
    Q_OBJECT
signals:
    void dataCalcu(int a,int oper,int b,int c);
public:
    explicit CalucWin(QWidget *parent = 0);
    ~CalucWin();

    void showEx(int column);
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::CalucWin *ui;
};

#endif // CALUCWIN_H
