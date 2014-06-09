#ifndef CC_CALIBRATION_DB_H
#define CC_CALIBRATION_DB_H

#include <ccoutofcore/ccMyBaseObject.h>

#include <helpers/ccSPCObjectsStreamer.h>
#include <spc/elements/SamplesDB.h>
#include <ccPointCloud.h>

#include <QIcon>

#include <ccBox.h>

#include <ccPointCloud.h>

///
/// \brief The ccAttitude class gives a qCC-valid representation of a geological
/// attitude
///
class ccCalibrationDB : public ccMyBaseObject

{
public:
    ccCalibrationDB();

    ccCalibrationDB(spc::SamplesDB db)
    {
        m_calibration_db_ = spcMakeSharedPtrMacro<spc::SamplesDB>(db);
        writeSPCClassNameToMetadata();
    }

    virtual bool hasColors() const
    {
        return false;
    }

    virtual QIcon getIcon() const
    {
        return QIcon(QString::fromUtf8(":/toolbar/icons/calibrationDB.png"));
    }

    spc::SamplesDB::Ptr getAsSpc() const
    {
        return m_calibration_db_;
    }

    // inherited from ccSerializableObject
    virtual bool isSerializable() const
    {
        return true;
    }


//    void exposeSamples();

    virtual QString getSPCClassName() const
    {
        return "ccCalibrationDB";
    }

protected:


    spc::SamplesDB::Ptr m_calibration_db_;
    // ccHObject interface
protected:
    virtual bool toFile_MeOnly(QFile &out) const
    {
        ccCustomHObject::toFile_MeOnly(out);
        ccSPCObjectsStreamer::WriteToQFile(m_calibration_db_, out);
        return true;
    }
    virtual bool fromFile_MeOnly(QFile &in, short dataVersion, int flags)
    {
        ccCustomHObject::fromFile_MeOnly(in, dataVersion, flags);

        spc::ISerializable::Ptr ptr = ccSPCObjectsStreamer::ReadFromQFile(in);
        m_calibration_db_ = spcStaticPointerCast<spc::SamplesDB>(ptr);

        return true;
    }

    virtual spc::ElementBase::Ptr getSPCElement() const
    {
        return m_calibration_db_;
    }

public:
    virtual ccBBox getMyOwnBB()
    {
        Eigen::Vector3f min(std::numeric_limits<float>::max(),
                            std::numeric_limits<float>::max(),
                            std::numeric_limits<float>::max());

        Eigen::Vector3f max(std::numeric_limits<float>::min(),
                            std::numeric_limits<float>::min(),
                            std::numeric_limits<float>::min());

        for (spc::Sample::Ptr sample : this->m_calibration_db_->getSamplesDB()) {

            Eigen::Vector3f pos = sample->getPosition();

            for (int i = 0 ; i < 3; ++i)
            {
                if (pos(i) < min(i))
                    min(i) = pos(i);

                if (pos(i) > max(i))
                    max(i) = pos(i);
            }

        }

        ccBBox box  = ccBBox(CCVector3(min.data()), CCVector3(max.data()));
        return box;
    }

    // ccDrawableObject interface
}; // end class

#endif // CC_CALIBRATION_DB_H
