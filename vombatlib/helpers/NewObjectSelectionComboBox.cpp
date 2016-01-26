#include "NewObjectSelectionComboBox.h"


#include <vombat.h>
#include <ccDBRoot.h>

NewObjectSelectionComboBox::NewObjectSelectionComboBox(QWidget *parent) : QComboBox(parent)
{
    connect(vombat::theInstance(), SIGNAL(selectionChanged(ccHObject::Container&)), this, SLOT(selectionChanged(ccHObject::Container&)));
    connect(vombat::theInstance()->getMainAppInterface()->db(), SIGNAL(elementAddedRemoved()), this, SLOT(updateItems()));


}


void NewObjectSelectionComboBox::addShownType(CC_CLASS_ENUM type)
{
    shown_types.push_back(type);
    updateItems();
}

void NewObjectSelectionComboBox::setOnlySelected(const bool &status)
{
    only_selected = status;
}



ccHObject *NewObjectSelectionComboBox::getSelectedObject()
{
    int sel_id = this->currentIndex();
    unsigned id = this->itemData(sel_id).toUInt();

    LOG(INFO) << "looking for the id " << id;

    ccHObject * obj = vombat::theInstance()->getMainAppInterface()->db()->find(id);



    return obj;
}

ccHObject::Container NewObjectSelectionComboBox::getChildrenOfSelectedObject(const CC_CLASS_ENUM type, bool recursive, bool strict)
{
    ccHObject::Container out;
    ccHObject * obj = this->getSelectedObject();
    if (!obj)
        return out;

    obj->filterChildren(out, recursive, type, strict);

    return out;
}



void NewObjectSelectionComboBox::selectionChanged(ccHObject::Container &sel)
{
    if (only_selected)
        updateItems();
}

ccHObject::Container NewObjectSelectionComboBox::performFiltering()
{
    ccHObject::Container out;
    ccHObject::Container starting_items;

    if (only_selected)
        starting_items =  vombat::theInstance()->getSelected();
    else
        starting_items = vombat::theInstance()->getAllObjectsInTree();



    if (shown_types.empty()) // showing everything
    {

        ccHObject::Container good  = starting_items;
        for(auto o: good)
        {
            if (exclude_root)
            {
                if (o == vombat::theInstance()->getMainAppInterface()->dbRootObject())
                    continue;
                else
                    out.push_back(o);
            }
            else
                out.push_back(o);
        }
    }
    else
    {
        for (auto T : shown_types)
        {
            ccHObject::Container good ;


            if (strict_type)
                good = vombat::filterObjectsByType(starting_items,  T);
            else
                good = vombat::filterObjectsByKind(starting_items,  T);

            for(auto o: good)
            {
                if (exclude_root)
                {
                    if (o == vombat::theInstance()->getMainAppInterface()->dbRootObject())
                        continue;
                    else
                        out.push_back(o);
                }
                else
                    out.push_back(o);
            }
        }

    }

    return out;




}

void NewObjectSelectionComboBox::updateItems()
{

    LOG(INFO) << "Updating items";

    this->clear();

    ccHObject::Container good = performFiltering();

    for (ccHObject * ob: good)
        this->addItem(ob->getName(), QVariant(ob->getUniqueID()));

}
