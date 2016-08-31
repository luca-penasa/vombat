#include "SaveSPCElement.h"
#include <vombat.h>
#include <spc/core/ElementBase.h>

#include <ccoutofcore/ccSPCElementShell.h>
#include <ccoutofcore/ccAttitude.h>
//#include <boost/typeof/typeof.hpp>

#include <spc/io/element_io.h>

#include <iostream>
#include <spc/core/file_operations.h>

#include <QFileDialog>


SaveSPCElement::SaveSPCElement(ccPluginInterface* parent_plugin)
    : BaseFilter(FilterDescription("Save selected as SPC elemnts",
                     "Save selected as SPC elemnts",
                     "Save selected as SPC elemnts",
                     ":/toolbar/icons/save.png"),
          parent_plugin)
{

    setShowProgressBar(false);
}

int SaveSPCElement::compute()
{
    // only the first one

    ccHObject::Container all = vombat::theInstance()->getAllObjectsSelectedBySPCDti(&spc::ElementBase::Type);

    std::vector<spc::ISerializable::Ptr> to_be_saved;
    for (ccHObject* el : all) {
        ccSPCElementShell* asShell = dynamic_cast<ccSPCElementShell*>(el);
        if (asShell)
            to_be_saved.push_back(asShell->getSPCElement());
    }

    DLOG(INFO) << "selected filter: " << m_filter.toStdString();
    std::string sel = m_filter.toStdString();
    std::string ok(sel.begin(), sel.end() - 1); // skip a char
    ok = spc::getExtension(ok);

    spc::io::ARCHIVE_TYPE type = spc::io::extension_to_type(ok);

    if (to_be_saved.size() == 1) {
        spc::io::serializeToFile(to_be_saved.at(0), spc::getBaseFileName(m_filename.toStdString()), type);
    }
    else {

        spc::io::serializeToFile(to_be_saved, spc::getBaseFileName(m_filename.toStdString()), type, false, "", 3);
    }
    return 1;
}

int SaveSPCElement::openInputDialog()
{
    QString selected;
    m_filename.clear();
    m_filename = QFileDialog::getSaveFileName(0,
        tr("Save To XML File"),
        "",
        tr("SPC XML Documents (*.xml);;SPC binary files (*.spc);;SPC JSON Documents (*.json);;ASCII files - only supp (*.txt)"),
        &selected);

    m_filter = selected;
    if (m_filename.isEmpty())
        return -1;

    return 1;
}

int SaveSPCElement::checkSelected()
{
    // we can save any kind of SPC object
    ccHObject::Container all = vombat::theInstance()->getAllObjectsSelectedBySPCDti(&spc::ElementBase::Type);

    if (all.size() >= 1) // one at a time for now
        return 1;
    else
        return -1;
}
