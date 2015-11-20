#ifndef SPLIT_POINT_CLOUD_H
#define SPLIT_POINT_CLOUD_H
#ifdef SPC_WITH_PCL

//#include <BaseFilter.h>
#include <dialogs/split_point_cloud_dlg.h>
#include "BaseFilter.h"
class SplitPointCloud : public BaseFilter
{
    Q_OBJECT
public:
    SplitPointCloud(ccPluginInterface *parent_plugin = 0);

protected:
    virtual int compute();
    virtual int openInputDialog();

    SplitPointCloudDlg *m_dialog;
};

#endif

#endif // SPLIT_POINT_CLOUD_H
