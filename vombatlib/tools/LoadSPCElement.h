#ifndef LOAD_SPC_ELEMENT_H
#define LOAD_SPC_ELEMENT_H

#include <qPCL/PclUtils/filters/BaseFilter.h>

#include <vombat.h>

#include <ccoutofcore/ccMyBaseObject.h>
#include<ccoutofcore/ccAttitude.h>
#include <ccoutofcore/ccEigenTable.h>
#include <ccoutofcore/ccSample.h>
//#include <ccoutofcore/ccSingleAttitudeModel.h>

#include <ccPlanarSelection.h>


#include <ccoutofcore/ccCloudDataSourceOnDisk.h>

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

        else
        {
            LOG(WARNING) << "cannot transform the loaded spc element into something cloudcompare-comaptible. plase provide the implementation here.";
            newobj = NULL;
        }

        return newobj;
    }


    static std::vector<ccHObject *> rebuildMyChilds(ccHObject *parent)
    {
        std::vector<ccHObject *> out;
        ccMyBaseObject * asmine = dynamic_cast<ccMyBaseObject *> (parent);

        CHECK(asmine != NULL);

        for (spc::ElementBase::Ptr el: asmine->getSPCElement()->getChilds())
        {
            ccHObject * ascc =  elementToCCHobject(el);
            if (!ascc)
                continue;

            out.push_back(ascc);

            ascc->setEnabled(true);
            ascc->setVisible(true);
            parent->addChild(ascc);
        }

    }

    virtual int compute ()
    {

        for (QString filename : m_filenames)
        {
            if (QFileInfo(filename).suffix() == "pcd")
            {
                LOG(INFO) << "Found a pcd file. Loading as SPC point cloud source";

                ccCloudDataSourceOnDisk * source = new ccCloudDataSourceOnDisk(filename.toStdString());

                newEntity(source);

                continue;

            }


            spc::ISerializable::Ptr obj = spc::io::deserializeFromFile(filename.toStdString());

            if (!obj)
                return -1;

            spc::ElementBase::Ptr el = spcDynamicPointerCast<spc::ElementBase> (obj);



            if (!el)
                return -1;

            //! this must be moved in a real factory!
            ccHObject * newobj = elementToCCHobject(el);

            if (!newobj)
                return -1;



            //! \todo use a stack please
            std::vector<ccHObject *> to_parse = {newobj};

            while (to_parse.size() != 0 )
            {
                ccHObject * child = to_parse.at(0);

                // remove from stack
                to_parse.erase(std::remove(to_parse.begin(), to_parse.end(), child), to_parse.end());


                std::vector<ccHObject *> news = rebuildMyChilds(child);

                for (ccHObject * obj: news)
                {
                    to_parse.push_back(obj);
                }

            }


            newobj->setEnabled(true);
            newobj->setVisible(true);


            newEntity(newobj);

        }

        return 1;
    }

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
