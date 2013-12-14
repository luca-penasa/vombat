cmake_minimum_required(VERSION 2.8)
project(vombat)

include(cmake/macros.cmake)


#set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -std=c++0x -fopenmp -fPIC" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC" )

add_definitions("")

set(VOMBAT_MODULES) #this will collect all the modular libs needed by vombat
set(VOMBAT_INCLUDE_DIRS)


########################## USER-OPTIONS ############################
set(CC_BUILD_DIR "/home/luca/Code/CC_git_clean/build" CACHE STRING "Dir with CloudCompare build")
set(CC_SOURCE_DIR "/home/luca/Code/CC_git_clean" CACHE STRING "Dir with CloudCompare souces")
set(VOMBAT_INSTALL_DIR "/home/luca/apps/bin/plugins" CACHE STRING "Where to intall the vombat plugin")
####################################################################


#################### SPC ###########################################
#it also automatically find PCL and other required libraries
find_package(SPC 0.1.0 REQUIRED)
include_directories(${SPC_INCLUDE_DIRS})
message(${SPC_INCLUDE_DIRS})
link_directories(${SPC_LIBRARY_DIRS})
add_definitions(${SPC_DEFINITIONS})
####################################################################


################### QT4 ##################################################
find_package(Qt4 REQUIRED)
set(QT_USE_QTOPENGL TRUE)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})
include_directories(${QT_QTOPENGL_INCLUDE_DIR})
##########################################################################


######################## CLOUDCOMPARE THINGS ###########################
# it would be better to write down a CloudCompareConfig.cmake file to be
# integrated with the CC project

#include(${CC_SOURCE_DIR}/CMakeInclude.cmake)
#include(${CC_SOURCE_DIR}/CMakeExternalLibs.cmake)


#set(CC_PLUGINS_SOURCE_DIR "${CC_SOURCE_DIR}/qCC/plugins")
#set(CC_PLUGINS_BUILD_DIR "${CC_BUILD_DIR}/qCC/plugins")


set(CC_INCLUDE_DIRS    "${CC_SOURCE_DIR}/libs/qCC_db;
                        ${CC_SOURCE_DIR}/CC/include;
                        ${CC_SOURCE_DIR}/qCC/db_tree;
                        ${CC_SOURCE_DIR}/qCC;
                        ${CC_SOURCE_DIR}/qCC/dialogs;
                        ${CC_BUILD_DIR}/qCC;
                        ${CC_SOURCE_DIR}/qCC/plugins;
                        ${CC_BUILD_DIR}/qCC/plugins"}
)


set(CC_LIBRARIES_DIR "${CC_BUILD_DIR}/qCC/plugins/qPCL/PclUtils/")

include_directories(${CC_INCLUDE_DIRS})
link_directories(${CC_LIBRARIES_DIR})
###########################################################################


################## VOMBAT THINGS #################################
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#for mocketized files
include_directories(${CMAKE_CURRENT_BINARY_DIR})
#################################################################

#add_vombat_subdirectory(tools)
#add_vombat_subdirectory(visualization)

#message("** COMPILING WITH MODULES: ${VOMBAT_MODULES}")


#compile_vombat_submodule(tools)
#compile_vombat_submodule(visualization)

#link_install_vombat_submodule(tools)
#link_install_vombat_submodule(visualization)

add_vombat_subdir(tools)
add_vombat_subdir(visualization)
add_vombat_subdir(ccoutofcore)
add_vombat_subdir(dialogs)
add_vombat_subdir(plotter2d)


include_directories("${VOMBAT_INCLUDE_DIRS}")

add_subdirectory(tools)
add_subdirectory(visualization)
add_subdirectory(ccoutofcore)
add_subdirectory(dialogs)
add_subdirectory(plotter2d)





################ PLUGIN ITSELF ############################
set(header_list vombat.h)
set(source_list vombat.cpp)
set(qrc_list vombat.qrc)

qt4_wrap_cpp( moc_list ${header_list} )
QT4_ADD_RESOURCES( generated_qrc_list ${qrc_list} )
############################################################

message("modules: ${VOMBAT_MODULES}" )

add_library( ${PROJECT_NAME} SHARED ${header_list} ${source_list} ${moc_list} ${generated_qrc_list})

target_link_libraries(${PROJECT_NAME} PclUtils ${VOMBAT_MODULES} ${SPC_LIBRARIES} ${QT_LIBRARIES} boost_serialization)

install(TARGETS ${PROJECT_NAME} DESTINATION ${VOMBAT_INSTALL_DIR})


message("${CMAKE_CXX_FLAGS}" )
