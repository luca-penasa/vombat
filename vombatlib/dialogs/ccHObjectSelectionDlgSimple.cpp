
#include "ccHObjectSelectionDlgSimple.h"
#include "ui_ccHObjectSelectionDlgSimple.h"
#include <ccHObject.h>
#include <ccConsole.h>

#include <iostream>


ccHObjectSelectionDlgSimple::ccHObjectSelectionDlgSimple(QWidget *parent) :
    ui(new Ui::ccHObjectSelectionDlgSimple)
{

    m_selected_object_id = -1;
    ui->setupUi(this);

    connect(this, SIGNAL(accepted()) , this, SLOT(readSelection()) );

}

ccHObjectSelectionDlgSimple::~ccHObjectSelectionDlgSimple()
{
    delete ui;
}

void
ccHObjectSelectionDlgSimple::updateList(ccHObject::Container list)
{    

    if(!(ui->objects_list))
    {
        return;
    }

    ui->objects_list->clear();
    for (int i = 0; i < list.size(); ++i)
    {
        ui->objects_list->addItem(list.at(i)->getName());
    }

    m_current_list = list;
}

void ccHObjectSelectionDlgSimple::clearList()
{
    ui->objects_list->clear();
}

void
ccHObjectSelectionDlgSimple::readSelection()
{
    QModelIndexList selected_items = ui->objects_list->selectionModel()->selectedIndexes();
    if (selected_items.size() != 1)
    {
        return;
    }
    if (selected_items.size() == 0)
    {
        return;
    }

    m_selected_object_id = selected_items.at(0).row();

}



