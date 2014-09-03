#include "LoadSPCElement.h"


LoadSPCElement::LoadSPCElement(ccPluginInterface * parent_plugin): BaseFilter(FilterDescription(   "Load SPC elemnts",
                                                                                                   "Load SPC elemnts",
                                                                                                   "Load SPC elemnts",
                                                                                                   ":/toolbar/icons/load.png")
                                                                              , parent_plugin)
{

    setShowProgressBar(false);

}


