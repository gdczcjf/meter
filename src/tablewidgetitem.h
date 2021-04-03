#ifndef TABLEWIDGETITEM_H
#define TABLEWIDGETITEM_H

#include <QTableWidgetItem>

class TableWidgetItem : public QTableWidgetItem
{
public:
    TableWidgetItem();
    double getValue();
    //bool isReadOnly();
    void setValueAndText(QString text,double value);
    void setValueAndText(QString text);
    void reset();

private:
    double value;
    //bool readOnly;
};

#endif // TABLEWIDGETITEM_H
