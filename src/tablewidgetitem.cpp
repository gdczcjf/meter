#include "tablewidgetitem.h"

TableWidgetItem::TableWidgetItem()
{
    //readOnly = false;
    value=0;
}

double TableWidgetItem::getValue()
{
 return value;
}
/*
bool TableWidgetItem::isReadOnly()
{
    return readOnly;
}
*/
 void TableWidgetItem::setValueAndText(QString text,double value)
 {
     setText(text);
     this->value = value;
     //readOnly = true;
 }

 void TableWidgetItem::setValueAndText(QString text)
 {
     setText(text);
     value =text.toDouble();
 }
void TableWidgetItem::reset()
{
    setText("");
    value=0;
    //readOnly = false;


}
