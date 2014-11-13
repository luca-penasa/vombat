#include "LoadCloudDataSource.h"

LoadCloudDataSource::LoadCloudDataSource(ccPluginInterface * parent_plugin): BaseFilter(FilterDescription(   "Load the point cloud from a data source",
                                                       "Load the point cloud from a data source",
                                                       "Load the point cloud from a data source",
                                                       ":/toolbar/icons/cloud_data_source_on_disk_load.png"), parent_plugin)
{
    this->setShowProgressBar(false);
}
