#include "spcCCPointCloud.h"


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


void spcCCPointCloud::getFieldValue(const int id, const std::string fieldname, float &val)
{
    if (fieldname == "x")
        val = in_cloud->getPoint(id)->x;

    if (fieldname == "y")
        val = in_cloud->getPoint(id)->y;

    if (fieldname == "z")
        val = in_cloud->getPoint(id)->z;

    int field_id = in_cloud->getScalarFieldIndexByName(fieldname.c_str());

    if (field_id != -1)
    {
        CCLib::ScalarField * field = in_cloud->getScalarField(field_id);
        val = field->getValue(id);
    }
}


bool spcCCPointCloud::hasField(const std::string fieldname)
{

    if ((fieldname == "x") | (fieldname == "y") | (fieldname == "z")) // every ccpoint cloud have geometric infos
    {
            return true;
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
