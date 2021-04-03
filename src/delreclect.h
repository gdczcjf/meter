#ifndef DELRECLECT_H
#define DELRECLECT_H

#include <QDialog>

namespace Ui {
class DelRecLect;
}

class DelRecLect : public QDialog
{
    Q_OBJECT
    
public:
    explicit DelRecLect(QWidget *parent = 0);
    ~DelRecLect();
    int showEx();
private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::DelRecLect *ui;
    int selection;
};

#endif // DELRECLECT_H
