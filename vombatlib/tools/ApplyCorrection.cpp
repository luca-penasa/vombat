

#include <tools/ApplyCorrection.h>
#include <vombat.h>
#include <PlotterDlg.h>

#include <spc/io/time_series_writer.h>

#include <boost/filesystem.hpp>
#include <cccalibrationmodel.h>

#include <dialogs/ccapplycorrection.h>

#include <boost/foreach.hpp>


ApplyCorrection::ApplyCorrection(ccPluginInterface *parent_plugin) : BaseFilter(FilterDescription(   "Apply intensity calibration model ",
                                                                                                 "Apply intensity calibration model",
                                                                                                 "Apply intensity calibration model",
                                                                                                 ":/toolbar/icons/apply_correction.png" ), parent_plugin)
{
    this->setShowProgressBar(false);

}

int
ApplyCorrection::compute()
{


    if (!model_)
    {
        return -1;
    }


    ccPointCloud * cloud = getSelectedEntityAsCCPointCloud();



    if (!cloud)
        return -1;


    ccCalibrationModel * mod = dynamic_cast<ccCalibrationModel *> (model_);

    if (!mod)
        return -1;

    spc::CalibrationModelBase::Ptr mod_spc = mod->getModel();


    CCLib::ScalarField * dis = cloud->getScalarField(cloud->getScalarFieldIndexByName("distance"));


    if ((!dis))
        return -1;


    ccScalarField * newfield = new ccScalarField;
    newfield->resize(cloud->size());
    newfield->setName("correction intensity");

    std::vector<float> x, y;




    for (int i = 0 ; i < cloud->size(); ++i)
    {

       newfield->setValue(i, mod_spc->getDistanceCorrection(dis->getValue(i)) );
       y.push_back(newfield->getValue(i));
       x.push_back(dis->getValue(i));
    }


    newfield->computeMinAndMax();

    spc::SparseTimeSeries<float>::Ptr ecco (new spc::SparseTimeSeries<float>(x, y));
    ccTimeSeries * its_ts = new ccTimeSeries(ecco);

    its_ts->setName("Correction TS");
    cloud->addScalarField(newfield);


    newEntity(its_ts);
    entityHasChanged(cloud);


    return 1;
}

int ApplyCorrection::openInputDialog()
{
    model_ = 0;

    ccHObject::Container cont;
    getAllEntitiesThatHaveMetaData("[vombat][ccCalibrationModel]", cont);


    ccApplyCorrection * dialog  = new ccApplyCorrection();

    QComboBox * combo = dialog->getModelCombo();
    combo->clear();

//    dialog->layout()->addWidget(box);

    BOOST_FOREACH(auto obj, cont)
    {
        combo->addItem(obj->getName());
    }

    dialog->exec();

    int id = combo->currentIndex();


    model_ = cont.at(id);

    if (!model_)
    {
        return -1;
    }


    return 1;
}
int ApplyCorrection::checkSelected()
{


    return 1;
}

