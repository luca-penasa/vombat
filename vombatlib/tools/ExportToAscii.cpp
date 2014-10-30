#include "ExportToAscii.h"
#include <vombat.h>
#include <PlotterDlg.h>

#include <spc/io/AsciiEigenTableWriter.h>

#include <boost/filesystem.hpp>
#include <spc/elements/Fields.h>
#include <sstream>

#include <spc/elements/Attitude.h>

#include <boost/lexical_cast.hpp>

ExportToAscii::ExportToAscii(ccPluginInterface *parent_plugin)
    : BaseFilter(FilterDescription("Export to ascii txt ",
                                   "Export to ascii txt", "Export to ascii txt",
                                   ":/toolbar/icons/export_to_ascii.png"),
                 parent_plugin)
{
    this->setShowProgressBar(false);
}

int ExportToAscii::compute()
{

    ccHObject::Container ts_list = vombat::theInstance()->getSelected();

    int counter = 0;
    for(ccHObject * ts: ts_list)
    {
        ccMyBaseObject *myobj = dynamic_cast<ccMyBaseObject *>(ts);

        spc::EigenTable::Ptr obj;

        if (myobj->isASPC(&spc::EigenTable::Type))
            obj = spcDynamicPointerCast
                <spc::EigenTable>(myobj->getSPCElement());
        else
            obj = myobj->getSPCElement()->asEigenTable();

        if (myobj && myobj->getSPCElement()->isAsciiSerializable()) {

            typedef boost::filesystem::path pathT;
            pathT p(m_filename.toStdString().c_str());

            std::string newname = p.stem().string() + std::string("_")
                                  + boost::lexical_cast<std::string>(counter++)
                                  + p.extension().string();

            pathT out_file = p.parent_path() / newname;

            spc::io::AsciiEigenTableWriter w;

            if (!obj)
                return -1;

            w.setOutputFilename(out_file.c_str());
            w.setInput(obj);
            w.write();
        }
        else
            return -1;
    }

    return 1;
}

int ExportToAscii::openInputDialog()
{
    m_filename.clear();
    m_filename = QFileDialog::getSaveFileName(0, "select base filename", "",
                                              " ASCII text (*.txt *.csv)");
    if (m_filename.isEmpty())
        return -1;

    return 1;
}

int ExportToAscii::checkSelected()
{

    return 1;
}
