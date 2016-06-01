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

//    connect(this, SIGNAL(selectionChanged(ccHObject::Container &)), this, SLOT(selected(ccHObject::Container &)));
    connect(this, &PropertiesQt::selectionChanged, this, &PropertiesQt::selected);
//    connect(m_dialog, SIGNAL(objectChanged(ccHObject*)), this, SIGNAL(entityHasChanged(ccHObject*)));


    DLOG(INFO) << "created properties tree";

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
    DLOG(INFO) << "called selected . selection changed in main tree";

    if (objs.empty())
    {
        DLOG(INFO) << "no objects ins selectio. returning nullptr";
        m_propertyBrowser->setObject(nullptr);
        return;
    }

    QList<QObject *> mirrors;

    // \todo fix this;
    for (int i = 0; i< objs.size(); ++i)
    {
        QObject * asqt = dynamic_cast<QObject*> (objs.at(i));
        if (asqt)
        {
            DLOG(INFO) << "found qobject derived selection! ";
            mirrors.push_back(asqt);
        }
    }

    if (mirrors.empty())
    {
        DLOG(INFO) <<"mirrors is empty";
        m_propertyBrowser->setObject(nullptr);
        return;
    }


    LOG(INFO) << "setting new selection in properties qt";
    m_propertyBrowser->setObject(mirrors.at(0), mirrors);

    return;
}
