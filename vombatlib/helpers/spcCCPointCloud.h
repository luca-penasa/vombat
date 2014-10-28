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

    SPC_OBJECT(spcCCPointCloud)

    spcCCPointCloud(ccPointCloud *cloud)
    {
        in_cloud  = cloud;
    }

    virtual void getPoint (const int id, float &x, float &y, float &z) const;

    virtual void setPoint(const int id, const float x, const float y, const float z);

    virtual int size() const;

    virtual void resize(size_t s);

protected:
    ccPointCloud * in_cloud;

    // PointCloudBase interface
public:
    virtual std::vector<std::string> getFieldNames() const
    {
        std::vector<std::string> out;
        int n = in_cloud->getNumberOfScalarFields();
        for (int i = 0; i < n; ++i)
            out.push_back(in_cloud->getScalarFieldName(i));

        return out;
    }

    // PointCloudBase interface
public:
    virtual void getFieldValue(const int id, const std::string fieldname, float &val) const
    {
        if (fieldname == "x" ||fieldname == "y" ||fieldname == "z")
        {
            int component = nameToComponent(fieldname);
            val = in_cloud->getPoint(id)->operator [](component);
        }
        else if (fieldname == "normal_x" ||fieldname == "normal_y" ||fieldname == "normal_z")
        {
             int component = nameToComponent(fieldname);
             val = in_cloud->getPointNormal(id)[component];
        }
        else
        {
            int i = in_cloud->getScalarFieldIndexByName(fieldname.c_str());
            ccScalarField * sf = static_cast<ccScalarField*>(in_cloud->getScalarField(i));
            val  = sf->getValue(id);
        }
    }

    int nameToComponent(const std::string &name) const
    {
        if (name == "x" || name == "normal_x")
            return 0;
        else if (name == "y"|| name == "normal_y")
            return 1;
        else if (name == "z"|| name == "normal_z")
            return 2;
    }

    virtual void setFieldValue(const int id, const std::string fieldname, const float &val)
    {
        if (fieldname == "x" ||fieldname == "y" ||fieldname == "z")
        {
            PCL_ERROR("Cannot modify x, y, z values in ccPointCloud!\n");
        }
        else if (fieldname == "normal_x" ||fieldname == "normal_y" ||fieldname == "normal_z")
        {
            PCL_ERROR("Cannot modify normals values in ccPointCloud!\n");
        }
        else
        {
            int i = in_cloud->getScalarFieldIndexByName(fieldname.c_str());
            ccScalarField * sf = static_cast<ccScalarField*>(in_cloud->getScalarField(i));
            sf->setValue(id, val);
        }
    }
    virtual void addField(const std::string &name)
    {
        if (name  == "normal_x" ||name  == "normal_y" ||name  == "normal_z" )
        {
            in_cloud->reserveTheNormsTable();
        }

        ccScalarField * f = new ccScalarField(name.c_str());
        f->resize(in_cloud->resize(in_cloud->size()));
        in_cloud->addScalarField(f);
    }
    virtual bool hasField(const std::string fieldname) const;


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
