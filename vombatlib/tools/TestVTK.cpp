#include "TestVTK.h"
#include <ccSample.h>
#include <ccPointCloud.h>
#include <ccHObjectCaster.h>
#include <ScalarField.h>
#include <spc/core/logging.h>

TestVTK::TestVTK(ccPluginInterface* parent_plugin)
    : BaseFilter(FilterDescription("Use Scene to render a test vtk object",
                     "Add a Sample Object",
                     "Add a Sample Object",
                     ":/toolbar/icons/sample.png"),
          parent_plugin)
{
    this->setShowProgressBar(false);
}

int TestVTK::compute()
{



    return 1;
}

int TestVTK::checkSelected()
{

        return 1;

}
