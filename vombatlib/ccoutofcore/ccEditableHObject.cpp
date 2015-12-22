#include "ccEditableHObject.h"
#include <QDialog>

#include <ccConsole.h>

ccEditableHObject::ccEditableHObject(): m_edit_dlg(0), m_edit_dlg_is_freezes_ui(true)
{

}

ccEditableHObject::~ccEditableHObject()
{
    delete m_edit_dlg;
}

bool ccEditableHObject::getHasEditDlg()
{
    //try to init the dialog, only if it does not exists
    if (!m_edit_dlg)
    {
       ccConsole::PrintDebug("trying to intiialize dialog, it does not exists yet");
        initEditDlg();
    }

    //see if the dialog has been init
    if (!m_edit_dlg)
    {
        ccConsole::PrintDebug("the dialog still do not exist, have you implemented the initEditDlg method?");
        return false;
    }

    else
        return true;
}

void ccEditableHObject::showEditDlg()
{
    if (getHasEditDlg())
    {
        updateEditDlg(); // do the update
        if (m_edit_dlg_is_freezes_ui)
        {
            //                    vombat::theInstance()->getMainAppInterface()->freezeUI(true);
            m_edit_dlg->show();
        }
        else
            m_edit_dlg->show(); // then show it
    }
}

void ccEditableHObject::setEditDlgsFreezesUi(bool status)
{
    m_edit_dlg_is_freezes_ui = status;
}

void ccEditableHObject::initEditDlg()
{
    ccConsole::Print( "ccEditableHObject initEditDlg called... are you sure?" );
}
