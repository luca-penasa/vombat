#ifndef CREATE_TIME_SERIES_FROM_SCALAR_FIELDS_H
#define CREATE_TIME_SERIES_FROM_SCALAR_FIELDS_H

#include "BaseFilter.h"

#include <helpers/spcCCPointCloud.h>

#include <dialogs/CreateTimeSeriesFromScalarFieldsDlg.h>

#include "ui_CreateTimeSeriesFromScalarFieldsDlg.h"

#include <spc/elements/TimeSeriesBase.h>

#include <ccoutofcore/ccTimeSeries.h>

#include <spc/methods/TimeSeriesGenerator.h>
#include <plotter2d/Plotter2DDlg.h>

#include <spc/core/common.h>
//#include <spc/elements/Fields.h>
#include <spc/elements/PointCloudSpc.h>
#include <spc/elements/EigenTable.h>

class CreateTimeSeriesFromScalarFields : public BaseFilter
{
public:
    CreateTimeSeriesFromScalarFields(ccPluginInterface *parent_plugin = 0);

    ~CreateTimeSeriesFromScalarFields()
    {
        if (m_dialog && m_dialog->parent() == 0)
            delete (m_dialog);
    }

    // BaseFilter interface
public:
    // virtual from BaseFilter
    int compute()
    {

        ccHObject * obj = getSelectedEntityAsCCHObject();

        bool doKS = m_dialog->getUi()->grpKS->isChecked();

        if (!cloud_)
            return -1;

        std::string x_field_name, y_field_name;

        x_field_name = m_dialog->getUi()->cmbX->getSelectedFiedName();
        y_field_name = m_dialog->getUi()->cmbY->getSelectedFiedName();

        std::string name = x_field_name + "_" + y_field_name;

        spc::TimeSeriesBase::Ptr serie;

        if (!doKS) {
            std::vector<float> x = cloud_->getField(x_field_name);
            std::vector<float> y = cloud_->getField(y_field_name);

            // simply build up a scatters TS with the two scalar fields
            serie = spc::TimeSeriesSparse::Ptr(new spc::TimeSeriesSparse(x, y));
        } else // do KS
        {

            float ssx = m_dialog->getUi()->cmbSSX->value();
            float ksx = m_dialog->getUi()->cmbKSX->value();

            name += "_smoothed_" + boost::lexical_cast<std::string> (ssx) + "_"
                    + boost::lexical_cast<std::string>(ksx);

            std::cout << "init generator" << std::endl;
            spc::TimeSeriesGenerator generator;
            std::cout << "done init generator" << std::endl;
            generator.setInputCloud(cloud_);
            generator.setXFieldName(x_field_name);
            generator.setYFieldName(y_field_name);

            generator.setSamplingStep(ssx);
			LOG(INFO) << "Using sampling step: " << ssx;
			LOG(INFO) << "Using bandwidth: " << ksx;
            generator.setBandwidth(ksx);
            std::cout << "starting computing - compute()" << std::endl;

            generator.compute();
            std::cout << "ended computing - compute()" << std::endl;

            serie = generator.getOutputSeries();
            if (!serie)
                return -1;
        }

        ccTimeSeries *ccserie = new ccTimeSeries(serie);

        obj->addChild(ccserie);

        ccserie->setName(name.c_str());

        newEntity(ccserie);
        return 1;
    }

protected:
    ///// virtuals from BaseFilters
    int checkSelected()
    {

        ccHObject *obj = this->getSelectedEntityAsCCHObject();
        if (obj && obj->isA(CC_TYPES::POINT_CLOUD)) {
            return true;
        } else {
            ccSPCElementShell *myobj = dynamic_cast<ccSPCElementShell *>(obj);
            if (!myobj)
                return false;
            else {
                    spc::ElementBase::Ptr el = myobj->getSPCElement();

                    DCHECK(el != NULL);

                if (el->getType()->isA(
                        &spc::EigenTable::Type))
                    return true;
            }
        }


        return false;
    }

    int openInputDialog()
    {
        if (!m_dialog)
            m_dialog = new CreateTimeSeriesFromScalarFieldsDlg(0);



        ccHObject *obj = getSelectedEntityAsCCHObject();
        if (obj && obj->isA(CC_TYPES::POINT_CLOUD))
            cloud_ = spc::PointCloudBase::Ptr(
                new spcCCPointCloud(getSelectedEntityAsCCPointCloud()));

        // maybe is another spc type field-enabled
        ccSPCElementShell *myobj = dynamic_cast<ccSPCElementShell *>(obj);
        if (myobj && myobj->getSPCElement()->getType()->isA(
                         &spc::EigenTable::Type)) {
            spc::EigenTable::Ptr man = spcDynamicPointerCast
                <spc::EigenTable>(myobj->getSPCElement());
            spc::PointCloudSpc::Ptr spcc(new spc::PointCloudSpc);
            spcc->setFieldsManager(man);
            cloud_ = spcc;
        }

        std::vector<std::string> names = cloud_->getFieldNames();
        m_dialog->getUi()->cmbX->clear();
        m_dialog->getUi()->cmbY->clear();

        for (const std::string a : names) {
            m_dialog->getUi()->cmbX->addItem(a.c_str());

            m_dialog->getUi()->cmbY->addItem(a.c_str());
        }

        return m_dialog->exec() ? 1 : 0;
    }

protected:
    CreateTimeSeriesFromScalarFieldsDlg *m_dialog;

    spc::PointCloudBase::Ptr cloud_;
};

#endif // PLOT2DDATA_H
