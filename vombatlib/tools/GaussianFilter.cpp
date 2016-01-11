#include "GaussianFilter.h"


#include <qPCL/PclUtils/utils/cc2sm.h>

#include <spc/elements/point_types.h>

#include <spc/methods/ScalarFieldGaussianConvolver.h>

#include <ccScalarField.h>
#include <ccPointCloud.h>
#include <dialogs/GaussianFilterDlg.h>

#ifdef SPC_WITH_PCL
GaussianFilter::GaussianFilter(ccPluginInterface* parent_plugin)
    : BaseFilter(FilterDescription("Apply Gaussian filter to scalar field ",
                     "Apply Gaussian filter to scalar field",
                     "Apply Gaussian filter to scalar field",
                     ":/toolbar/icons/gaussian.png"),
          parent_plugin)
{
    this->setShowProgressBar(true);
}

int GaussianFilter::compute()
{

    ccPointCloud* cc_cloud = getSelectedEntityAsCCPointCloud();

    if (!cc_cloud)
        return -1;

    ccScalarField* selected_field = cc_cloud->getCurrentDisplayedScalarField();

    // construct the right pcl::pointcloud
    pcl::PointCloud<pcl::PointXYZI>::Ptr input = pcl::PointCloud<pcl::PointXYZI>::Ptr(new pcl::PointCloud<pcl::PointXYZI>);

    input->resize(cc_cloud->size());

    for (int i = 0; i < cc_cloud->size(); ++i) {
        CCVector3 point;
        cc_cloud->getPoint(i, point);

        input->at(i).x = point[0];
        input->at(i).y = point[1];
        input->at(i).z = point[2];
        input->at(i).intensity = selected_field->getValue(i);
    }

    spc::GaussianConvolver<pcl::PointXYZI> filt;
    filt.setInputCloud(input);
    filt.setFieldName("intensity");
    filt.setKernelSigma(m_dialog_->getSigma());
    filt.setDownsapleWidth(m_dialog_->getLeafSize());
    filt.applyFilter();

    std::vector<float> filtered_field = filt.getOutput();

    ccScalarField* f = new ccScalarField;

    f->resize(filtered_field.size());
    for (int i = 0; i < filtered_field.size(); ++i) {
        if (i <= 10)
            std::cout << filtered_field.at(i) << std::endl;

        f->setValue(i, filtered_field.at(i));
    }

    f->computeMinAndMax();

    f->setName("smoothed");

    int id = cc_cloud->addScalarField(f);

    cc_cloud->setCurrentDisplayedScalarField(id);

    emit entityHasChanged(cc_cloud);

    return 1;
}

int GaussianFilter::openInputDialog()
{
    if (!m_dialog_)
        m_dialog_ = new GaussianFilterDlg(0);

    return m_dialog_->exec() ? 1 : 0;
}
int GaussianFilter::checkSelected()
{
    ccPointCloud* cc_cloud = getSelectedEntityAsCCPointCloud();
    if (!cc_cloud)
        return -1;

    return 1;
}
#endif
