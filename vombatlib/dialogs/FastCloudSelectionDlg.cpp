
#include "FastCloudSelectionDlg.h"
#include "ui_FastCloudSelectionDlg.h"

#include <ccHObject.h>
#include <ccConsole.h>

#include <iostream>


FastCloudSelectionDlg::FastCloudSelectionDlg(QWidget *parent) :
    ui(new Ui::FastCloudSelectionDlg)
{

    m_selected_object_id = -1;
    ui->setupUi(this);

    connect(this, SIGNAL(accepted()) , this, SLOT(readSelection()) );

}

FastCloudSelectionDlg::~FastCloudSelectionDlg()
{
    delete ui;
}

void
FastCloudSelectionDlg::updateList(ccHObject::Container list)
{    

    if(!(ui->objects_list))
    {
        std::cout << " It does not exists " << std::endl;
    }
    std::cout << "updating list wit  "  << list.size() << " elements" << std::endl;
    ui->objects_list->clear();
    for (int i = 0; i < list.size(); ++i)
    {
        std::cout << " ecco " << std::endl;
        std::cout << "list element: " << i << " named " << list.at(i)->getName().toStdString().c_str() << std::endl;

        ui->objects_list->addItem(list.at(i)->getName());
    }
    std::cout << "done!" << std::endl;

    m_current_list = list;
}

void FastCloudSelectionDlg::clearList()
{
    ui->objects_list->clear();
}

void
FastCloudSelectionDlg::readSelection()
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



