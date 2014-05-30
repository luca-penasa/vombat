#include "ExportToAscii.h"
#include <vombat.h>
#include <PlotterDlg.h>

#include <spc/io/time_series_writer.h>

#include <boost/filesystem.hpp>
#include <sstream>

ExportToAscii::ExportToAscii(ccPluginInterface *parent_plugin) : BaseFilter(FilterDescription(   "Export to ascii txt ",
                                                                                                 "Export to ascii txt",
                                                                                                 "Export to ascii txt",
                                                                                                 ":/toolbar/icons/export_to_ascii.png" ), parent_plugin)
{
    this->setShowProgressBar(false);

}

int
ExportToAscii::compute()
{

    ccHObject::Container ts_list = vombat::theInstance()->getSelectedThatHaveMetaData("[vombat][ccTimeSeries]");

    std::cout << "here" << std::endl;

    int counter = 0 ;
    spcForEachMacro(ccHObject * ts, ts_list)
    {
        ccTimeSeries * t  = dynamic_cast<ccTimeSeries *> (ts) ;

        if (!t)
        {
            break;
        }

        std::cout << m_filename.toStdString().c_str() << std::endl;


        spc::TimeSeriesBase<float>::Ptr spct = t->getTimeSeries();

        spc::TimeSeriesWriter<float> w;

        boost::filesystem::path const p(m_filename.toStdString().c_str());

        boost::filesystem::path basename ( p.stem());
        boost::filesystem::path path = p.parent_path();
        boost::filesystem::path  ext = p.extension();

        std::stringstream sstream;

        sstream << path.c_str() << "/";
        sstream << basename.c_str() ;
        sstream << "_" << counter << "." << ext;

        std::cout << "saved to:" << sstream.str().c_str() << std::endl;


        w.setFilename(sstream.str());

        w.setInputSeries(spct);
        w.writeAsciiAsSparse();

        std::cout << "saved to:" << sstream.str().c_str() << std::endl;



    }

    return 1;
}

int ExportToAscii::openInputDialog()
{
    m_filename.clear();
    m_filename = QFileDialog::getSaveFileName(0, "select base filename", "", " ASCII text (*.txt *.csv)");
    if (m_filename.isEmpty())
        return -1;

    return 1;
}

int ExportToAscii::checkSelected()
{


    return 1;
}

