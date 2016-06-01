#pragma once
#ifndef CCEDITABLEHOBJECT_H
#define CCEDITABLEHOBJECT_H

class QDialog;

class ccEditableHObject
{
//    Q_GADGET

public:
    ccEditableHObject();

    //destructor
    ~ccEditableHObject();

    bool getHasEditDlg();

    virtual void showEditDlg();

    void setEditDlgsFreezesUi(bool status);

protected:
    QDialog * m_edit_dlg;

    ///
    /// \brief initEditDlg is the only method you MUST reimplement in subclasses
    ///         if you want to hve a dlg
    ///
    virtual void initEditDlg();

    ///
    /// \brief updateEditDlg some objects may need to do somethin before to show the dialog
    /// as re-read the dbtree and update comboBoxes etc...
    ///
    virtual void updateEditDlg()
    {
        // nothing by def
    }

    bool m_edit_dlg_is_freezes_ui;



};

#endif // CCEDITABLEHOBJECT_H
