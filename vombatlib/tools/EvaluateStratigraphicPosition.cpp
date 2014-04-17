#include "EvaluateStratigraphicPosition.h"

//#include <ccoutofcore/ccMyCCHObject.h>
//#include <ccoutofcore/ccAdditionalCaster.h>

//#include <qPCL/PclUtils/utils/cc2sm.h>

#include <spc/geology/stratigraphic_evaluator.h>


#include <iostream> // for debug

#include <vombat.h>

#include <spcCCPointCloud.h>
#include <boost/foreach.hpp>

EvaluateStratigraphicPosition::EvaluateStratigraphicPosition(ccPluginInterface *parent_plugin) : BaseFilter(FilterDescription(   "Evaluate Stratigraphic Position",
                                                                         "Evaluate the stratiraphic position for the current clouds",
                                                                         "Evaluate the stratiraphic position for the current clouds",
                                                                         ":/toolbar/icons/ev_sp.png"), parent_plugin)
{

}


int EvaluateStratigraphicPosition::compute()
{
    if (!m_dialog)
    {
        getMainAppInterface()->dispToConsole("[vombat] aborted due to null pointer to dialog");
        return -1;
    }

    std::cout << "starting compute method()" << std::endl;

    m_model = static_cast <ccSingleAttitudeModel *> (m_dialog->getSelectedObject());

    if (!m_model)
    {
        getMainAppInterface()->dispToConsole("[vombat] aborted due to null pointer to model");
        return -1;
    }






    //now get the selected cloud (we are sure at least one exists - see checkSelected)

    ccHObject::Container clouds;
    getSelectedEntitiesThatAreCCPointCloud(clouds);

//    spc::spcStratigraphicModelBase * m_base = static_cast<spc::spcStratigraphicModelBase *> (m_model);

//    spc::StratigraphicModelBase::Ptr m_base_ptr = boost::make_shared<spc::StratigraphicModelBase> (*m_base);

    //for each cloud compute a scalar field! and add it to the pertinent cloud
    BOOST_FOREACH(ccHObject * obj, clouds)
    {

        ccPointCloud * cloud = ccHObjectCaster::ToPointCloud(obj);
        spcCCPointCloud::Ptr ptr (new spcCCPointCloud  (cloud) );

        spc::StratigraphicEvaluator evaluator;
        evaluator.setInputCloud(ptr);
        evaluator.setInputModel(m_model->getModel());
        evaluator.compute();

        std::vector<float> scalars = evaluator.getOutput();


        ccScalarField * sf = new ccScalarField("Stratigraphic Position");
        sf->reserve(cloud->size());

        int counter = 0;
        BOOST_FOREACH(float f , scalars)
        {
            sf->setValue(counter++, f);
        }
        sf->computeMinAndMax();

        int index = cloud->getScalarFieldIndexByName(sf->getName());

        if (index >= 0)
        {
            //suggest a new name
            QString new_name = suggestIncrementalName(cloud->getScalarFieldName(index) );
            sf->setName(new_name.toStdString().c_str());

        }

        int n = cloud->addScalarField(sf);
        cloud->setCurrentDisplayedScalarField(n);
        cloud->showSF(true);

        emit entityHasChanged(cloud);


    }

    return 1;
}

int EvaluateStratigraphicPosition::openInputDialog()
{



    std::cout << "starting open input dialog method()" << std::endl;

    if( !m_dialog)
        m_dialog= new FastCloudSelectionDlg();


    ccHObject::Container selected;
    getAllEntitiesThatHaveMetaData(QString("[vombat][ccSingleAttitudeModel]"), selected);

    std::cout << selected.size() << "N: " <<std::endl;

    if (selected.size() <= 0)
        return -1;

    std::cout << "before to updateList()" << std::endl;

    m_dialog->updateList(selected);


std::cout << "ended open input dialog method()" << std::endl;

    return m_dialog->exec() ? 1 : 0;
}


int EvaluateStratigraphicPosition::checkSelected()
{
    ccHObject::Container cont;
    getSelectedEntitiesThatAreCCPointCloud(cont);
    if (cont.size() != 0)
        return 1;
    else
        return 0;
}
