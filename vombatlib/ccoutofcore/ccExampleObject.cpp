#include "ccExampleObject.h"
#include <iostream>

#include <helpers/ccSPCObjectsStreamer.h>
#include <ccGenericGLDisplay.h>

#include <spc/elements/ElementBase.h>

ccExampleObject::ccExampleObject(spc::ElementBasePtr obj)
    : ccSPCElementShell(obj)
{
}
