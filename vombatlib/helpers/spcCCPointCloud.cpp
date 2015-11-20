#include "spcCCPointCloud.h"
#include <ScalarField.h>

void spcCCPointCloud::getPoint(const IndexT id, float &x, float &y, float &z) const
{
    assert(id < in_cloud->size());
    CCVector3 point;
    in_cloud->getPoint(id, point);
    x = point.x;
    y = point.y;
    z = point.z;
}

void spcCCPointCloud::setPoint(const IndexT id, const float x, const float y, const float z)
{
     const CCVector3 * p = in_cloud->getPointPersistentPtr(id);

     CCVector3 * ptr = const_cast<CCVector3*> (p);


    (*ptr).x = x;
    (*ptr).y = y;
    (*ptr).z = z;
}


bool spcCCPointCloud::hasField(const std::string fieldname) const
{

    if ((fieldname == "x") | (fieldname == "y") | (fieldname == "z")) // every ccpoint cloud have geometric infos
    {
            return true;
    }

    else if (fieldname == "normal_x" | fieldname == "normal_y" | fieldname == "normal_z")
    {
        return in_cloud->hasNormals();
    }

    int id =  in_cloud->getScalarFieldIndexByName(fieldname.c_str());
    if (id < 0)
        return false;
    else
        return -1;
}

void spcCCPointCloud::resize(const IndexT s)
{
    in_cloud->resize(s);
}

std::vector<std::string> spcCCPointCloud::getFieldNames() const
{
    std::vector<std::string> out;
    int n = in_cloud->getNumberOfScalarFields();
    for (int i = 0; i < n; ++i)
        out.push_back(in_cloud->getScalarFieldName(i));

    return out;
}

void spcCCPointCloud::getFieldValue(const spcCCPointCloud::IndexT id, const std::string fieldname, float &val) const
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

int spcCCPointCloud::nameToComponent(const std::string &name) const
{
    if (name == "x" || name == "normal_x")
        return 0;
    else if (name == "y"|| name == "normal_y")
        return 1;
    else if (name == "z"|| name == "normal_z")
        return 2;
}

void spcCCPointCloud::setFieldValue(const spcCCPointCloud::IndexT id, const std::string fieldname, const float &val)
{
    if (fieldname == "x" ||fieldname == "y" ||fieldname == "z")
    {
        LOG(ERROR) << "Cannot modify x, y, z values in ccPointCloud!";
    }
    else if (fieldname == "normal_x" ||fieldname == "normal_y" ||fieldname == "normal_z")
    {
        LOG(ERROR) << "Cannot modify normals values in ccPointCloud!";
    }
    else
    {
        int i = in_cloud->getScalarFieldIndexByName(fieldname.c_str());
        ccScalarField * sf = static_cast<ccScalarField*>(in_cloud->getScalarField(i));
        sf->setValue(id, val);
    }
}

void spcCCPointCloud::addField(const std::string &name)
{
    if (name  == "normal_x" ||name  == "normal_y" ||name  == "normal_z" )
    {
        in_cloud->reserveTheNormsTable();
    }

    ccScalarField * f = new ccScalarField(name.c_str());
    f->resize(in_cloud->resize(in_cloud->size()));
    in_cloud->addScalarField(f);
}

spcCCPointCloud::IndexT spcCCPointCloud::getNumberOfPoints() const
{
    return in_cloud->size();
}
