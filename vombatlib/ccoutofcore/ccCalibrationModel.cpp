#include "ccCalibrationModel.h"

//#include <spc/experimental/ICalPHFunction.h>

//#include <boost/serialization/shared_ptr.hpp>

#include <spc/io/element_io.h>

#include <QIcon>

#include <spc/elements/Attitude.h>

//#include "DistanceComputationTools.h"
#include "ccPointCloud.h"

QIcon ccCalibrationModel::getIcon() const
{
    return QIcon(QString::fromUtf8(":/toolbar/icons/ca.png"));
}

#include "ccNormalVectors.h"
