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

    if (!cloud_cont)
    {
        LOG(INFO) << "no cloud container found";
        return;
    }

    ccHObject::Container  filtered;
    cloud_cont->filterChildren(filtered, false, CC_TYPES::POINT_CLOUD,true);

    LOG(INFO) << "there are " << filtered.size() << "point clouds";

    std::list<FieldDescriptor> field_list;

    for (ccHObject * obj: filtered)

    {
        ccPointCloud * cloud = ccHObjectCaster::ToPointCloud(obj);
        if (cloud)
        {
            if (cloud->hasColors())
            {
                field_list.push_back(FieldDescriptor("R", true, spc::PointCloudBase::COLORS_ENUM::R));
                field_list.push_back(FieldDescriptor("G", true, spc::PointCloudBase::COLORS_ENUM::G));
                field_list.push_back(FieldDescriptor("B", true, spc::PointCloudBase::COLORS_ENUM::B));
                field_list.push_back(FieldDescriptor("Average", true, spc::PointCloudBase::COLORS_ENUM::AVERAGE));
            }

            for (int i = 0; i < cloud->getNumberOfScalarFields(); ++i)
            {
                CCLib::ScalarField * field = cloud->getScalarField(i);
                field_list.push_back(FieldDescriptor(field->getName(), false));
            }


        }

    }


    field_list.sort();
    field_list.unique();

    for ( FieldDescriptor f: field_list)
    {
        QString name;
        if (f.iscolor_)
        {
             name = QString(f.name_.c_str()) + " [Color Cannel]";
        }
        else
        {
            name = QString(f.name_.c_str());

        }

        QVariant desc;
        desc.setValue(f);
        this->comboScalarFields->addItem(name , desc);
    }

}


