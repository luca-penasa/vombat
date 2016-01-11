#include "AutoComputeTimeSeries.h"
#include <spc/methods/TimeSeriesAutoExtractor.h>
#include <LoadSPCElement.h>
#include <ccSample.h>
#include <ccPointCloud.h>
#include <ccHObjectCaster.h>
#include <ScalarField.h>
#include <helpers/spcCCPointCloud.h>
#include <vombat.h>


AutoComputeTimeSeries::AutoComputeTimeSeries(ccPluginInterface* parent_plugin)
    : BaseFilter(FilterDescription("Automatically compute time series for selections defined in childrens",
                     "Automatically compute time series for selections defined in childrens",
                     "Automatically compute time series for selections defined in childrens",
                     ":/toolbar/icons/time_series_multi.png"),
          parent_plugin)
{
    this->setShowProgressBar(false);
}

int AutoComputeTimeSeries::compute()
{
    LOG(INFO) << "starting to compute() autoComputeTimeSeries";

    ccHObject* root = vombat::theInstance()->getSelected().at(0);
    ccSPCElementShell* el = dynamic_cast<ccSPCElementShell*>(root);

    LOG(INFO) << "nhere";

    if (!el)
        LOG(INFO) << "no spc element!!!";

    ccHObject::Container clouds = vombat::theInstance()->getAllObjectsInTreeThatAre(CC_TYPES::POINT_CLOUD);

    LOG(INFO) << "found  " << clouds.size() << " clouds in addition!";

    std::vector<spc::PointCloudBase::Ptr> add_clouds;
    for (auto c : clouds) {

        LOG(INFO) << "creating special cloud";

        ccPointCloud* ascloud = static_cast<ccPointCloud*>(c);

        spcCCPointCloud::Ptr asspc = spcCCPointCloud::fromccPointCloud(ascloud);

        LOG(INFO) << "done";
        add_clouds.push_back(asspc);

        LOG(INFO) << "Added additional cloud " << asspc;
    }

    spc::ElementBase::Ptr r = el->getSPCElement();

    spc::TimeSeriesAutoExtractor extractor;

    extractor.setRoot(r);
    extractor.setAdditionalCloudsInMemory(add_clouds);
    extractor.compute();

    LoadSPCElement::rebuildMyChildsRecursive(vombat::theInstance()->getObjectFromElement(r));

    entityHasChanged(vombat::theInstance()->getObjectFromElement(r));

    LOG(INFO) << "done";

    return 1;
}

int AutoComputeTimeSeries::checkSelected()
{

    if (vombat::theInstance()->getSelected().size() != 1) {
        return -1;
    }

    ccHObject* root = vombat::theInstance()->getSelected().at(0);
    ccSPCElementShell* el = dynamic_cast<ccSPCElementShell*>(root);

    ccHObject::Container objects = vombat::theInstance()->getAllObjectsInTreeThatAre(CC_TYPES::POINT_CLOUD);

    if (objects.size() > 0) {

        ccHObject* cloud = objects.at(0);

        ccPointCloud* ascloud = ccHObjectCaster::ToPointCloud(cloud);

        if (cloud) {
            LOG(INFO) << "found cloud";
//            spc::spcCCPointCloud::Ptr t = spc::spcCCPointCloud::fromccPointCloud(ascloud);
            try {
//                LOG(INFO) << "at check time" << t->getPtr();
            }
            catch (std::exception& e) {
                LOG(INFO) << "got exception" << e.what();
            }
        }
    }

    if (el != NULL)
        return 1;
    else
        return 0;
}
