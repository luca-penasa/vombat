#include "spcCCPointCloud.h"
#include <ScalarField.h>

void spcCCPointCloud::getPoint(int id, float &x, float &y, float &z) const
{
    assert(id < in_cloud->size());
    CCVector3 point;
    in_cloud->getPoint(id, point);
    x = point.x;
    y = point.y;
    z = point.z;
}

void spcCCPointCloud::setPoint(const int id, const float x, const float y, const float z)
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

void spcCCPointCloud::resize(size_t s)
{
    in_cloud->resize(s);
}





int spcCCPointCloud::size() const
{
    return in_cloud->size();
}
