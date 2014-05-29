#ifndef CC_CALIBRATION_DB_H
#define CC_CALIBRATION_DB_H


#include <ccoutofcore/ccMyBaseObject.h>


#include <spc/elements/IntensityCalibration/DataDB.h>
#include <ccPointCloud.h>

#include <QIcon>

#include <ccBox.h>

#include <ccPointCloud.h>

///
/// \brief The ccAttitude class gives a qCC-valid representation of a geological attitude
///
class ccCalibrationDB:  public ccMyBaseObject

{
public:


    ccCalibrationDB();

    ccCalibrationDB(spc::CalibrationDataDB db)
    {
        m_calibration_db_ = spcMakeSharedPtrMacro<spc::CalibrationDataDB> (db);

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

    static std::vector<ccPointCloud * > getAsPointClouds( const spc::CalibrationDataDB &db);


    void rebuildClouds();

    virtual QString getSPCClassName() const
    {
        return "ccCalibrationDB";
    }
protected:

    //    void setAttitudeAsMetadata();

    virtual void drawMeOnly(CC_DRAW_CONTEXT &context);
    virtual void applyGLTransformation(const ccGLMatrix& trans);
    virtual void setGLTransformation(const ccGLMatrix& trans);






    spc::CalibrationDataDB::Ptr m_calibration_db_;


    ccBBox box;



};//end class

#endif // CC_CALIBRATION_DB_H
