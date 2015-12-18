#ifndef AUTOCOMPUTE_TIME_SERIES_H
#define AUTOCOMPUTE_TIME_SERIES_H

#include "BaseFilter.h"
#include <ccSample.h>
#include <ccPointCloud.h>
#include <ccHObjectCaster.h>
#include <ScalarField.h>
#include <helpers/spcCCPointCloud.h>


class AutoComputeTimeSeries : public BaseFilter
{
public:
    AutoComputeTimeSeries(ccPluginInterface * parent_plugin = 0);

    // BaseFilter interface
public:
    int compute();

protected:
    int checkSelected()
    {

        if (vombat::theInstance()->getSelected().size() != 1)
        {
            return -1;
        }

        ccHObject * root =  vombat::theInstance()->getSelected().at(0);
        ccSPCElementShell * el = dynamic_cast<ccSPCElementShell *> (root);


        ccHObject::Container objects = vombat::theInstance()->getAllObjectsInTreeThatAre(CC_TYPES::POINT_CLOUD);

        if (objects.size() > 0)
        {

            ccHObject * cloud = objects.at(0);

            ccPointCloud * ascloud =ccHObjectCaster::ToPointCloud(cloud);


            if (cloud)
            {
                LOG(INFO) << "found cloud";
                spc::spcCCPointCloud::Ptr t =  spc::spcCCPointCloud::fromccPointCloud(ascloud) ;
                try {
                    LOG(INFO)  << "at check time" << t->getPtr();
                } catch ( std::exception& e ) {
                    LOG(INFO) << "got exception" << e.what();
                }

            }

        }

        if (el != NULL)
            return 1;
        else
            return 0;
    }

    int openInputDialog()
    {
        return 1;
    }
};

#endif // AutoComputeTimeSeries_H
