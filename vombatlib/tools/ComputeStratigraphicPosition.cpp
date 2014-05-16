#include "ComputeStratigraphicPosition.h"
#include <dialogs/ComputeStratigraphicPositionDlg.h>

//tmp
#include <helpers/qtHelper.h>

#include <ccConsole.h>
#include <ccPlane.h>

//#include <spc/geology/stratigraphic_normal_model.h>
#include <spc/geology/stratigraphic_evaluator.h>



#include <pcl/io/pcd_io.h>

#include <spc/estimators/attitude_estimator.h>


#include <helpers/spcCCPointCloud.h>

ComputeStratigraphicPosition::ComputeStratigraphicPosition(ccPluginInterface * parent_plugin): BaseFilter(FilterDescription(   "Compute Stratigraphic Position",
                                                                                              "Compute Stratigraphic Position",
                                                                                              "For each point of the cloud compute its stratigraphic position",
                                                                                              ":/toolbar/icons/strat_pos.png")
                                                                                               , parent_plugin),  m_obj(NULL)
{

    std::cout << "created comp strat pos object tool" << std::endl;
    m_dialog = NULL;
}

int
ComputeStratigraphicPosition::openInputDialog()
{

    std::cout << "called OPEN INPUT DIALOG" << std::endl;
    if (!m_dialog)
        m_dialog = new ComputeStratigraphicPositionDlg(0);


    std::cout << "end of OPEN INPUT DIALOG" << std::endl;


    ccHObject::Container objCont;
    this->getAllEntitiesThatHaveMetaData("[vombat][ccSingleAttitudeModel]", objCont);

    std::cout << "at opening" << std::endl;


    //now use these object to populate the combo
    m_dialog->comboBox->updateObjects(objCont);





    return m_dialog->exec() ? 1 : 0;
}

void
ComputeStratigraphicPosition::getParametersFromDialog()
{    
    m_obj = m_dialog->comboBox->getSelected();
}


int
ComputeStratigraphicPosition::compute()
{

    if (!m_obj)
        return 0;

    ccPointCloud * in_cloud = getSelectedEntityAsCCPointCloud();
    if (!in_cloud)
        return 0;




    spcCCPointCloud::Ptr  spcCloud = spcCCPointCloud::Ptr (new spcCCPointCloud (in_cloud));


    spc::spcStratigraphicModelBase * modelBase = dynamic_cast<spc::spcStratigraphicModelBase *> (m_obj);

    if (!modelBase)
        return 0;

    std::vector<float> sps = modelBase->getStratigraphicPositions(spcCloud);

    ccScalarField * field =  new ccScalarField;
    field->setName("SP");

    for (int i =0; i < sps.size(); ++i)
        field->addElement(sps.at(i));

    field->computeMinAndMax();

    in_cloud->addScalarField(field);


//    QString def_name = "Stratigraphic Position";

//    unsigned trys = 1;
//    while (in_cloud->getScalarFieldIndexByName(qPrintable(def_name))>=0 || trys>99)
//        def_name = QString("Stratigraphic Position #%1").arg(++trys);

//    sp_field->setName(qPrintable(def_name));

//    sp_field->computeMinAndMax();

//    int index = in_cloud->getScalarFieldIndexByName(sp_field->getName());
//    std::cout << index << std::endl;
//    if (index >= 0)
//    {
//        //suggest a new name
//        QString new_name = suggestIncrementalName(in_cloud->getScalarFieldName(index) );
//        sp_field->setName(new_name.toStdString().c_str());

//    }

//    int n = in_cloud->addScalarField(sp_field);
//    in_cloud->setCurrentDisplayedScalarField(n);
//    in_cloud->showSF(true);

//    emit entityHasChanged(in_cloud);





//    return 1 ;


}


