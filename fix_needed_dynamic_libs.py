executable = "CloudCompare.exe"
dll_dir =  "/mxe.git/"

import fnmatch
import os
import subprocess
import re
import shutil


files = ["Qt5Concurrent.dll",
"Qt5Core.dll",
"Qt5Gui.dll",
"Qt5OpenGL.dll",
"Qt5PrintSupport.dll",
"Qt5Svg.dll",
"Qt5Widgets.dll",
"libboost_filesystem-mt.dll",
"libboost_regex-mt.dll",
"libboost_system-mt.dll",
"libbz2.dll",
"libfreetype-6.dll",
"libgcc_s_seh-1.dll",
"libbgomp-1.dll",
"libharfbuzz-0.dll",
"libiconv-2.dll",
"libintl-8.dll",
"libjasper-1.dll",
"libjpeg-9.dll",
"liblcms2-2.dll",
"liblzma-5.dll",
"libmng-2.dll",
"libpcre-1.dll",
"libpcre16-0.dll",
"libpng16-16.dll",
"libstdc++-6.dll",
"libtiff-5.dll",
"libwebp-5.dll",
"libwebpdemux-1.dll",
"libwinpthread-1.dll",
"zlib1.dll"]




def find_file (srcdir, pattern):
    matches = []
    for root, dirnames, filenames in os.walk(srcdir):
        for filename in fnmatch.filter(filenames, pattern):
            matches.append(os.path.abspath(os.path.join(root, filename)))

    return matches


found = find_file("./", executable)[0]

exedir = os.path.dirname(found)



for dll in files:
    print ("looking for " + str(dll))
    qua = find_file(dll_dir, dll)

    if len(qua) == 0:
        print("-------> cannot find file " + str(dll))
        continue

    print ("copying " + str(qua[0]))
    print( "copying in  " + str(exedir))


    shutil.copy2 (qua[0], exedir)
