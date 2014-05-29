
#include <boost/graph/graph_concepts.hpp>
#include <ObjectSelectionComboBox.h>

#include <spc/elements/macros.h>



ObjectSelectionComboBox::ObjectSelectionComboBox(QWidget *parent): QComboBox(parent), m_has_none(false), m_old_selected_id(-1)
{
    connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(updateCurrentSelectionInfo(int)));
}

void ObjectSelectionComboBox::updateObjects(ccHObject::Container &cont)
{
    int old_selected = m_old_selected_id; //first of all!

    if (cont.empty())
        return;
    //clear everything
    this->clear();

    m_container = cont;

    spcForEachMacro(ccHObject * obj , cont)
    {
        QString name = obj->getName();
        this->addItem(name);
    }

    if (this->hasNone())
        this->addItem("None"); // it correspond to -1 old id

    int position;
    if (isPresentObjectWithID(old_selected, position))
    {
        // restore it as selected
        this->setCurrentIndex(position);
    }
}

bool ObjectSelectionComboBox::isPresentObjectWithID(const int id, int &position) const
{
    position = 0;
    spcForEachMacro (ccHObject * obj, m_container)
    {
        if (obj->getUniqueID() == id)
        {
            return true;
        }
        position +=1;
    }



    return false;
}


ccHObject *ObjectSelectionComboBox::getSelected() const
{
    int id = this->currentIndex();

    if (id >= m_container.size())
        return 0;       

    return m_container.at(id);
}



void ObjectSelectionComboBox::updateCurrentSelectionInfo(int id)
{
    if (id >= m_container.size()) // is a None
        m_old_selected_id = -1;
    else
    {
        ccHObject * obj = m_container.at(id);
        m_old_selected_id = obj->getUniqueID();
    }
}
