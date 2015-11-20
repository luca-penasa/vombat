#ifndef LOAD_SPC_ELEMENT_H
#define LOAD_SPC_ELEMENT_H

#include "BaseFilter.h"

#include <stack>
#include <vombat.h>
#include <ccStratigraphicConstrain.h>

#include <ccoutofcore/ccSPCElementShell.h>
#include<ccoutofcore/ccAttitude.h>
#include <ccoutofcore/ccEigenTable.h>
#include <ccoutofcore/ccSample.h>
#include <ccoutofcore/ccSingleAttitudeModel.h>

#include <ccPlanarSelection.h>

#include <ccVirtualOutcrop.h>
#include <ccoutofcore/ccCloudDataSourceOnDisk.h>
#include <ccTimeSeries.h>


#include <QApplication>
#include <QFileDialog>
class LoadSPCElement: public BaseFilter
{
public:
    LoadSPCElement(ccPluginInterface * parent_plugin);

    static ccHObject * elementToCCHobject(spc::ElementBase::Ptr el)
    {
        ccHObject * newobj;

        if (el == NULL)
        {
            LOG(ERROR)<<"you passed a null pointer!";
            return NULL;
        }

        if (el->getType() == &spc::Attitude::Type)
        {
            spc::Attitude::Ptr att = spcDynamicPointerCast<spc::Attitude>(el);
            newobj = new ccAttitude(att);
        }
        else if (el->getType() == &spc::EigenTable::Type)
        {
            spc::EigenTable::Ptr att = spcDynamicPointerCast<spc::EigenTable>(el);
            newobj = new ccEigenTable(att);
        }
        else if (el->getType() == &spc::Sample::Type)
        {
            spc::Sample::Ptr att = spcDynamicPointerCast<spc::Sample>(el);
            newobj = new ccSample(att);
        }
        else if (el->getType() ==&spc::SelectionRubberband::Type)
        {
            spc::SelectionRubberband::Ptr att = spcDynamicPointerCast<spc::SelectionRubberband> (el);
           LOG(INFO) << "found selection rubberband with T " << att->getPojectionTransform().matrix();
            newobj = new ccPlanarSelection(att);
        }

        else if (el->getType() ==&spc::CloudDataSourceOnDisk::Type)
        {
            spc::CloudDataSourceOnDisk::Ptr ob = spcDynamicPointerCast<spc::CloudDataSourceOnDisk> (el);
            newobj = new ccCloudDataSourceOnDisk(ob);
        }

        else if (el->getType() ==& spc::StratigraphicModelSingleAttitude::Type)
        {
            spc::StratigraphicModelSingleAttitude::Ptr ob = spcDynamicPointerCast<spc::StratigraphicModelSingleAttitude> (el);
            newobj = new ccSingleAttitudeModel(ob);
//            newobj->setName(ob->getElementName());
        }

        else if (el->getType() == & spc::VirtualOutcrop::Type)
        {
            spc::VirtualOutcrop::Ptr ob = spcDynamicPointerCast<spc::VirtualOutcrop>(el);
            newobj = new ccVirtualOutcrop(ob);
        }

        else if (el->isA(&spc::TimeSeriesBase::Type))
        {
                 spc::TimeSeriesBase::Ptr series= spcDynamicPointerCast<spc::TimeSeriesBase>(el);
                 newobj = new ccTimeSeries(series);
        }

        else if (el->isA(&spc::StratigraphicConstrain::Type))
        {
            spc::StratigraphicConstrain::Ptr ob= spcDynamicPointerCast<spc::StratigraphicConstrain>(el);
            newobj = new ccStratigraphicConstrain(ob);
        }
        else
        {
            LOG(WARNING) << "cannot transform the loaded spc element into something cloudcompare-comaptible. plase provide the implementation here.";
            newobj = NULL;
        }




        LOG(INFO) << "new object created.";

        return newobj;
    }

    static void rebuildMyChildsRecursive(ccHObject * newobj)
    {
        LOG(INFO) << "new ccHObject correctly created";
        //! \todo use a stack please
        std::stack<ccHObject *> to_parse;
        to_parse.push(newobj);

        while (to_parse.size() != 0 )
        {
            LOG(INFO) << "parsing chid" << to_parse.top()->getName().toStdString();

            ccHObject * child = to_parse.top();
            to_parse.pop();

            std::vector<ccHObject *> news = rebuildMyChilds(child);

            for (ccHObject * obj: news)
            {
                to_parse.push(obj);
            }

            LOG(INFO) << "parsing done still n: " << to_parse.size();
        }


        newobj->setEnabled(true);
        newobj->setVisible(true);
    }


    static std::vector<ccHObject *> rebuildMyChilds(ccHObject *parent)
    {

        LOG(INFO) << "called rebuild my childs";
        std::vector<ccHObject *> out;
        ccSPCElementShell * asmine = dynamic_cast<ccSPCElementShell *> (parent);

        CHECK(asmine != NULL);

        LOG(INFO) << "correctly transformed to a ccSPCElementShell: " << asmine->getSPCClassName().toStdString();

        for (spc::ElementBase::Ptr el: asmine->getSPCElement()->getChilds())
        {
            if (vombat::theInstance()->getObjectFromElement(el) != NULL) // is yet present in the current tree
            {
                LOG(INFO) << "object is yet present in the tree. Not rebuilding it " << el->getType()->getClassName();
                out.push_back(vombat::theInstance()->getObjectFromElement(el));
                continue; //nothing to be done
            }

            LOG(INFO) << "working on child of type " << el->getType()->getClassName();
            ccHObject * ascc =  elementToCCHobject(el);                       

            if (!ascc)
                continue;

            out.push_back(ascc);

            ascc->setEnabled(true);
            ascc->setVisible(true);


            parent->ccHObject::addChild(ascc);                        
        }

        return out;

    }

    virtual int compute ();

    virtual int openInputDialog()
    {

        QSettings settings;
        settings.beginGroup("vombat");
        QString current_path = settings.value("CurrentLoadPath",QApplication::applicationDirPath()).toString();
//        QString currentOpenDlgFilter = settings.value("CurrentOpenDialogFilter","SPC XML Documents (*.xml)").toString();



        m_filenames.clear();
        m_filenames =  QFileDialog::getOpenFileNames(0,
                                                     "Load SPC data sources",
                                                     current_path,
                                                     "SPC XML Documents (*.xml);; SPC binary files (*.spc);; SPC JSON Documents (*.json);; PCD files sources (*.pcd)");
        if (m_filenames.isEmpty())
            return -1;



        current_path = QFileInfo(m_filenames[0]).absolutePath();
        settings.setValue("CurrentLoadPath", current_path);
//        settings.setValue(s_psSelectedInputFilter,currentOpenDlgFilter);
        settings.endGroup();


        return 1;
    }

    virtual int checkSelected()
    {
        return 1;
    }


protected:
    QStringList m_filenames;


};

#endif // OPENINCOMPOSER_H
