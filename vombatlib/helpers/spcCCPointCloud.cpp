
#include "spcCCPointCloud.h"
#include <ScalarField.h>
#include <spc/elements/OrientedSensor.h>
namespace spc
{

DtiClassType spcCCPointCloud::Type = DtiClassType("spcCCPointCloud", &PointCloudBase::Type);


void spcCCPointCloud::getPoint(const IndexT id, float &x, float &y, float &z) const
{
    assert(id < cloud_->size());
    CCVector3 point;
    cloud_->getPoint(id, point);
    x = point.x;
    y = point.y;
    z = point.z;
}

void spcCCPointCloud::setPoint(const IndexT id, const float x, const float y, const float z)
{
     const CCVector3 * p = cloud_->getPointPersistentPtr(id);

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
        return cloud_->hasNormals();
    }

    int id =  cloud_->getScalarFieldIndexByName(fieldname.c_str());
    if (id < 0)
        return false;
    else
        return -1;
}

void spcCCPointCloud::resize(const IndexT s)
{
    cloud_->resize(s);
}

std::vector<std::string> spcCCPointCloud::getFieldNames() const
{
    std::vector<std::string> out;
    int n = cloud_->getNumberOfScalarFields();
    for (int i = 0; i < n; ++i)
        out.push_back(cloud_->getScalarFieldName(i));

    return out;
}

void spcCCPointCloud::getFieldValue(const spcCCPointCloud::IndexT id, const std::string fieldname, float &val) const
{
    if (fieldname == "x" ||fieldname == "y" ||fieldname == "z")
    {
        int component = nameToComponent(fieldname);
        val = cloud_->getPoint(id)->operator [](component);
    }
    else if (fieldname == "normal_x" ||fieldname == "normal_y" ||fieldname == "normal_z")
    {
        int component = nameToComponent(fieldname);
        val = cloud_->getPointNormal(id)[component];
    }


    else
    {
        int i = cloud_->getScalarFieldIndexByName(fieldname.c_str());
        ccScalarField * sf = static_cast<ccScalarField*>(cloud_->getScalarField(i));
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
        int i = cloud_->getScalarFieldIndexByName(fieldname.c_str());
        ccScalarField * sf = static_cast<ccScalarField*>(cloud_->getScalarField(i));
        sf->setValue(id, val);
    }
}

void spcCCPointCloud::addField(const std::string &name)
{
    if (name  == "normal_x" ||name  == "normal_y" ||name  == "normal_z" )
    {
        cloud_->reserveTheNormsTable();
    }

    ccScalarField * f = new ccScalarField(name.c_str());
    f->resize(cloud_->resize(cloud_->size()));
    cloud_->addScalarField(f);
}

spcCCPointCloud::IndexT spcCCPointCloud::getNumberOfPoints() const
{
    return cloud_->size();
}

spc::OrientedSensor spc::spcCCPointCloud::getSensor() const
{
    spc::OrientedSensor sensor;
    LOG(WARNING) << "WARNING!!! getSensor in spcCCPointCloud is only a fake virtual function!!!!!!!";
    return sensor;
}

void spcCCPointCloud::setSensor(const OrientedSensor &sensor) const
{
    LOG(WARNING)<< "WARNING!!! setSensor in spcCCPointCloud is only a fake virtual function!!!!!!!";

}




}// end nspace


bool spc::spcCCPointCloud::getRGBField(const PointCloudBase::COLORS_ENUM &color, VectorXf &vector, const std::vector<PointSetBase::IndexT> &indices) const
{

        // put everything in an eigen map fo easy access
        // this only works on 64 bit systems!!!!

        const ColorCompType * firstc = cloud_->getPointColor(0);

        typedef Eigen::Matrix<ColorCompType, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> ColMatType;
//        typedef Eigen::Matrix<ColorCompType, Eigen::Dynamic, 1> ColVectType;

        Eigen::Map<ColMatType> map(const_cast<ColorCompType *> (firstc), cloud_->size(), 3);


        if (color != COLORS_ENUM::AVERAGE)
        {
            Eigen::Block<Eigen::Map<ColMatType>, -1, 1> all = map.col((int) color);
            if (indices.empty())
                vector =  all.cast<float>();
            else
            {
                vector.resize(indices.size());
                size_t counter = 0;
                for (const int &id: indices)
                {
                    vector(counter++) = all(id);
                }
            }
            return true;
        }

        else // average was requested
        {
            Eigen::Matrix<ColorCompType, Eigen::Dynamic, 3> mat;
            if (indices.empty())
            {
                vector = (map.rowwise().sum().array() / 3.0).cast<float>();
            }
            else
            {
                vector.resize(indices.size());
                size_t counter = 0;
                for (const int &id: indices)
                {
                    vector(counter++) = static_cast<float>(map.row(id).sum()) / 3.0;
                }
            }
            return true;
        }


}
