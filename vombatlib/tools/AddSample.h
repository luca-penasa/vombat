#ifndef ADDSAMPLE_H
#define ADDSAMPLE_H

#include <qPCL/PclUtils/filters/BaseFilter.h>
#include <ccSample.h>
#include <ccPointCloud.h>
#include <ccHObjectCaster.h>
#include <ScalarField.h>
class AddSample : public BaseFilter
{
public:
    AddSample(ccPluginInterface * parent_plugin = 0);

    // BaseFilter interface
public:
    int compute()
    {

        ccHObject::Container clouds;
        getSelectedEntitiesThatAre(CC_TYPES::POINT_CLOUD, clouds);

        for(ccHObject * obj: clouds)
        {
            ccPointCloud * cloud = ccHObjectCaster::ToPointCloud(obj);
            size_t n_scalars = cloud->getNumberOfScalarFields();


            for (int i = 0; i < cloud->size(); ++i)
            {
                CCVector3 p;
                cloud->getPoint(i, p);
                ccSample * sample = new ccSample(p);

                for (int j =0 ; j < n_scalars; ++j)
                {
                    CCLib::ScalarField * sf = cloud->getScalarField(j);
                    float value = sf->getValue(i);
                    QString sf_name = sf->getName();

                    sample->getSample()->getVariantPropertiesRecord().property(sf_name.toStdString()) = value;
                }

                sample->setVisible(true);
                emit newEntity(sample);
            }

        }



        ccHObject::Container labels;
        getSelectedEntitiesThatAre(CC_TYPES::LABEL_2D, labels);


        for(ccHObject * obj: labels)
        {
            cc2DLabel * label = ccHObjectCaster::To2DLabel(obj);

            ccSample * sample = new ccSample(label);
            sample->setVisible(true);

            emit newEntity(sample);

        }


    }

protected:
    int checkSelected()
    {
        ccHObject::Container selected;
        getSelectedEntitiesThatAre(CC_TYPES::POINT_CLOUD, selected);
        getSelectedEntitiesThatAre(CC_TYPES::LABEL_2D, selected);

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
