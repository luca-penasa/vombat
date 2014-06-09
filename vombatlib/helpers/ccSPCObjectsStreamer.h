#ifndef CCSPCOBJECTSSTREAMER_H
#define CCSPCOBJECTSSTREAMER_H

#include <QFile>
#include <spc/io/element_io.h>
#include <sstream>
class ccSPCObjectsStreamer
{
public:


    static void WriteToQFile(const spc::ISerializable::Ptr obj, QFile & file);

    static spc::ISerializable::Ptr ReadFromQFile( QFile & file);
};

#endif // CCSPCOBJECTSSTREAMER_H
