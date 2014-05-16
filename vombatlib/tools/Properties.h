#ifndef PROPERTIES_H
#define PROPERTIES_H

//#include <BaseFilter.h>
#include <dialogs/ccProperties.h>
#include <qPCL/PclUtils/filters/BaseFilter.h>

class Properties : public BaseFilter
{
public:


    Properties(ccPluginInterface * parent_plugin = 0);

    virtual int compute() {return 1;}

    int checkSelected() {return 1;}

    int openOutputDialog();

private:

    ccProperties * m_dialog;
};

#endif // PROPERTIES_H