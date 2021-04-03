#ifndef DATACOLLECTION_H
#define DATACOLLECTION_H

#include <QDialog>

class Meter;

namespace Ui {
class DataCollection;
}

class DataCollection : public QDialog
{
    Q_OBJECT
    
public:
    explicit DataCollection(QWidget *parent = 0);
    ~DataCollection();
    int showEx(int *s,int *n);
    
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::DataCollection *ui;
    int *s,*n;
};

#endif // DATACOLLECTION_H
