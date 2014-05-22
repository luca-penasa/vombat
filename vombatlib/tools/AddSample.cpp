#include "AddSample.h"

AddSample::AddSample(ccPluginInterface * parent_plugin): BaseFilter(FilterDescription(   "Add a Sample Object",
                                                       "Add a Sample Object",
                                                       "Add a Sample Object",
                                                       ":/toolbar/icons/sample.png"), parent_plugin)
{
    this->setShowProgressBar(false);
}
