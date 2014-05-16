#include "qtHelper.h"
#include <boost/graph/graph_concepts.hpp>
#include <boost/foreach.hpp>


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
    QString last_string = list.at(list.size()-1);
    bool * ok = new bool;
    number = last_string.toInt(ok);
    return *ok;
}

QString suggestIncrementalName(QString name)
{
    int number;
    //try split with a space
    QStringList list = name.split(" ");
    if (isLastOfListAnInteger(list, number));
    {
        QString id = QString().setNum(number + 1);
        return name + QString(" ") + QString(id + 1);
    }

    //try another split
    list = name.split("_");
    if (isLastOfListAnInteger(list, number));
    {
        QString id = QString().setNum(number + 1);
        return name + QString("_") + QString(id + 1);
    }

    //try another split
    list = name.split("-");
    if (isLastOfListAnInteger(list, number));
    {
        QString id = QString().setNum(number + 1);
        return name + QString("-") + QString(id + 1);
    }

    //if we are here no good splits have been found.
    //So simply give a new name
    QString id = QString().setNum(1);
    return name + QString("_") + QString(1);

}



