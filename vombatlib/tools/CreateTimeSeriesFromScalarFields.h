#ifndef CREATE_TIME_SERIES_FROM_SCALAR_FIELDS_H
#define CREATE_TIME_SERIES_FROM_SCALAR_FIELDS_H


#include <qPCL/PclUtils/filters/BaseFilter.h>

#include <helpers/spcCCPointCloud.h>

#include <dialogs/CreateTimeSeriesFromScalarFieldsDlg.h>

#include "ui_CreateTimeSeriesFromScalarFieldsDlg.h"

#include <spc/time_series/sparse_time_series.h>

#include <ccoutofcore/ccTimeSeries.h>
#include <plotter2d/Plotter2DDlg.h>


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

        spc::spcGenericCloud * cloud = new  spcCCPointCloud(getSelectedEntityAsCCPointCloud());

        if (!cloud)
            return -1;

        std::string x_field_name, y_field_name;

        x_field_name = m_dialog->getUi()->cmbX->getSelectedFiedName();
        x_field_name = m_dialog->getUi()->cmbY->getSelectedFiedName();

        if (doKS)
        {

            std::vector<float>  x = cloud->getField(x_field_name);
            std::vector<float>  y = cloud->getField(y_field_name);


            std::cout << x.size() << std::endl;
            spc::SparseTimeSeries<float>::Ptr serie = spc::SparseTimeSeries<float>::Ptr (new spc::SparseTimeSeries<float>(x, y));

            ccTimeSeries * ccserie =  new ccTimeSeries(serie);

            QVector<double> qx = ccserie->getX();
            QVector<double> qy = ccserie->getY();

            Plotter2DDlg * plot = vombat::theInstance()->getPlotter2DDlg();

            this->newEntity(ccserie);

            plot->addPlot(ccserie);


        }


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
