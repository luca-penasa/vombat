#ifndef SCALAR_FIELD_COMBO_BOX_H
#define SCALAR_FIELD_COMBO_BOX_H


#include <QComboBox>
#include <ccPointCloud.h>
#include <iostream>
#include <fstream>

class QString;



//to help keeping track of the selected item and its meaning
struct ComboItemDescriptor
{
    enum allowed_types {SCALAR, COORDINATE, RGB};
    QString name;
    int index_in_cloud;
    int index_in_combo;
    allowed_types type;

    friend std::ostream& operator<<(std::ostream& stream,ComboItemDescriptor ob);


};


class ScalarFieldsComboBox: public QComboBox
{
    Q_OBJECT

public:
    ScalarFieldsComboBox(QWidget * parent = 0) : QComboBox(parent) {}

    void addItemsFromFieldsCloud(const ccPointCloud * cloud);

    void addCommonFieldsFromClouds(const ccPointCloud * cloud);


    void addItemsXYZ();

    void addItemsRGB(bool add_also_composite=true);

    std::string getSelectedFiedName() const;


};




std::vector<float> getComboItemAsStdFloatVector(ComboItemDescriptor desc, const ccPointCloud * cloud);




Q_DECLARE_METATYPE (ComboItemDescriptor)



#endif //Q_PCL_PLUGIN_QTHELPER_H
