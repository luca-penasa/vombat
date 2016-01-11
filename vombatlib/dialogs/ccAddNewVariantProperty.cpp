#include "ccAddNewVariantProperty.h"
#include "ui_ccAddNewVariantProperty.h"




ccAddNewVariantProperty::ccAddNewVariantProperty(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ccAddNewVariantProperty)
{
    ui->setupUi(this);
}

ccAddNewVariantProperty::~ccAddNewVariantProperty()
{
    delete ui;
}

QString ccAddNewVariantProperty::getName() const
{
    QString name = ui->lneName->text();
    if (name.isEmpty())
    { // put a defualt name
        name = this->getTypeName();
    }
    return name;
}

int ccAddNewVariantProperty::getType() const
{
    return ui->cmbType->currentIndex();
}

QString ccAddNewVariantProperty::getTypeName() const
{
    return ui->cmbType->currentText();
}
