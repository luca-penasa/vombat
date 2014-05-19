#ifndef FASTCLOUDSELECTIONDLG_H
#define FASTCLOUDSELECTIONDLG_H

#include <QDialog>

#include <ccHObject.h>

class ccHObject;

namespace Ui
{
    class ccHObjectSelectionDlgSimple;
}

class ccHObjectSelectionDlgSimple : public QDialog
{
    Q_OBJECT
    
public:
    explicit ccHObjectSelectionDlgSimple(QWidget *parent = 0);

    ~ccHObjectSelectionDlgSimple();

    void updateList(ccHObject::Container list);

    int getSelectedObjectIndex() {return m_selected_object_id;}

    ccHObject * getSelectedObject() const
    {
        return m_current_list.at(m_selected_object_id);
    }

    void clearList();

private slots:
    void readSelection();
    
private:
    Ui::ccHObjectSelectionDlgSimple *ui;
    int m_selected_object_id;

    ccHObject::Container m_current_list;
};

#endif // FASTCLOUDSELECTIONDLG_H
