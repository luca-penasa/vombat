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
#include <ccScalarField.h>

#include <dialogs/ccHObjectSelectionDlgSimple.h>
#include <spc/elements/StratigraphicModelSingleAttitude.h>
#include <ccoutofcore/ccSingleAttitudeModel.h>

#include <EvaluateDynamicScalarFieldGeneratorDlg.h>
EvaluateDynamicScalarFieldGenerator::EvaluateDynamicScalarFieldGenerator(ccPluginInterface* parent_plugin)
    : BaseFilter(FilterDescription("Compute a new scalar field evaluating a Dynamic Scalar Field Generator object",
                     "Compute a new scalar field evaluating a Dynamic Scalar Field Generator object",
                     "Compute a new scalar field evaluating a Dynamic Scalar Field Generator object",
                     ":/toolbar/icons/SFEvaluator.png"),
          parent_plugin)
    , m_dialog(0)
{
}

int EvaluateDynamicScalarFieldGenerator::compute()
{
    if (!m_dialog) {
        DLOG(ERROR) << "no dialog found";
        return -1;
    }

    m_generator = dynamic_cast<ccDynamicScalarFieldGenerator*>(m_dialog->ui->cmbModelSelection->getSelected());

    if (!m_generator) {
        DLOG(ERROR) << "no generator found";
        return -1;
    }

    ccHObject::Container clouds;
    getSelectedEntitiesThatAreCCPointCloud(clouds);

    //for each cloud compute a scalar field! and add it to the pertinent cloud
    for (ccHObject* obj : clouds) {
        ccPointCloud* cloud = ccHObjectCaster::ToPointCloud(obj);
        spcCCPointCloud::Ptr ptr = spcCCPointCloud::fromccPointCloud(cloud);

        Eigen::VectorXf scalars = spc::evaluate_dynamic_scalar_field_generator<float>(ptr, m_generator->getGenerator());

        std::string sf_name = m_dialog->ui->lneSFName->text().toStdString();
        if (sf_name.empty()) {
            sf_name = "Scalar Field"; // to a default
            DLOG(WARNING) << "scalar field name to default: " << sf_name;
        }

        ccScalarField* sf = new ccScalarField(sf_name.c_str());
        sf->reserve(cloud->size());

        for (int i = 0; i < scalars.size(); ++i) {
            sf->setValue(i, scalars.at(i));
        }

        int index = cloud->getScalarFieldIndexByName(sf->getName());

        if (index >= 0) {
            if (this->m_dialog->ui->chkOverwrite->isChecked()) // delete existing
            {
                cloud->deleteScalarField(index);
            }
            else {
                //suggest a new name
                QString new_name = suggestScalarFieldIncrementalName(cloud, sf_name.c_str());
                sf->setName(new_name.toStdString().c_str());
            }
        }

        int n = cloud->addScalarField(sf);
        cloud->setCurrentDisplayedScalarField(n);
        cloud->showSF(true);

        sf->computeMinAndMax();

        emit entityHasChanged(cloud);
    }

    return 1;
}

int EvaluateDynamicScalarFieldGenerator::openInputDialog()
{

    if (!m_dialog)
        m_dialog = new EvaluateDynamicScalarFieldGeneratorDlg;

    ccHObject::Container selected;
    selected = vombat::theInstance()->getAllObjectsInTreeBySPCDti(&spc::VariableScalarFieldBase::Type);

    if (selected.size() <= 0) {
        LOG(ERROR) << "no dynamic scalar field generator found";
        return -1;
    }

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
