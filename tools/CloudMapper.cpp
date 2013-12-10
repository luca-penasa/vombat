#include "CloudMapper.h"


void spcCCPointCloud::getPoint(int id, float &x, float &y, float &z) const
{
    assert(id < in_cloud->size());
    CCVector3 point;
    in_cloud->getPoint(id, point);
    x = point.x;
    y = point.y;
    z = point.z;
}


void spcCCPointCloud::getFieldValue(const int id, const std::string fieldname, float &val)
{
    int field_id = in_cloud->getScalarFieldIndexByName(fieldname.c_str());

    if (field_id != -1)
    {
        CCLib::ScalarField * field = in_cloud->getScalarField(field_id);
        val = field->getValue(id);
    }
}


bool spcCCPointCloud::hasField(const std::string fieldname)
{
    int id =  in_cloud->getScalarFieldIndexByName(fieldname.c_str());
    if (id < 0)
        return false;
    else
        return -1;
}





int spcCCPointCloud::getSize() const
{
    return in_cloud->size();
}
