#include "AutoComputeTimeSeries.h"
#include <spc/methods/TimeSeriesAutoExtractor.h>
#include <LoadSPCElement.h>
#include <ccSample.h>
#include <ccPointCloud.h>
#include <ccHObjectCaster.h>
#include <ScalarField.h>
#include <helpers/spcCCPointCloud.h>
#include <vombat.h>

#include <ccPlanarSelection.h>
#include <dialogs/ComputeTimeSeriesDlg.h>
#include <ccTimeSeries.h>

#include <QMainWindow>
#include <ccSingleAttitudeModel.h>
AutoComputeTimeSeries::AutoComputeTimeSeries(ccPluginInterface* parent_plugin)
    : BaseFilter(FilterDescription("Automatically compute time series for selections defined in childrens",
                                   "Automatically compute time series for selections defined in childrens",
                                   "Automatically compute time series for selections defined in childrens",
                                   ":/toolbar/icons/time_series_multi.png"),
                 parent_plugin)
{
    this->setShowProgressBar(false);
}

int AutoComputeTimeSeries::compute()
{
    LOG(INFO) << "starting to compute() autoComputeTimeSeries";


    ccHObject::Container clouds, selections, models ;
    m_dialog->comboClouds->getSelectedObject()->filterChildren(clouds,false, CC_TYPES::POINT_CLOUD,true);

    m_dialog->comboModels->getSelectedObject()->filterChildren(models);

    m_dialog->comboRegions->getSelectedObject()->filterChildren(selections);




    for (ccHObject * s: selections)
    {

        ccPlanarSelection * sel = dynamic_cast<ccPlanarSelection *> (s);

        if (sel)
        {
            LOG(INFO) << "working on sel  " << sel->getName().toStdString();


            spc::SelectionRubberband::Ptr spcsel = sel->getSPCElement<spc::SelectionRubberband>();

            // now we need to find a goog model for this selection


            for (ccHObject * m: models)
            {
                ccSingleAttitudeModel * mod =  dynamic_cast<ccSingleAttitudeModel * > (m);


                spc::StratigraphicModelSingleAttitude::Ptr model;

                if (mod) // go ahead an thest it
                {
                    LOG(INFO) << "Testing model for this selection;";

                    spc::StratigraphicModelSingleAttitude::Ptr spcmod = mod->getModel();


                    LOG(INFO) << "position " << spcmod->getAttitude().getPosition();

                    if (spcsel->contains(spcmod->getAttitude().getPosition()))
                    {
                        LOG(INFO) << " found pertinent selection";
                        model = spcmod;
                    }
                    else
                    {
                        LOG(INFO) << " Not pertinent";

                        continue;
                    }

                }

                for (ccHObject * o :clouds)
                {

                    ccPointCloud * cloud = ccHObjectCaster::ToPointCloud(o);

                    spcCCPointCloud::Ptr cloud_spc =  spcCCPointCloud::fromccPointCloud(cloud);

                    if(!cloud)
                        continue;

                    spc::TimeSeriesGenerator generator;

                    generator.setInputCloud(cloud_spc);
                    generator.setBandwidth(m_dialog->spinBandwidth->value());
                    generator.setSamplingStep(m_dialog->spinResolution->value());
                    generator.setSelection(spcsel);
                    generator.setStratigraphicModel(model);

                    generator.setMinNumberOfPoints(m_dialog->spinMinNbPoints->value());

                    FieldDescriptor descriptor = m_dialog->comboScalarFields->itemData(m_dialog->comboScalarFields->currentIndex()).value<FieldDescriptor>();

                    if (!descriptor.iscolor_) // just a regular field
                        generator.setYFieldName(descriptor.name_);
                    else // is a color field
                    {
                        generator.setYFieldUseColor(descriptor.color_channel);
                    }


                    generator.setDoAutoCalibration(false);
                    generator.compute();
                    spc::TimeSeriesEquallySpaced::Ptr ts = generator.getOutputSeries();

                    if (ts)
                    {
                        ccTimeSeries * ccts  = new ccTimeSeries(ts);

                        newEntity(ccts);
                    }
                }
            }


        }

    }


    LOG(INFO) << "done";

    return 1;
}

int AutoComputeTimeSeries::checkSelected()
{
    return 1;
}

int AutoComputeTimeSeries::openInputDialog()
{

    if (!m_dialog)
        m_dialog =  new ComputeTimeSeriesDlg(vombat::theInstance()->getMainWindow());

    return m_dialog->exec() ? 1 : 0;
    return 1;
}
