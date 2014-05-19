#ifndef CREATE_TIME_SERIES_FROM_SCALAR_FIELDS_H
#define CREATE_TIME_SERIES_FROM_SCALAR_FIELDS_H


#include <qPCL/PclUtils/filters/BaseFilter.h>

#include <helpers/spcCCPointCloud.h>

#include <dialogs/CreateTimeSeriesFromScalarFieldsDlg.h>

#include "ui_CreateTimeSeriesFromScalarFieldsDlg.h"

#include <spc/time_series/sparse_time_series.h>

#include <ccoutofcore/ccTimeSeries.h>

#include <spc/methods/time_series_generator.h>
#include <plotter2d/Plotter2DDlg.h>

#include <spc/common/common.h>


class CreateTimeSeriesFromScalarFields : public BaseFilter
{
public:
    CreateTimeSeriesFromScalarFields(ccPluginInterface * parent_plugin = 0);

    ~CreateTimeSeriesFromScalarFields()
    {
        if (m_dialog && m_dialog->parent() == 0)
            delete(m_dialog);
    }



    // BaseFilter interface
public:
    // virtual from BaseFilter
    int compute()
    {

        bool doKS = m_dialog->getUi()->grpKS->isChecked();

        ccPointCloud * cccloud = getSelectedEntityAsCCPointCloud();
        spc::spcGenericCloud::Ptr cloud = spc::spcGenericCloud::Ptr(new  spcCCPointCloud(cccloud));

        if (!cloud)
            return -1;

        std::string x_field_name, y_field_name;

        x_field_name = m_dialog->getUi()->cmbX->getSelectedFiedName();
        y_field_name = m_dialog->getUi()->cmbY->getSelectedFiedName();

        std::string name = x_field_name + "_" + y_field_name;

        spc::GenericTimeSeries<float>::Ptr serie;

        if (!doKS)
        {
            std::vector<float>  x = cloud->getField(x_field_name);
            std::vector<float>  y = cloud->getField(y_field_name);

            // simply build up a scatters TS with the two scalar fields
            serie = spc::SparseTimeSeries<float>::Ptr (new spc::SparseTimeSeries<float>(x, y));
        }


        else // do KS
        {

            float ssx = m_dialog->getUi()->cmbSSX->value();
            float ksx = m_dialog->getUi()->cmbKSX->value();

            name += "_smoothed_" +  spc::asString(ssx) + "_" +spc::asString(ksx);

            spc::TimeSeriesGenerator generator;
            generator.setInputCloud(cloud);
            generator.setXFieldName(x_field_name);
            generator.setYFieldName(y_field_name);

            generator.setSamplingStep(ssx);
            generator.setBandwidth(ksx);
            generator.compute();
            serie = generator.getOutputSeries();
            if (!serie)
                return -1;

        }

        ccTimeSeries * ccserie = new ccTimeSeries(serie);

        cccloud->addChild(ccserie);

        ccserie->setName(name.c_str());

        newEntity(cccloud);
        return 1;
    }


protected:
    ///// virtuals from BaseFilters
    int checkSelected()
    {
        return isFirstSelectedCcPointCloud();
    }

    int openInputDialog()
    {
        if (!m_dialog)
            m_dialog =  new CreateTimeSeriesFromScalarFieldsDlg(0);

        // populate the right way the dialog
        ccPointCloud * cloud = getSelectedEntityAsCCPointCloud();

        m_dialog->getUi()->cmbX->clear();
        m_dialog->getUi()->cmbX->addItemsFromFieldsCloud(cloud);

        m_dialog->getUi()->cmbY->clear();
        m_dialog->getUi()->cmbY->addItemsFromFieldsCloud(cloud);





        return m_dialog->exec() ? 1 : 0;
    }


    //    int openOutputDialog() {}
    //    void getParametersFromDialog() {}
    //    int checkParameters() {}


protected:
    CreateTimeSeriesFromScalarFieldsDlg * m_dialog;
};

#endif // PLOT2DDATA_H
