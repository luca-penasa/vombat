#ifndef GAUSSIANFILTER_H
#define GAUSSIANFILTER_H




#include <BaseFilter.h>
#include <dialogs/GaussianFilterDlg.h>

#include <spc/stratigraphy/single_attitude_model.h>

#include <ccoutofcore/ccSingleAttitudeModel.h>


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



#endif // GAUSSIANFILTER_H
