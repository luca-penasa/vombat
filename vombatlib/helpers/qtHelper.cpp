#include "qtHelper.h"
#include <boost/graph/graph_concepts.hpp>
#include <boost/foreach.hpp>
#include <spc/methods/common.h>

int
ccVector3fromQstring(QString &string, CCVector3 &vector_output, QString separator)
{

    QStringList splitted = string.split(separator);

    //check size
    if (splitted.size() < 3)
        return -1;

    bool *ok = new bool;
    *ok = true;
    for (int i = 0; i < 3; ++i)
    {
        vector_output[i] = splitted.at(i).toFloat(ok);
        if (!ok)
            return -1;
    }

    return 1;
}

bool isLastOfListAnInteger(QStringList list, int &number)
{
    QString last_string = list.at(list.size()-1).trimmed();
    bool ok (false);
    number = last_string.toInt(&ok);
    return ok;
}

QString suggestScalarFieldIncrementalName(const ccPointCloud * cloud, QString name)
{
    while (cloud->getScalarFieldIndexByName(name.toStdString().c_str()) >= 0) // meaning this name yet exists
    {
        // suggest a new incremental name please
        name = suggestNextIncrementalName(name);
    }
    return name;
}

QString suggestNextIncrementalName(QString name)
{
    int number;
    //try split with a space
    QStringList list = name.trimmed().split(" ");


    if (isLastOfListAnInteger(list, number))
    {
        list.removeLast();
        name = list.join(" ");
        QString id = QString().setNum(number + 1);
        return name + QString(" ") + id;
    }

    //try another split
    list = name.split("_");
    if (isLastOfListAnInteger(list, number))
    {
        list.removeLast();
        name = list.join("_");
        QString id = QString().setNum(number + 1);
        return name + QString("_") + id;
    }

    //try another split
    list = name.split("-");
    if (isLastOfListAnInteger(list, number))
    {
        list.removeLast();
        name = list.join("-");
        QString id = QString().setNum(number + 1);
        return name + QString("-") + id;
    }

    //if we are here no good splits have been found.
    //So simply give a new name
    QString id = QString().setNum(1).trimmed();
    name += QString("_") + id;
    std::cout << name.toStdString() << std::endl;
    return name;



}





QString suggestHObjectIncrementalName(const ccHObject * object, QString name)
{
    ccHObject * parent = object->getParent();
    if (!parent)
        return name;

    int child_n = parent->getChildrenNumber();

    int id = 0;
    while (id < child_n)
    {
        ccHObject * this_child = parent->getChild(id++);

        if (this_child->getName() == name)
            // suggest a new incremental name please
            name = suggestNextIncrementalName(name);

        //else do nothing
    }
    return name;
}
