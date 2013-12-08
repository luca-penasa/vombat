cmake_minimum_required(VERSION 2.8)
project(qGEO)

include(cmake/macros.cmake)


set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -std=c++11 -fopenmp -fPIC" )

add_definitions(-DQGEO)


########################## USER-OPTIONS ############################
set(CC_BUILD_DIR "/home/luca/Code/CC_git_clean/build" CACHE STRING "Dir with CloudCompare build")
set(CC_SOURCE_DIR "/home/luca/Code/CC_git_clean" CACHE STRING "Dir with CloudCompare souces")
set(QGEO_INSTALL_DIR "/home/luca/apps/bin/plugins" CACHE STRING "Where to intall the qGEO plugin")
####################################################################


#################### SPC ###########################################
find_package(SPC 0.1.0 REQUIRED)

include_directories(${SPC_INCLUDE_DIRS})
link_directories(${SPC_LIBRARY_DIRS})
####################################################################


################### PCL #############################################
find_package(PCL 1.2 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

########################################################################


################### QT4 ##################################################
find_package(Qt4 4 COMPONENTS REQUIRED)
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
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/tools)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/visualization)


#for mocketized files
include_directories(${CMAKE_CURRENT_BINARY_DIR}/tools)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/tools/dialogs)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/visualization)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

#################################################################

add_subdirectory(tools)
add_subdirectory(visualization)


#file( GLOB header_list *.h)
#file( GLOB source_list *.cpp)
#file( GLOB ui_list *.ui )
#file( GLOB qrc_list *.qrc )
#file( GLOB rc_list *.rc )

set(header_list qGEO.h)
set(source_list qGEO.cpp)
set(qrc_list qGEO.qrc)

# find Qt mocable files
#find_mocable_files( mocable_list ${header_list} )
qt4_wrap_cpp( moc_list ${header_list} )
#QT4_WRAP_UI( generated_ui_list ${ui_list} )
QT4_ADD_RESOURCES( generated_qrc_list ${qrc_list} )


add_library( ${PROJECT_NAME} SHARED ${header_list} ${source_list} ${moc_list} ${generated_qrc_list})

target_link_libraries(${PROJECT_NAME} PclUtils qGEOTools qGEOVis ${SPC_LIBRARIES} ${PCL_LIBRARIES} ${QT_LIBRARIES} boost_serialization)

install(TARGETS ${PROJECT_NAME} DESTINATION ${QGEO_INSTALL_DIR})
