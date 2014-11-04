#ifndef CLOUDMAPPER_H
#define CLOUDMAPPER_H
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

#include <ccScalarField.h>

#include <ccPointCloud.h>

#include <spc/elements/PointCloudBase.h>



class spcCCPointCloud: public spc::PointCloudBase
{
public:

    using spc::PointCloudBase::IndexT;

    SPC_OBJECT(spcCCPointCloud)

    spcCCPointCloud(ccPointCloud *cloud)
    {
        in_cloud  = cloud;
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
    ccPointCloud * in_cloud;




    // PointCloudBase interface
public:
    /** \todo IMPLEMENT THIS METHOD **/
    virtual spc::OrientedSensor getSensor() const
    {
        spc::OrientedSensor sensor;
        std::cout << "WARNING!!! getSensor in spcCCPointCloud is only a fake virtual function!!!!!!!"<< std::endl;
        return sensor;
    }
    /** \todo IMPLEMENT THIS METHOD **/
    virtual void setSensor(const spc::OrientedSensor &sensor) const
    {
        std::cout << "WARNING!!! setSensor in spcCCPointCloud is only a fake virtual function!!!!!!!"<< std::endl;

    }

};




#endif // CLOUDMAPPER_H
