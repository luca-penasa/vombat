#include "ComputeSmoothedTimeSeriesXY.h"
#include <spcCCPointCloud.h>
#include <spc/methods/kernelsmoothing2.h>
#include <spc/time_series/sparse_time_series.h>
#include <ccTimeSeries.h>

ComputeSmoothedTimeSeriesXY::ComputeSmoothedTimeSeriesXY(ccPluginInterface * parent_plugin) : BaseFilter(FilterDescription(   "Compute XY time series, as a running gaussian-weighted moving average",
                                                                                                                              "Compute XY time series, as a running gaussian-weighted moving average",
                                                                                                                              "Compute XY time series, as a running gaussian-weighted moving average",
                                                                                                                              ":/toolbar/icons/XvsY.png") , parent_plugin), m_dialog(NULL)
{
    this->setShowProgressBar(false);
}



int ComputeSmoothedTimeSeriesXY::compute()
{

    float bandwidth = m_dialog->getBandwidth();
    float s_step = m_dialog->getSamplingStep();

    std::string x_name = m_dialog->getXField();
    std::string y_name = m_dialog->getYField();

    ccPointCloud * cloud = getSelectedEntityAsCCPointCloud();

    spcCCPointCloud::Ptr spc_cloud (new spcCCPointCloud (cloud));

    std::vector<float> f1 = spc_cloud->getField(x_name);
    std::vector<float> f2 = spc_cloud->getField(y_name);

    spc::SparseTimeSeries<float>::Ptr ser_in (new spc::SparseTimeSeries<float> (f1, f2));

    spc::KernelSmoothing2<float> ks;
    ks.setInputSeries(ser_in);
    ks.setBandwidth(bandwidth);
    ks.setStep(s_step);

    ks.compute();

    spc::EquallySpacedTimeSeries<float>::Ptr out = ks.getOutputSeries();

    ccTimeSeries * out_ts = new ccTimeSeries(out);

    out_ts->setName("XY smoothed Time Series");

    newEntity(out_ts);



    return 1;
}




int ComputeSmoothedTimeSeriesXY::checkSelected()
{
    return isFirstSelectedCcPointCloud();
}


int ComputeSmoothedTimeSeriesXY::openInputDialog()
{

    m_dialog = new ccComputeSmoothedTimeSeriesXYDlg(0);


    ccPointCloud * cloud = getSelectedEntityAsCCPointCloud();

    m_dialog->getUI()->comboX->addItemsFromFieldsCloud(cloud);
    m_dialog->getUI()->comboY->addItemsFromFieldsCloud(cloud);



    /// we need to init the dialog

    return m_dialog->exec() ? 1 : 0;

}
