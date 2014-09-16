#ifndef CC_CALIBRATION_DB_H
#define CC_CALIBRATION_DB_H

#include <ccoutofcore/ccMyBaseObject.h>

#include <helpers/ccSPCObjectsStreamer.h>
//#include <spc/elements/SamplesDB.h>
#include <ccPointCloud.h>

#include <QIcon>

#include <ccBox.h>

#include <ccPointCloud.h>
#include <spc/elements/EigenTable.h>


class ccEigenTable : public ccMyBaseObject

{
public:
    ccEigenTable();

    ccEigenTable(spc::EigenTable::Ptr db)
    {
        m_calibration_db_ = db;
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

    spc::ElementBase::Ptr getAsSpc() const
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
        return "ccEigenTable";
    }

protected:


    spc::EigenTable::Ptr m_calibration_db_;
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
        m_calibration_db_ = spcStaticPointerCast<spc::EigenTable>(ptr);

        return true;
    }

    virtual spc::ElementBase::Ptr getSPCElement() const
    {
        return m_calibration_db_;
    }


}; // end class

#endif // CC_CALIBRATION_DB_H