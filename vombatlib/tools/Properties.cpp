#include "Properties.h"
#include <dialogs/ccPropertiesTree.h>

Properties::Properties(ccPluginInterface* parent_plugin)
    : BaseFilter(FilterDescription("Open Properties Dialog",
                     "Opens the properties editor for selected SPC object",
                     "Properties",
                     ":/toolbar/icons/properties.png"),
          parent_plugin)
{
    this->setShowProgressBar(false);

    m_dialog = new ccPropertiesTree();

    connect(this, SIGNAL(selectionChanged(ccHObject::Container)), m_dialog, SLOT(selectionChanged(ccHObject::Container)));
    connect(m_dialog, SIGNAL(objectChanged(ccHObject*)), this, SIGNAL(entityHasChanged(ccHObject*)));
}

Properties::~Properties()
{
    delete m_dialog;
}

int Properties::openOutputDialog()
{
    if (m_dialog->isVisible())
        m_dialog->setVisible(false);

    else {
        m_dialog->setVisible(true);
    }

    return 1;
}
