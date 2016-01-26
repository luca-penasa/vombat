#ifndef NEWOBJECTSELECTIONCOMBOBOX_H
#define NEWOBJECTSELECTIONCOMBOBOX_H

#include <QComboBox>

#include <ccPointCloud.h>


class NewObjectSelectionComboBox: public QComboBox
{
    Q_OBJECT
public:

    NewObjectSelectionComboBox(QWidget * parent =0);

    void addShownType(CC_CLASS_ENUM type);


    void setOnlySelected(const bool & status);


//    void setObjects(const ccHObject::Container & objs);

    ccHObject * getSelectedObject();

    ccHObject::Container  getChildrenOfSelectedObject(const CC_CLASS_ENUM type, bool recursive = false, bool strict=true);

public slots:
    void selectionChanged(ccHObject::Container & sel);

    ccHObject::Container performFiltering();

    void updateItems();

private:
    bool exclude_root = true;

    bool only_selected = false;

    bool strict_type = true;

//    bool all_types = true;

    std::vector<CC_CLASS_ENUM> shown_types;


};
#endif // NEWOBJECTSELECTIONCOMBOBOX_H
