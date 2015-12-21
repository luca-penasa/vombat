
#include <ccPointCloud.h>
#include <ccScalarField.h>
#include <tools/ApplyCorrection.h>
#include <vombat.h>
#include <PlotterDlg.h>

//#include <spc/io/AsciiEigenTableWriter.h>

#include <boost/filesystem.hpp>

#include <dialogs/ccapplycorrection.h>

#include <boost/foreach.hpp>
#include <ccScalarField.h>

#include <spc/methods/InterpolatorSpline.h>

ApplyCorrection::ApplyCorrection(ccPluginInterface* parent_plugin)
	: BaseFilter(FilterDescription("Apply intensity calibration model ",
					 "Apply intensity calibration model",
					 "Apply intensity calibration model",
					 ":/toolbar/icons/apply_correction.png"),
		  parent_plugin)
{
    this->setShowProgressBar(false);
}

int ApplyCorrection::compute()
{

	if ((!ts_) | (!field_) | (!cloud_)) // we need all three!
		return -1;

	LOG(INFO) << "Found everything!";

	ccScalarField* outf(new ccScalarField);
	outf->resize(field_->currentSize());
	outf->setName("Interpolated");

	spc::TimeSeriesBase::Ptr spc_ts_ptr = ts_->getTimeSeries();

	spc::InterpolatorSimpleSpline interpolator;
	interpolator.setInputSeries(spc_ts_ptr);
	//	interpolator().updateInternals();

	for (size_t i = 0; i < field_->currentSize(); ++i) {
		outf->setValue(i, interpolator.getInterpolatedValue(field_->getValue(i)));
	}

	cloud_->addScalarField(outf);
	outf->computeMinAndMax();
	entityHasChanged(cloud_);

    return 1;
}

int ApplyCorrection::openInputDialog()
{
	// any time series can be used!
	ccHObject::Container cont = vombat::theInstance()->getAllObjectsInTreeBySPCDti(&spc::TimeSeriesBase::Type);

	ccApplyCorrection* dialog = new ccApplyCorrection();

	for (auto obj : cont) {
		dialog->getModelCombo()->addItem(obj->getName());
    }

	cloud_ = this->getSelectedEntityAsCCPointCloud();
	size_t n_fields = cloud_->getNumberOfScalarFields();

	for (size_t i = 0; i < n_fields; ++i) {
		std::string fname = cloud_->getScalarFieldName(i);
		dialog->getFieldCombo()->addItem(fname.c_str());
	}

    dialog->exec();

	int id = dialog->getModelCombo()->currentIndex();
	if (id >= 0) // was not set
		ts_ = static_cast<ccTimeSeries*>(cont.at(id));

	int field_id = dialog->getFieldCombo()->currentIndex();
	if (field_id >= 0)
		field_ = static_cast<ccScalarField*>(cloud_->getScalarField(field_id));

	LOG(INFO) << "Finished without errors!";

    return 1;
}
int ApplyCorrection::checkSelected()
{

	if (this->getSelectedEntityAsCCPointCloud() != nullptr)
		return 1;
	else
		return 0;
}
