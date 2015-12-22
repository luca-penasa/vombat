#include "LoadCloudDataSource.h"
#include <ccSample.h>
#include <ccPointCloud.h>
#include <ccHObjectCaster.h>
#include <ScalarField.h>

#include <FileIOFilter.h>

#include <spc/elements/MovableElement.h>

#include <spc/elements/CloudDataSourceOnDisk.h>
#include <vombat.h>

LoadCloudDataSource::LoadCloudDataSource(ccPluginInterface * parent_plugin): BaseFilter(FilterDescription(   "Load the point cloud from a data source",
                                                       "Load the point cloud from a data source",
                                                       "Load the point cloud from a data source",
                                                       ":/toolbar/icons/cloud_data_source_on_disk_load.png"), parent_plugin)
{
    this->setShowProgressBar(false);
}

int LoadCloudDataSource::compute()
{

    DLOG(INFO) << "going to compue!";

    ccHObject::Container objects = vombat::theInstance()->getAllObjectsSelectedBySPCDti(&spc::CloudDataSourceOnDisk::Type);


    for(ccHObject * obj: objects)
    {

        DLOG(INFO) << "working on " << obj;

        ccSPCElementShell * myobj = dynamic_cast<ccSPCElementShell *> (obj);

        CHECK(myobj != NULL) << "Bad error. pointer is null!";

        spc::CloudDataSourceOnDisk::Ptr source_ptr = spcDynamicPointerCast<spc::CloudDataSourceOnDisk> (myobj->getSPCElement());


        std::string fname = source_ptr->getFilename();

        FileIOFilter::LoadParameters pars;

        ccHObject * cloud = FileIOFilter::LoadFromFile(QString(fname.c_str()), pars);

        cloud->setVisible(true);
        obj->addChild(cloud);
        emit newEntity(obj);


    }

    return 1;
}

int LoadCloudDataSource::checkSelected()
{
    ccHObject::Container selected = vombat::theInstance()->getAllObjectsSelectedBySPCDti(&spc::CloudDataSourceOnDisk::Type);

    if (selected.size() > 0)
        return 1;
    else
        return -1;
}
