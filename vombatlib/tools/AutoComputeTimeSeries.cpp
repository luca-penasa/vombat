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

    std::string  field = m_dialog->comboScalarFields->currentText().toStdString();

    LOG(INFO) << "trying to use field " << field;


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
                    spc::StratigraphicModelSingleAttitude::Ptr spcmod = mod->getModel();


                    if (spcsel->contains(spcmod->getAttitude().getPosition()))
                    {
                        LOG(INFO) << " found pertinent selection";
                        model = spcmod;
                    }
                    else
                        continue;

                }


               ////////////////////////

                        spc::PointCloudBase::Ptr asspc =  spcCCPointCloud::fromccPointCloud(cloud);

                        spc::SelectionExtractor<Eigen::Vector3f, int> ext;
                        ext.setInputSet(asspc);
                        ext.setSelection(spcse;);
                        ext.compute();

                        LOG(INFO) << "selection of the cloud extracted";

                        spc::DynamicScalarFieldEvaluator eval;
                        eval.setInputCloud(asspc);
                        eval.setIndices(ext.getInsideIds());
                        Eigen::VectorXf positions = eval.getOutput();


                        ////////////////////// now get out the scalar field
                        ///
                        Eigen::VectorXf yfield;
                        yfield.resize(positions.rows()); // same size of te other



                        if ((field ==  "R Color") ||
                                (field ==   "G Color") ||
                                (field ==   "B Color"))
                        {


                            if (!cloud->hasColors())
                            {
                                LOG(INFO) << "a rgb field was requested but the cloud has none";
                                continue;
                            }

                            size_t pos;
                            if (field == "R Color")
                                 pos = 0;
                            else if (field == "G Color")
                                pos = 1;
                            else if (field == "B Color")
                                pos = 2;




                            int counter = 0;
                            for (int id : ext.getInsideIds())
                            {
                                yfield(counter ++) = (float) cloud->getPointColor(id)[pos];
                            }


                        }

                        else // is a standard scalar field
                        {
                            CCLib::ScalarField * f = cloud->getScalarField(cloud->getScalarFieldIndexByName(field));

                            if (!f)

                            {
                                LOG(INFO) << "cannot find requested field in the cloud";
                                continue;
                            }

                            int counter = 0;
                            for (int id : ext.getInsideIds())
                            {
                                yfield(counter ++) = f->getValue(id);
                            }
                        }




                        ///// DONE!
                        ///
                        /// Compute the time series


                                KernelSmoothing<float> ks(positions, y_field_);
                                ks.setKernelSigma(bandwidth_);




            }


        }
        ccPointCloud * cloud = ccHObjectCaster::ToPointCloud(c);

        if (cloud)
        {
            LOG(INFO)
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
