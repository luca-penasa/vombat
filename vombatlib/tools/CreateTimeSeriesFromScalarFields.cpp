#include "CreateTimeSeriesFromScalarFields.h"

CreateTimeSeriesFromScalarFields::CreateTimeSeriesFromScalarFields(ccPluginInterface *parent_plugin): BaseFilter(FilterDescription("Plot some data as 2d scatter/line plot",
                                                                                       "Plot some data as 2d scatter/line plot",
                                                                                       "Plot some data as 2d scatter/line plot",
                                                                                       ":/toolbar/icons/plot_dlg.png"), parent_plugin),
    m_dialog(0)
{
}