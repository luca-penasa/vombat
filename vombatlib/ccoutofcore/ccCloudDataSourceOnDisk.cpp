#include "ccCloudDataSourceOnDisk.h"
#include <iostream>

#include <helpers/ccSPCObjectsStreamer.h>
#include <ccGenericGLDisplay.h>

#include <spc/elements/CloudDataSourceOnDisk.h>
#include <QIcon>

ccCloudDataSourceOnDisk::ccCloudDataSourceOnDisk(spc::CloudDataSourceOnDiskPtr source)
    : ccSPCElementShell(source)
{

    source_ = source;
}

QIcon ccCloudDataSourceOnDisk::getIcon() const
{
    return QIcon(QString::fromUtf8(":/toolbar/icons/cloud_data_source_on_disk.png"));
}
