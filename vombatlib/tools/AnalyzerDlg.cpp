#include "AnalyzerDlg.h"
#include "ui_AnalyzerDlg.h"

#include <ccDBRoot.h>

#include <vombat.h>

AnalyzerDlg::AnalyzerDlg(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);

    this->comboRegions->addShownType(CC_TYPES::HIERARCHY_OBJECT);
    this->comboTraces->addShownType(CC_TYPES::HIERARCHY_OBJECT);
    this->comboLinks->addShownType(CC_TYPES::HIERARCHY_OBJECT);

}

AnalyzerDlg::~AnalyzerDlg()
{
}

//void AnalyzerDlg::populateCombos()
//{
//    ccHObject::Container objs = vombat::theInstance()->getAllObjectsInTreeThatAre(CC_TYPES::HIERARCHY_OBJECT);

//    LOG(INFO) << "found " << objs.size();

//    for (ccHObject * obj: objs)
//    {
//        if (obj->getName() == "DB Tree")
//            continue;

//        LOG(INFO) << "updating with id: " << obj->getUniqueID();
//        comboRegions->addItem(obj->getName(), QVariant(obj->getUniqueID()));
//        comboTraces->addItem(obj->getName(), QVariant(obj->getUniqueID()));
////        comboBox->addItem(obj->getName(), QVariant(obj->getUniqueID()));
//    }
//}

//void AnalyzerDlg::clearCombos()
//{
////    comboBox->clear();
//    comboRegions->clear();
//    comboTraces->clear();
//}

//ccHObject::Container AnalyzerDlg::getRegions()
//{
//    ccHObject * selected  = comboToObject(this->comboRegions);
//    ccHObject::Container out;
//    selected->filterChildren(out,false, CC_TYPES::POLY_LINE,true);
//    return out;
//}



//ccHObject::Container AnalyzerDlg::getTraces()
//{
//    ccHObject * selected  = comboToObject(this->comboTraces);
//    ccHObject::Container out;
//    selected->filterChildren(out,false, CC_TYPES::POLY_LINE,true);
//    return out;
//}

//ccHObject *AnalyzerDlg::comboToObject(const QComboBox *combo)
//{

//    int sel_id =combo->currentIndex();



//    int id = combo->itemData(sel_id).toInt();

//    LOG(INFO) << "unique id of selected:  "<<  id;

//    ccHObject * obj = vombat::theInstance()->getMainAppInterface()->db()->find(id);

//    if (obj)
//    {
//        LOG(INFO) << "obj name is " << obj->getName().toStdString();
//    }
//    return obj;
//}

//bool AnalyzerDlg::cropStrataTraces() const
//{
//    return checkBoxCropStrataTraces->checkState();
//}

//bool AnalyzerDlg::outputAttitudes() const
//{
//    return checkBoxGenerateAttitudes->checkState();
//}

//bool AnalyzerDlg::outputRulers() const
//{
//    return checkBoxGenerateRulers->checkState();
//}

//bool AnalyzerDlg::generateRegions() const
//{
//    return checkBoxGenerateRegions->checkState();
//}


