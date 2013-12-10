#ifndef Q_GEO_PLUGIN_TEST_HEADER
#define Q_GEO_PLUGIN_TEST_HEADER

#include <qPCL/PclUtils/filters/BaseFilter.h>


class QDialog;

class Test: public BaseFilter
{
    Q_OBJECT
public:
    Test(ccPluginInterface * parent_plugin);
protected:
   virtual int compute();
   virtual int checkSelected();
   virtual int openOutputDialog()
   {
        return 1;
   }



 

};

#endif
