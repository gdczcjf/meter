#ifndef KEYBOARD_H
#define KEYBOARD_H


#include <QDialog>
#include "tablewidgetitem.h"

namespace Ui {
class Keyboard;
}

class Keyboard : public QDialog
{
    Q_OBJECT
signals:
    void editFinish();
    void enter(Keyboard *keyboard);

public:
    explicit Keyboard(QWidget *parent = 0);
    ~Keyboard();

    void showEx(TableWidgetItem *item);
    void changeItem(TableWidgetItem *item);

protected:
    void closeEvent(QCloseEvent *);
    
private slots:
    void on_pushButton_0_clicked();

    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_dot_clicked();

    void on_pushButton_del_clicked();

    void on_pushButton_sign_clicked();

    void on_pushButton_Enter_clicked();

private:
    Ui::Keyboard *ui;
    TableWidgetItem *item;
    QString text;
};

#endif // KEYBOARD_H
