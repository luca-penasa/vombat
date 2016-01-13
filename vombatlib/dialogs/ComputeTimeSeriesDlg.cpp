#include "ComputeTimeSeriesDlg.h"
#include <spc/core/logging.h>
#include <ccHObjectCaster.h>
#include <ccScalarField.h>

ComputeTimeSeriesDlg::ComputeTimeSeriesDlg(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);

    this->comboClouds->addShownType(CC_TYPES::HIERARCHY_OBJECT);
    this->comboRegions->addShownType(CC_TYPES::HIERARCHY_OBJECT);
    this->comboModels->addShownType(CC_TYPES::HIERARCHY_OBJECT);

    connect (this->comboClouds, SIGNAL(currentIndexChanged(int)), this , SLOT(changedCloudSelection(int)));
}

void ComputeTimeSeriesDlg::changedCloudSelection(int n)
{

    this->comboScalarFields->clear();
    LOG(INFO) << "cloud selection changed";


    ccHObject * cloud_cont = this->comboClouds->getSelectedObject();

    ccHObject::Container  filtered;
    cloud_cont->filterChildren(filtered, false, CC_TYPES::POINT_CLOUD,true);

    LOG(INFO) << "there are " << filtered.size() << "point clouds";

    std::list<std::string> field_list;

    for (ccHObject * obj: filtered)

    {
        ccPointCloud * cloud = ccHObjectCaster::ToPointCloud(obj);
        if (cloud)
        {
            if (cloud->hasColors())
            {
                field_list.push_back("R Color");
                field_list.push_back("G Color");
                field_list.push_back("B Color");
            }

            for (int i = 0; i < cloud->getNumberOfScalarFields(); ++i)
            {
                CCLib::ScalarField * field = cloud->getScalarField(i);
                field_list.push_back(field->getName());
            }


        }

    }


    field_list.sort();
    field_list.unique();

    for (std::string f: field_list)
    {
        this->comboScalarFields->addItem(QString(f.c_str()));
    }

}
