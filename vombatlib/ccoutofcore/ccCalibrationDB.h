#ifndef CC_CALIBRATION_DB_H
#define CC_CALIBRATION_DB_H


#include <ccoutofcore/ccMyBaseObject.h>


#include <spc/calibration/CalibrationDataDB.h>


#include <QIcon>




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
    }

    //inherited methods (ccHObject)
    virtual bool hasColors() const { return true; }
    virtual ccBBox getMyOwnBB();

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




protected:

    //    void setAttitudeAsMetadata();

    virtual void drawMeOnly(CC_DRAW_CONTEXT &context);
    virtual void applyGLTransformation(const ccGLMatrix& trans);
    virtual void setGLTransformation(const ccGLMatrix& trans);


//    void initParameters();
    void initMetadata();


  spc::CalibrationDataDB::Ptr m_calibration_db_;






};//end class

#endif // CC_CALIBRATION_DB_H
