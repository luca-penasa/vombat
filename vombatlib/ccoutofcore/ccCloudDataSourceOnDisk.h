#pragma once
#ifndef CC_EXAMPLE_OBJECT_H
#define CC_EXAMPLE_OBJECT_H

#include <ccoutofcore/ccSPCElementShell.h>

namespace spc {
spcFwdDeclSharedPtr(CloudDataSourceOnDisk)
}
///
/// \brief The ccAttitude class gives a qCC-valid representation of a geological attitude
///
class ccCloudDataSourceOnDisk : public ccSPCElementShell {
public:
    ccCloudDataSourceOnDisk(spc::CloudDataSourceOnDiskPtr source);

    ~ccCloudDataSourceOnDisk()
    {
    }

    virtual QIcon getIcon() const;

    //inherited from ccSerializableObject
    virtual bool isSerializable() const
    {
        return true;
    }

public:
protected:
    virtual bool toFile_MeOnly(QFile& out) const
    {

        return true;
    }
    virtual bool fromFile_MeOnly(QFile& in, short dataVersion, int flags)
    {

        return true;
    }

    virtual void drawMeOnly(CC_DRAW_CONTEXT& context)
    {
    }

protected:
    spc::CloudDataSourceOnDiskPtr source_;

}; //end class

#endif // CCPLANEORIENTATION_H
