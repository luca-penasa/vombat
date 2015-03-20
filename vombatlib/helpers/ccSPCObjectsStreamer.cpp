#include "ccSPCObjectsStreamer.h"

#include <iostream>

void ccSPCObjectsStreamer::WriteToQFile(const spc::ISerializable::Ptr obj, QFile &file)
{
    std::cout << "writing to file" << std::endl;
    std::stringstream stream;
    spc::io::serializeToStream(obj, stream, spc::io::SPC);
    size_t s = ( size_t ) stream.str().size();
    file.write((char*)&s, sizeof(size_t));
    file.write(stream.str().data(), stream.str().size());
        std::cout << "written to file" << std::endl;
}

spc::ISerializable::Ptr ccSPCObjectsStreamer::ReadFromQFile(QFile &file)
{
    size_t obj_size;
    file.read((char *)&obj_size, sizeof(size_t));
    std::string string;
    string.resize(obj_size);
    file.read(&(*string.begin()), obj_size);

    return spc::io::deserializeFromString(string, spc::io::SPC);
}
