#include "AddSample.h"
#include <ccSample.h>
#include <ccPointCloud.h>
#include <ccHObjectCaster.h>
#include <ScalarField.h>
#include <spc/core/logging.h>
#include <ccPolyline.h>
#include <ccLinearGeologicalFeature.h>


#include <spc/elements/LinearGeologicalFeature.h>
AddSample::AddSample(ccPluginInterface* parent_plugin)
    : BaseFilter(FilterDescription("Add a Sample Object",
                                   "Add a Sample Object",
                                   "Add a Sample Object",
                                   ":/toolbar/icons/sample.png"),
                 parent_plugin)
{
    this->setShowProgressBar(false);
}

int AddSample::compute()
{

    ccHObject::Container clouds;
    getSelectedEntitiesThatAre(CC_TYPES::POINT_CLOUD, clouds);

    for (ccHObject* obj : clouds) {
        ccPointCloud* cloud = ccHObjectCaster::ToPointCloud(obj);
        size_t n_scalars = cloud->getNumberOfScalarFields();

        if (cloud->size() >= 100) {
            LOG(ERROR) << "cannot create so many samples.";
            continue;
        }

        for (int i = 0; i < cloud->size(); ++i) {
            CCVector3 p;
            cloud->getPoint(i, p);
            ccSample* sample = new ccSample(p);

            for (int j = 0; j < n_scalars; ++j) {
                CCLib::ScalarField* sf = cloud->getScalarField(j);
                float value = sf->getValue(i);
                QString sf_name = sf->getName();

                //                sample->getSample()->getVariantPropertiesRecord().property(sf_name.toStdString()) = value;
            }

            sample->setVisible(true);
            emit newEntity(sample);
        }
    }

    ccHObject::Container labels;
    getSelectedEntitiesThatAre(CC_TYPES::LABEL_2D, labels);

    for (ccHObject* obj : labels) {
        cc2DLabel* label = ccHObjectCaster::To2DLabel(obj);

        ccSample* sample = new ccSample(label);
        sample->setVisible(true);

        emit newEntity(sample);
    }

    ccHObject::Container polylines;
    getSelectedEntitiesThatAre(CC_TYPES::POLY_LINE, polylines);

    for (ccHObject* obj : polylines) {
        ccPolyline* pline = ccHObjectCaster::ToPolyline(obj);


        ccLinearGeologicalFeature* linear  = ccLinearGeologicalFeature::fromPolyline(*pline);

//         = new ccLinearGeologicalFeature();
//        spc::LinearGeologicalFeature::Ptr asspc =  linear->getSPCElement<spc::LinearGeologicalFeature>();
//        for (int i = 0; i < pline->getAssociatedCloud()->size() ; ++i)
//        {
//            CCVector3 p;
//            pline->getAssociatedCloud()->getPoint(i, p);

//            Eigen::Map<Eigen::Vector3f> mapped (&p[0]);


//            asspc->addPoint(mapped);



//        }

        linear->setVisible(true);
        emit newEntity(linear);




    }




    return 1;
}

int AddSample::checkSelected()
{
    ccHObject::Container selected;
    getSelectedEntitiesThatAre(CC_TYPES::POINT_CLOUD, selected);
    getSelectedEntitiesThatAre(CC_TYPES::POLY_LINE, selected);
    getSelectedEntitiesThatAre(CC_TYPES::LABEL_2D, selected);

    if (selected.size() > 0)
        return 1;
    else
        return -1;
}
