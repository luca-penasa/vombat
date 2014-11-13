#include "CreateStratigraphicConstrain.h"

CreateStratigraphicConstrain::CreateStratigraphicConstrain(ccPluginInterface * parent_plugin): BaseFilter(FilterDescription(   "Create a stratigraphic constrain between samples or points",
                                                       "Create a stratigraphic constrain between samples or points",
                                                       "Create a stratigraphic constrain between samples or points",
                                                       ":/toolbar/icons/stratigraphic_constrain.png"), parent_plugin)
{
    this->setShowProgressBar(false);
}
