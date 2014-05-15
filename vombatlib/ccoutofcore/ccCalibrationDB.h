#ifndef CC_CALIBRATION_DB_H
#define CC_CALIBRATION_DB_H


#include <ccoutofcore/ccMyBaseObject.h>


#include <spc/calibration/CalibrationDataDB.h>


#include <QIcon>

#include <ccBox.h>



///
/// \brief The ccAttitude class gives a qCC-valid representation of a geological attitude
///
class ccCalibrationDB:  public ccMyBaseObject

{
public:


    ccCalibrationDB();

    ccCalibrationDB(spc::CalibrationDataDB db)
    {
        m_calibration_db_ = boost::make_shared<spc::CalibrationDataDB> (db);
        initMetadata();
    }

    //inherited methods (ccHObject)
    virtual bool hasColors() const { return true; }
//    virtual ccBBox getMyOwnBB();

    virtual QIcon getIcon() const
    {
        return QIcon(QString::fromUtf8(":/toolbar/icons/calibrationDB.png"));
    }

    spc::CalibrationDataDB::Ptr getAsSpc() const
    {
        return m_calibration_db_;
    }



    //inherited from ccSerializableObject
    virtual bool isSerializable() const
    {
        return false;
    }
    virtual bool toFile(QFile& out) const {}
    virtual bool fromFile(QFile& in, short dataVersion, int flags) {}

    static std::vector<ccPointCloud * > getAsPointClouds( const spc::CalibrationDataDB &db)
    {
        size_t n_clouds = db.getNumberOfDifferentClouds();
        std::vector<ccPointCloud * > out(n_clouds);
        BOOST_FOREACH(ccPointCloud * &cloud, out)
        {
            cloud = new ccPointCloud(); //we need them instantiated

            ccScalarField * distance = new ccScalarField();
            distance->setName("distance");

            ccScalarField * angle = new ccScalarField();
            angle->setName("angle");

            ccScalarField * intensity = new ccScalarField();
            intensity->setName("intensity");

            cloud->addScalarField(distance);
            cloud->addScalarField(angle);
            cloud->addScalarField(intensity);
        }



        BOOST_FOREACH(spc::CorePointData::Ptr core, db.getDataDB())
        {

            Eigen::Vector3f center = core->value<Eigen::Vector3f>("centroid");
            CCVector3 p (center(0), center(1), center(2));

            ccPointCloud * cloud = out.at(core->value<size_t>("cloud_id"));

            float distance, angle, intensity;
            distance = core->value<float>("distance");
            angle = core->value<float>("angle");
            intensity = core->value<float>("intensity");

            std::string name =core->value<std::string>("cloud_name");

            cloud->setName(name.c_str());


            cloud->reserve(cloud->size() + 1);

            cloud->getScalarField(cloud->getScalarFieldIndexByName("distance"))->addElement(distance);
            cloud->getScalarField(cloud->getScalarFieldIndexByName("angle"))->addElement(angle);
            cloud->getScalarField(cloud->getScalarFieldIndexByName("intensity"))->addElement(intensity);

            cloud->getScalarField(cloud->getScalarFieldIndexByName("distance"))->computeMinAndMax();
            cloud->getScalarField(cloud->getScalarFieldIndexByName("angle"))->computeMinAndMax();
            cloud->getScalarField(cloud->getScalarFieldIndexByName("intensity"))->computeMinAndMax();

            cloud->addPoint(p);

        }

        return out;
    }


    void rebuildClouds();
protected:

    //    void setAttitudeAsMetadata();

    virtual void drawMeOnly(CC_DRAW_CONTEXT &context);
    virtual void applyGLTransformation(const ccGLMatrix& trans);
    virtual void setGLTransformation(const ccGLMatrix& trans);


    //    void initParameters();
    void initMetadata();


    spc::CalibrationDataDB::Ptr m_calibration_db_;


    ccBBox box;



};//end class

#endif // CC_CALIBRATION_DB_H
