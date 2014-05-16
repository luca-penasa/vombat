#ifndef VOMBAT_PLUGIN_QTHELPER_H
#define VOMBAT_PLUGIN_QTHELPER_H


#include <QComboBox>
#include <ccPointCloud.h>
#include <iostream>
#include <fstream>

class QString;




QString suggestIncrementalName(QString name);

bool isLastOfListAnInteger(QStringList list, int &number);


int ccVector3fromQstring(QString &string, CCVector3 &output_vector, QString separator = " ");


#endif //Q_PCL_PLUGIN_QTHELPER_H
