#pragma once
#ifndef CLOUDMAPPER_H
#define CLOUDMAPPER_H
//#include <pcl/point_cloud.h>
//#include <pcl/point_types.h>

#include <ccScalarField.h>

#include <ccPointCloud.h>

#include <spc/elements/PointCloudBase.h>
#include <ccSPCElementShell.h>

namespace spc
{

class spcCCPointCloud: public PointCloudBase
{
public:

    using PointCloudBase::IndexT;

    SPC_ELEMENT(spcCCPointCloud)
    EXPOSE_TYPE


    void setInCloud (ccPointCloud * cloud)
    {
        cloud_ = cloud;
    }

//    SPC_ELEMENT(spcCCPointCloud)

    static spcCCPointCloud::Ptr fromccPointCloud(ccPointCloud *cloud)
    {

        spcCCPointCloud::Ptr out (new spcCCPointCloud);

        if (!cloud)
        {
            LOG(ERROR) << "Trying to create spcCCPointCloud from a null ptr";
            return nullptr;
        }


        LOG(INFO) << "spcCCPointCloud constructor here";
        out->setInCloud( cloud );

        for (int i = 0 ; i < cloud->getChildrenNumber(); ++i)
        {

             ccHObject * child = cloud->getChild(i);

             LOG(INFO) << "translating childs " << i << " " <<  child->getName().toStdString().c_str();

             // now we need to know is its s spc-base object
             ccSPCElementShell * shell  = dynamic_cast<ccSPCElementShell *> (child);

//             LOG(INFO)<< "PTR " << shell->getSPCElement()->getPtr();

//            LOG(INFO)<< "PTR " << out->getPtr();


             if (shell)
             {
                 LOG(INFO) << "child was spc";


                 LOG(INFO) << "element is " << shell->getSPCElement();
                 out->addChild(shell->getSPCElement());

                 LOG(INFO) << "child was sp";
             }
             else
             {
                 LOG(INFO) << "child was NOT spc";
             }

             LOG(INFO) << "done " << i << " " <<  child->getName().toStdString().c_str();

        }


        return out;
    }

    spcCCPointCloud()
    {



    }

    virtual void getPoint (const IndexT id, float &x, float &y, float &z) const override;

    virtual void setPoint(const IndexT id, const float x, const float y, const float z) override;

    virtual IndexT getNumberOfPoints() const override;

    virtual void resize(const IndexT s) override;

    virtual std::vector<std::string> getFieldNames() const override;

    virtual void getFieldValue(const IndexT id, const std::string fieldname, float &val) const override;

    virtual void setFieldValue(const IndexT id, const std::string fieldname, const float &val) override;

    virtual void addField(const std::string &name) override;

    virtual bool hasField(const std::string fieldname) const override;


    int nameToComponent(const std::string &name) const ;
protected:
    ccPointCloud * cloud_;




    // PointCloudBase interface
public:
    /** \todo IMPLEMENT THIS METHOD **/
    virtual spc::OrientedSensor getSensor() const;
    /** \todo IMPLEMENT THIS METHOD **/
    virtual void setSensor(const spc::OrientedSensor &sensor) const;


//    // ElementBase interface
//public:
//    virtual ElementBase::Ptr clone() const override;


    // PointCloudBase interface
public:
    virtual bool getRGBField(const COLORS_ENUM &color, VectorXf &vector, const std::vector<IndexT> &indices) const override;
};



} // end nspace
#endif // CLOUDMAPPER_H
