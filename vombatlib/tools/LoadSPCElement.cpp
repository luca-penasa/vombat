#include "LoadSPCElement.h"


LoadSPCElement::LoadSPCElement(ccPluginInterface * parent_plugin): BaseFilter(FilterDescription(   "Load SPC elements",
                                                                                                   "Load SPC elements",
                                                                                                   "Load SPC elements",
                                                                                                   ":/toolbar/icons/load.png")
                                                                              , parent_plugin)
{

    setShowProgressBar(false);

}

int LoadSPCElement::compute()
{

    for (QString filename : m_filenames)
    {
        if (QFileInfo(filename).suffix() == "pcd")
        {
            LOG(INFO) << "Found a pcd file. Loading as SPC point cloud source";
            spc::CloudDataSourceOnDisk::Ptr ob(new spc::CloudDataSourceOnDisk(filename.toStdString()));
            ccCloudDataSourceOnDisk * source = new ccCloudDataSourceOnDisk(ob);
            LOG(INFO) << "going to send back the entity";

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


        LOG(INFO) << "new ccHObject correctly created";
        //! \todo use a stack please

        rebuildMyChildsRecursive(newobj);
        newEntity(newobj);
    }

    return 1;
}


