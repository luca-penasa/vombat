#include "SetUpNewSeries.h"

#include <dialogs/ccTimeSeriesGeneratorEditorDlg.h>

//#include <ccoutofcore/ccMyCCHObject.h>
//#include <ccoutofcore/ccAdditionalCaster.h>

//#include <spc/geology/stratigraphic_model_base.h>
#include <ccoutofcore/ccSingleAttitudeModel.h>

#include <ccHObjectCaster.h>
#include <spcCCPointCloud.h>

#include <iostream>
#include <qPCL/PclUtils/utils/cc2sm.h>

#include <spc/elements/generic_cloud.h>

#include <spc/methods/time_series_generator.h>

#include <ccoutofcore/ccTimeSeriesGenerator.h>
#include <ccoutofcore/ccTimeSeries.h>
#include <vombat.h>

#include <visualization/PlotterWidget.h>
#include <visualization/PlotterDlg.h>
#include <OpenPlotsDialog.h>

#include <ccoutofcore/ccPlanarSelection.h>

#include <spc/io/time_series_writer.h>

SetUpNewSeries::SetUpNewSeries(ccPluginInterface * parent_plugin): BaseFilter(FilterDescription(   "Add a new time series generator",
                                                                                                   "Add a new time series generator",
                                                                                                   "Add a new time series generator",
                                                                                                   ":/toolbar/icons/tseries_generator.png")
                                                                              , parent_plugin), m_dialog(0)

{
    this->setShowProgressBar(false);

    PlotterWidget * plotter = vombat::theInstance()->getPlotterDlg()->getPlotterWidget();
    //    connect(this, SIGNAL(newSeries(ccTimeSeries)), plotter, SLOT(handleNewTimeSeries(ccTimeSeries)));

}

int SetUpNewSeries::compute()
{
    //    ccTimeSeriesGenerator * generator =  new ccTimeSeriesGenerator();

    //    newEntity(generator);

    return 1;
}


int SetUpNewSeries::checkSelected()
{
    //always active!
    return 1;
}

int SetUpNewSeries::openInputDialog()
{
    if (!m_dialog)
        m_dialog = new ComputeTimeSeriesDlg(0);

    m_dialog->initWithTree();

    return m_dialog->exec() ? 1 : 0;
}

int SetUpNewSeries::openOutputDialog()
{

    //get the objects from the combo
    ccHObject * mod_obj = m_dialog->getSelectedModel();
    ccHObject * cloud_obj = m_dialog->getSelectedCloud();
    ccHObject * sel_obj = m_dialog->getSelectedArea();


    ccPointCloud * cloud = static_cast<ccPointCloud *> (cloud_obj);
    ccSingleAttitudeModel * model  = static_cast<ccSingleAttitudeModel *> (mod_obj);

    if (!model || !cloud)
    {
        ccLog::Warning("Some error occured retrieving model and cloud");
        return -1;
    }

    //we wrap i in a nice container for SPC
    spcCCPointCloud::Ptr mycloud ( new spcCCPointCloud(cloud));

    //set up a ts generator
    spc::TimeSeriesGenerator generator;

    // extract a smaller area if necessary
    std::vector<int> indices;
    if (sel_obj)
    {
        ccPlanarSelection * selection = static_cast<ccPlanarSelection *> (sel_obj);
        selection->setInputCloud(mycloud);
        selection->updateIndices();
        indices = selection->getIndices();
        generator.setIndices(indices);
    }

    generator.setInputCloud(mycloud);
    generator.setStratigraphicModel(model->getModel());
    generator.setLogFieldName(m_dialog->getSelectedScalarFieldName());
    generator.setSamplingStep(m_dialog->getStep());
    generator.setBandwidth(m_dialog->getBandwidth());

    int status = generator.compute();

    if (status <= 0)
    {
        ccLog::Error("Some error computing the time series");
        return -1;
    }



    spc::EquallySpacedTimeSeries<float>::Ptr ts = generator.getOutputSeries();


    spc::TimeSeriesWriter<float> w;
    w.setInputSeries(ts);
    w.setFilename("/home/luca/series.txt");
    w.writeAsciiAsSparse();

    std::cout << ts->getMinX() << " " << ts->getMaxX() << std::endl;

    ccTimeSeries * series = new ccTimeSeries(ts);


    vombat::theInstance()->getPlotterDlg()->getPlotterWidget()->handleNewTimeSeries(series);
    emit newEntity(series);



    return 1;
}
