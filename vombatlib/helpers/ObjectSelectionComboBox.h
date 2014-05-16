#ifndef OBJECT_SELECTION_COMBO_BOX_H
#define OBJECT_SELECTION_COMBO_BOX_H


#include <QComboBox>
#include <ccPointCloud.h>
#include <iostream>
#include <fstream>

class QString;


class ObjectSelectionComboBox: public QComboBox
{
    Q_OBJECT

public:
    ObjectSelectionComboBox(QWidget * parent =0);

    void updateObjects(ccHObject::Container & cont);

    void setNone(bool has) {m_has_none = has;}

    bool hasNone() const {return m_has_none;}

    bool isPresentObjectWithID(const int id, int &position) const;

    // if none -> void
    ccHObject * getSelected() const;

public slots:
    void updateCurrentSelectionInfo(int id);


private:
    bool m_has_none;

    int m_old_selected_id;

    /// where we keep a copy of the full container, for easy retrieving
    ccHObject::Container m_container;

};





#endif //Q_PCL_PLUGIN_QTHELPER_H
