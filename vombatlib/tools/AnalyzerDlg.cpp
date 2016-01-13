#include "AnalyzerDlg.h"
#include "ui_AnalyzerDlg.h"

#include <ccDBRoot.h>

#include <vombat.h>

AnalyzerDlg::AnalyzerDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnalyzerDlg)
{
    ui->setupUi(this);


//    connect (ui->comboRegions, SIGNAL(currentIndexChanged(int)), this, SLOT(itemChanged(int)));
}

AnalyzerDlg::~AnalyzerDlg()
{
    delete ui;
}

void AnalyzerDlg::populateCombos()
{
    ccHObject::Container objs = vombat::theInstance()->getAllObjectsInTreeThatAre(CC_TYPES::HIERARCHY_OBJECT);

    LOG(INFO) << "found " << objs.size();

    for (ccHObject * obj: objs)
    {
        if (obj->getName() == "DB Tree")
            continue;

        LOG(INFO) << "updating with id: " << obj->getUniqueID();
        ui->comboRegions->addItem(obj->getName(), QVariant(obj->getUniqueID()));
        ui->comboTraces->addItem(obj->getName(), QVariant(obj->getUniqueID()));
//        ui->comboBox->addItem(obj->getName(), QVariant(obj->getUniqueID()));
    }
}

void AnalyzerDlg::clearCombos()
{
//    ui->comboBox->clear();
    ui->comboRegions->clear();
    ui->comboTraces->clear();
}

ccHObject::Container AnalyzerDlg::getRegions()
{
    ccHObject * selected  = comboToObject(this->ui->comboRegions);
    ccHObject::Container out;
    selected->filterChildren(out,false, CC_TYPES::POLY_LINE,true);
    return out;
}



ccHObject::Container AnalyzerDlg::getTraces()
{
    ccHObject * selected  = comboToObject(this->ui->comboTraces);
    ccHObject::Container out;
    selected->filterChildren(out,false, CC_TYPES::POLY_LINE,true);
    return out;
}

ccHObject *AnalyzerDlg::comboToObject(const QComboBox *combo)
{

    int sel_id =combo->currentIndex();



    int id = combo->itemData(sel_id).toInt();

    LOG(INFO) << "unique id of selected:  "<<  id;

    ccHObject * obj = vombat::theInstance()->getMainAppInterface()->db()->find(id);

    if (obj)
    {
        LOG(INFO) << "obj name is " << obj->getName().toStdString();
    }
    return obj;
}

bool AnalyzerDlg::cropStrataTraces() const
{
    return ui->checkBoxCropStrataTraces->checkState();
}

bool AnalyzerDlg::outputAttitudes() const
{
    return ui->checkBoxGenerateAttitudes->checkState();
}

bool AnalyzerDlg::outputRulers() const
{
    return ui->checkBoxGenerateRulers->checkState();
}

//bool AnalyzerDlg::generateRegions() const
//{
//    return ui->checkBoxGenerateRegions->checkState();
//}


