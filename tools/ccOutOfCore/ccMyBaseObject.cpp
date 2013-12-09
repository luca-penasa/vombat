#include "ccMyBaseObject.h"

ccMyBaseObject::ccMyBaseObject()
{
    QVariant var(QString("VOMBAT plugin object"));
    setMetaData(QString("[vombat]"), var);
}


Q_DECLARE_METATYPE(ccPointCloud)
