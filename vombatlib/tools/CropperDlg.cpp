#include "CropperDlg.h"
#include "ui_CropperDlg.h"

#include <ccDBRoot.h>

#include <vombat.h>

#include <ccSPCElementShell.h>
#include <spc/elements/SelectionRubberband.h>

CropperDlg::CropperDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CropperDlg)
{
    ui->setupUi(this);


//    connect (ui->comboRegions, SIGNAL(currentIndexChanged(int)), this, SLOT(itemChanged(int)));
}

CropperDlg::~CropperDlg()
{
    delete ui;
}

void CropperDlg::populateCombos()
{
    ccHObject::Container objs = vombat::theInstance()->getAllObjectsInTreeThatAre(CC_TYPES::HIERARCHY_OBJECT);

    LOG(INFO) << "found " << objs.size();

    for (ccHObject * obj: objs)
    {
        if (obj->getName() == "DB Tree")
            continue;

        LOG(INFO) << "updating with id: " << obj->getUniqueID();
        ui->comboRubberbands->addItem(obj->getName(), QVariant(obj->getUniqueID()));
        ui->comboCroppables->addItem(obj->getName(), QVariant(obj->getUniqueID()));
    }
}

void CropperDlg::clearCombos()
{
//    ui->comboBox->clear();
	this->ui->comboRubberbands->clear();
	this->ui->comboCroppables->clear();
}

ccHObject::Container CropperDlg::getSelections()
{
    ccHObject * selected  = comboToObject(this->ui->comboRubberbands);
    ccHObject::Container childrens = vombat::theInstance()->getAllChildren(selected);
    ccHObject::Container out;

    for (ccHObject * obj: childrens)
    {
        ccSPCElementShell * asspc = dynamic_cast<ccSPCElementShell *> (obj);
        if (obj)
        {
            if (asspc->isASPC(&spc::SelectionRubberband::Type))
            {
                out.push_back(obj);
            }
        }

    }

    return out;
}



ccHObject::Container CropperDlg::getCroppables()
{
    ccHObject * selected  = comboToObject(this->ui->comboCroppables);
    ccHObject::Container out, plines, clouds;



    selected->filterChildren(plines,false, CC_TYPES::POLY_LINE,true);

    selected->filterChildren(clouds,false, CC_TYPES::POINT_CLOUD,true);


    for (ccHObject * obj : plines)
        out.push_back(obj);

    for (ccHObject * obj : clouds)
        out.push_back(obj);

    return out;
}

ccHObject *CropperDlg::comboToObject(const QComboBox *combo)
{

    int sel_id =combo->currentIndex();


    LOG(INFO) << "size of combo " << combo->count();
    for (int i =0; i < combo->count(); ++i)
    {
        LOG(INFO) << "combo el " << combo->itemText(i).toStdString();
    }

    LOG(INFO) << "selected index is " << sel_id;

    int id = combo->itemData(sel_id).toInt();

    LOG(INFO) << "unique id of selected:  "<<  id;

    ccHObject * obj = vombat::theInstance()->getMainAppInterface()->dbRootObject()->find(id);

    if (obj)
    {
        LOG(INFO) << "obj name is " << obj->getName().toStdString();
    }
    return obj;
}

//bool CropperDlg::cropStrataTraces() const
//{
//    return ui->checkBoxCropStrataTraces->checkState();
//}

//bool CropperDlg::outputAttitudes() const
//{
//    return ui->checkBoxGenerateAttitudes->checkState();
//}

//bool CropperDlg::outputRulers() const
//{
//    return ui->checkBoxGenerateRulers->checkState();
//}

//bool CropperDlg::generateRegions() const
//{
//    return ui->checkBoxGenerateRegions->checkState();
//}


