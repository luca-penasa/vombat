#ifndef LOAD_CLOUD_DATA_SOURCE_H
#define LOAD_CLOUD_DATA_SOURCE_H

#include <qPCL/PclUtils/filters/BaseFilter.h>
#include <ccSample.h>
#include <ccPointCloud.h>
#include <ccHObjectCaster.h>
#include <ScalarField.h>

#include <FileIOFilter.h>

#include <spc/elements/MovableElement.h>

#include <spc/elements/CloudDataSourceOnDisk.h>
class LoadCloudDataSource : public BaseFilter
{
public:
    LoadCloudDataSource(ccPluginInterface * parent_plugin = 0);

    // BaseFilter interface
public:
    int compute()
    {

        DLOG(INFO) << "going to compue!";

        ccHObject::Container objects = vombat::theInstance()->getAllObjectsSelectedBySPCDti(&spc::CloudDataSourceOnDisk::Type);


        for(ccHObject * obj: objects)
        {

            DLOG(INFO) << "working on " << obj;

            ccMyBaseObject * myobj = dynamic_cast<ccMyBaseObject *> (obj);

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

protected:
    int checkSelected()
    {
        ccHObject::Container selected = vombat::theInstance()->getAllObjectsSelectedBySPCDti(&spc::CloudDataSourceOnDisk::Type);

        if (selected.size() > 0)
            return 1;
        else
            return -1;
    }

    int openInputDialog()
    {
        return 1;
    }
};

#endif // ADDSAMPLE_H
