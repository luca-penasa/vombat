#include "PropertiesQt.h"
#include <PropertyInspector.h>
#include <QDialog>
#include <vombat.h>
#include <QMainWindow>


#include <QLayout>
PropertiesQt::PropertiesQt(ccPluginInterface* parent_plugin)
    : BaseFilter(FilterDescription("Open Properties Dialog",
                     "Opens the properties editor for selected SPC object",
                     "Properties",
                     ":/toolbar/icons/properties_qt.png"),
          parent_plugin)
{
    this->setShowProgressBar(false);

    QMainWindow * win = vombat::theInstance()->getMainWindow();
    m_dialog = new QDialog(win);

    QLayout * layout  = new QGridLayout(m_dialog);

    m_dialog->setLayout(layout);

    m_propertyBrowser = new PropertyBrowser(m_dialog);

    layout->addWidget(m_propertyBrowser);

    connect(this, SIGNAL(selectionChanged(ccHObject::Container)), this, SLOT(selected(ccHObject::Container)));
//    connect(m_dialog, SIGNAL(objectChanged(ccHObject*)), this, SIGNAL(entityHasChanged(ccHObject*)));
}

PropertiesQt::~PropertiesQt()
{
    delete m_propertyBrowser;
    delete m_dialog;
}

int PropertiesQt::openOutputDialog()
{
    if (m_dialog->isVisible())
        m_dialog->setVisible(false);

    else {
        m_dialog->setVisible(true);
    }

    return 1;
}

void PropertiesQt::selected(const ccHObject::Container &objs)
{
    LOG(INFO) << "called selected";

    if (objs.empty())
    {
        m_propertyBrowser->setObject(nullptr);
        return;
    }

    QList<QObject *> mirrors;

    // \todo fix this;
//    for (int i = 1; i< objs.size(); ++i)
//    {
//        mirrors.append(objs.at(i));
//    }

//    m_propertyBrowser->setObject(objs.at(0), mirrors);

    return;
}
