#include "EvaluateDynamicScalarFieldGenerator.h"
//#include <ccoutofcore/ccMyCCHObject.h>
//#include <ccoutofcore/ccAdditionalCaster.h>

//#include <qPCL/PclUtils/utils/cc2sm.h>

#include <spc/methods/DynamicScalarFieldEvaluator.h>

#include <iostream> // for debug

#include <vombat.h>

#include <spcCCPointCloud.h>
#include <boost/foreach.hpp>

#include <helpers/qtHelper.h>
#include <ccHObjectCaster.h>

EvaluateDynamicScalarFieldGenerator::EvaluateDynamicScalarFieldGenerator(ccPluginInterface *parent_plugin) : BaseFilter(FilterDescription(   "Compute a new scalar field evaluating a Dynamic Scalar Field Generator object",
                                                                         "Compute a new scalar field evaluating a Dynamic Scalar Field Generator object",
                                                                         "Compute a new scalar field evaluating a Dynamic Scalar Field Generator object",
                                                                                                                                             ":/toolbar/icons/SFEvaluator.png"), parent_plugin), m_dialog(0)
{

}


int EvaluateDynamicScalarFieldGenerator::compute()
{
    if (!m_dialog)
    {
        return -1;
    }

    m_generator = dynamic_cast <ccDynamicScalarFieldGenerator *> (m_dialog->ui->cmbModelSelection->getSelected());

    if (!m_generator)
    {
        return -1;
    }

    ccHObject::Container clouds;
    getSelectedEntitiesThatAreCCPointCloud(clouds);

    //for each cloud compute a scalar field! and add it to the pertinent cloud
    spcForEachMacro(ccHObject * obj, clouds)
    {

        ccPointCloud * cloud = ccHObjectCaster::ToPointCloud(obj);
        spcCCPointCloud::Ptr ptr (new spcCCPointCloud  (cloud) );

        spc::DynamicScalarFieldEvaluator evaluator;
        evaluator.setInputCloud(ptr);
        evaluator.setGenerator(m_generator->getGenerator());
        evaluator.compute();

        std::cout << "test " << m_generator->getGenerator()->getScalarFieldValue(Vector3f(0,0,0)) << std::endl;

        std::vector<float> scalars = m_generator->getGenerator()->getScalarFieldValues(ptr);

        for (int i = 0 ; i < 10; ++i)
            std::cout << "val " << scalars.at(i) << std::endl;

//        spcForEachMacro(auto s, scalars)
//                std::cout << s << std::endl;

        std::string sf_name = m_dialog->ui->lneSFName->text().toStdString();
        if (sf_name.empty())
        {
            sf_name = "Scalar Field"; // to a default
        }

        ccScalarField * sf = new ccScalarField(sf_name.c_str());
        sf->reserve(cloud->size());

        int counter = 0;
        spcForEachMacro(float f , scalars)
        {
            sf->setValue(counter++, f);
        }
        sf->computeMinAndMax();

        int index = cloud->getScalarFieldIndexByName(sf->getName());

        if (index >= 0)
        {
            if (this->m_dialog->ui->chkOverwrite->isChecked()) // delete existing
            {
                cloud->deleteScalarField(index);
            }
            else
            {
                //suggest a new name
                QString new_name = suggestScalarFieldIncrementalName(cloud, sf_name.c_str() );
                sf->setName(new_name.toStdString().c_str());
            }

        }



        int n = cloud->addScalarField(sf);
        cloud->setCurrentDisplayedScalarField(n);
        cloud->showSF(true);

        emit entityHasChanged(cloud);


    }

    return 1;
}

int EvaluateDynamicScalarFieldGenerator::openInputDialog()
{


    if( !m_dialog)
        m_dialog= new EvaluateDynamicScalarFieldGeneratorDlg;


    ccHObject::Container selected;
    getAllEntitiesThatHaveMetaData(QString("[vombat][ccDynamicScalarFieldGenerator]"), selected);

    if (selected.size() <= 0)
        return -1;

    m_dialog->ui->cmbModelSelection->updateObjects(selected);

    return m_dialog->exec() ? 1 : 0;
}


int EvaluateDynamicScalarFieldGenerator::checkSelected()
{
    ccHObject::Container cont;
    getSelectedEntitiesThatAreCCPointCloud(cont);
    if (cont.size() != 0)
        return 1;
    else
        return 0;
}
