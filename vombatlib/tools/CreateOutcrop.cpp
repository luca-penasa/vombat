#include "CreateOutcrop.h"

CreateOutcrop::CreateOutcrop(ccPluginInterface * parent_plugin):
    BaseFilter(FilterDescription(   "Create an outcrop unit",
                                                       "Create an outcrop unit",
                                                       "Create an outcrop unit",
                                                       ":/toolbar/icons/outcrop.png"), parent_plugin)
{
    this->setShowProgressBar(false);
}
