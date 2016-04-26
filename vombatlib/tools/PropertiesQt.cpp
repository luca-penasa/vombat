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

void PropertiesQt::selected(ccHObject::Container &objs)
{
    LOG(INFO) << "called selected";

    if (objs.empty())
    {
        m_propertyBrowser->setObject(nullptr);
        return;
    }

    QList<QObject *> mirrors;
<<<<<<< HEAD

    // \todo fix this;
    for (int i = 1; i< objs.size(); ++i)
    {
        QObject * asqt = dynamic_cast<QObject*> (objs.at(i));

        if (asqt)
            mirrors.push_back(asqt);
    }

    if (mirrors.empty())
        return;


    LOG(INFO) << "setting new selection in properties qt";
    m_propertyBrowser->setObject(mirrors.at(0), mirrors);
=======

    // \todo fix this;
//    for (int i = 1; i< objs.size(); ++i)
//    {
//        mirrors.append(objs.at(i));
//    }

//    m_propertyBrowser->setObject(objs.at(0), mirrors);
>>>>>>> 4d76e02bbef7b55ab45eecb6f21f51bddb697e21

    return;
}
