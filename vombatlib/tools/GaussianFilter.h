#ifndef VOMBAT_GAUSSIANFILTER_H
#define VOMBAT_GAUSSIANFILTER_H


#include <qPCL/PclUtils/filters/BaseFilter.h>

//#include <BaseFilter.h>
#include <dialogs/GaussianFilterDlg.h>

//#include <spc/scalar_fields_generators/single_attitude_model.h>
//
//#include <ccoutofcore/ccSingleAttitudeModel.h>


class GaussianFilter : public BaseFilter
{
public:
    GaussianFilter(ccPluginInterface * parent_plugin = 0);


    virtual int compute() ;

protected:
    virtual int checkSelected();

    int openInputDialog();

private:
    GaussianFilterDlg * m_dialog_;


};



#endif // VOMBAT_GAUSSIANFILTER_H
