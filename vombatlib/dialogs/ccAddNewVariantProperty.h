#ifndef CCADDNEWVARIANTPROPERTY_H
#define CCADDNEWVARIANTPROPERTY_H

#include <QDialog>

namespace Ui {
class ccAddNewVariantProperty;
}

class ccAddNewVariantProperty : public QDialog
{
    Q_OBJECT

public:
    explicit ccAddNewVariantProperty(QWidget *parent = 0);
    ~ccAddNewVariantProperty();

    QString getName () const;

    int getType() const;
    QString getTypeName() const;

private:
    Ui::ccAddNewVariantProperty *ui;
};

#endif // CCADDNEWVARIANTPROPERTY_H
