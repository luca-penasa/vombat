#include "ScalarFieldsComboBox.h"
#include <boost/graph/graph_concepts.hpp>
#include <boost/foreach.hpp>

std::ostream&  operator<<(std::ostream& stream,ComboItemDescriptor ob)
{
    stream<< "name: " <<ob.name.toStdString()<<"  cloud_id: "<<ob.index_in_cloud<<"  combo_id: "<<ob.index_in_combo<< "  type: " << ob.type << '\n';
    return stream;
}

std::vector<float> getComboItemAsStdFloatVector(ComboItemDescriptor desc, const ccPointCloud* cloud)
{
    int n = cloud->size();
    std::vector<float> v;
    v.resize(n);
    v.reserve(n);
    if (desc.type == ComboItemDescriptor::COORDINATE)
    {
        CCVector3 point;
        for (int i = 0; i < n; i++)
        {
            cloud->getPoint(i, point);
            v[i] = point[desc.index_in_cloud];
        }
    }
    else if (desc.type == ComboItemDescriptor::SCALAR)
    {
        CCLib::ScalarField * field = cloud->getScalarField(desc.index_in_cloud);
        for (int i = 0; i < n; i++)
            v[i] = field->getValue(i);

    }


    return v;
}

void ScalarFieldsComboBox::addItemsFromFieldsCloud(const ccPointCloud * cloud)
{

    const int n = cloud->getNumberOfScalarFields();
    for (int i = 0; i < n ; i++)
    {
        ComboItemDescriptor desc;
        desc.name = cloud->getScalarFieldName(i);
        desc.index_in_cloud = i;
        desc.type = desc.SCALAR;
        desc.index_in_combo  = this->count() + 1;

        //put in a qVariant
        QVariant data;
        data.setValue(desc);

        this->addItem(desc.name, data);
    }
}

void ScalarFieldsComboBox::addItemsXYZ()
{
    QStringList list;
    list.reserve(3);
    list.append("X Coord");
    list.append("Y Coord");
    list.append("Z Coord");

    for (int i =0; i < list.size(); ++i)
    {
        ComboItemDescriptor desc;
        desc.name = list.at(i);
        desc.index_in_cloud = i;
        desc.index_in_combo = this->count()  + 1;
        desc.type = desc.COORDINATE;

        QVariant data;
        data.setValue(desc);
        
        this->addItem(list.at(i), data);
    }
}

void ScalarFieldsComboBox::addItemsRGB(bool add_also_composite)
{

    QStringList list;
    if (add_also_composite)
        list.reserve(4);
    else
        list.reserve(3);

    list.append("R Color");
    list.append("G Color");
    list.append("B Color");
    if (add_also_composite)
        list.append("RGB Composite");


    for (int i =0; i < list.size(); ++i)
    {
        ComboItemDescriptor desc;
        desc.name = list.at(i);
        desc.index_in_cloud = i;
        desc.index_in_combo = this->count()  + 1;
        desc.type = desc.RGB;

        QVariant data;
        data.setValue(desc);
        
        this->addItem(list.at(i), data);
    }
}

std::string ScalarFieldsComboBox::getSelectedFiedName() const
{
    QString name = this->itemText(this->currentIndex());

    return name.toStdString();
}

