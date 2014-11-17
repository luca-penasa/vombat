#include "AutoComputeTimeSeries.h"
#include <spc/methods/TimeSeriesAutoExtractor.h>
#include <LoadSPCElement.h>

AutoComputeTimeSeries::AutoComputeTimeSeries(ccPluginInterface * parent_plugin): BaseFilter(FilterDescription(   "Automatically compute time series for selections defined in childrens",
                                                       "Automatically compute time series for selections defined in childrens",
                                                       "Automatically compute time series for selections defined in childrens",
                                                       ":/toolbar/icons/time_series_multi.png"), parent_plugin)
{
    this->setShowProgressBar(false);
}


int AutoComputeTimeSeries::compute()
{

    ccHObject * root =  vombat::theInstance()->getSelected().at(0);
    ccSPCElementShell * el = dynamic_cast<ccSPCElementShell *> (root);


    spc::ElementBase::Ptr r = el->getSPCElement();

    spc::TimeSeriesAutoExtractor extractor;

    extractor.setRoot(r);
    extractor.compute();



    LoadSPCElement::rebuildMyChildsRecursive(vombat::theInstance()->getObjectFromElement(r));

    entityHasChanged(vombat::theInstance()->getObjectFromElement(r));

    return 1;
}
