#ifndef Q_GEO_PLUGIN_TEST_HEADER
#define Q_GEO_PLUGIN_TEST_HEADER

#include <qPCL/PclUtils/filters/BaseFilter.h>

#include <spc/common/common.h>

#include <spc/flann/flann1dsearcher.h>

class QDialog;

class Test: public BaseFilter
{
    Q_OBJECT
public:
    Test(ccPluginInterface * parent_plugin);
protected:
    virtual int compute()
    {

        return 1;
    }

    virtual int checkSelected()
    {
        return 1;
    }
    virtual int openInputDialog()
    {


        std::vector<float> x(100);
        for (int i =0 ; i < 100; ++i)
            x.at(i) = 0.2;

        spc::Flann1DSearcher<float> ecco(x);


          return 1;
    }
    virtual int openOutputDialog()
    {
        return 1;
    }





};

#endif
