#ifndef CLOUDMAPPER_H
#define CLOUDMAPPER_H
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>


#include <ccPointCloud.h>

#include <spc/elements/PointCloudBase.h>



class spcCCPointCloud: public spc::PointCloudBase
{
public:

    SPC_OBJECT(spcCCPointCloud)

    spcCCPointCloud(ccPointCloud *cloud)
    {
        in_cloud  = cloud;
    }

    virtual void getPoint (const int id, float &x, float &y, float &z) const;

    virtual void setPoint(const int id, const float x, const float y, const float z);

    virtual void getFieldValue(const int id, const std::string fieldname,  float &val);

    virtual int size() const;

    virtual bool hasField(const std::string fieldname);

    virtual void resize(size_t s);

protected:
    ccPointCloud * in_cloud;
};




#endif // CLOUDMAPPER_H
