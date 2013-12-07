cmake_minimum_required(VERSION 2.8)
project(qGEO)

set(CC_BUILD_DIR "/home/luca/Code/CC_git_clean/build" CACHE STRING "Dir with CloudCompare build")
set(CC_SOURCE_DIR "/home/luca/Code/CC_git_clean" CACHE STRING "Dir with CloudCompare souces")
set(QGEO_INSTALL_DIR "/home/luca/apps/bin/plugins" CACHE STRING "Where to intall the qGEO plugin")


###### we need to write a Find Module for doing this thing #########
set(SPC_INCLUDES_DIRS "/home/luca/apps/include" CACHE STRING "SPC includes")
#set(SPC_LIBRARIES "spc_common spc_devices spc_elements spc_estimators spc_geology spc_io spc_methods spc_statigraphy spc_time_series" CACHE STRING "SPC libraries to link with")
set(SPC_LIBRARY_DIRS "/home/luca/apps/lib" CACHE STRING "SPC linking dir")

include_directories(${SPC_INCLUDES_DIRS})
link_directories(${SPC_LIBRARY_DIRS})



find_library(SPC_LIBRARIES NAMES spc_common spc_devices spc_elements spc_estimators spc_geology spc_io spc_methods spc_statigraphy spc_time_series
             HINTS ${SPC_LIBRARY_DIRS} )

#message("${SPC_LIBRARIES}")




####################################################################

find_package(PCL 1.2 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})


include_directories(${CMAKE_CURRENT_SOURCE_DIR})



add_definitions(-DQGEO)

find_package(Qt4 4 COMPONENTS REQUIRED)
set(QT_USE_QTOPENGL TRUE)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})
include_directories(${QT_QTOPENGL_INCLUDE_DIR})


include_directories(${CC_SOURCE_DIR}/libs/qCC_db)
include_directories(${CC_SOURCE_DIR}/CC/include)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})



set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -std=c++11 -fopenmp -fPIC" )
include(${CC_SOURCE_DIR}/CMakeInclude.cmake)
include(${CC_SOURCE_DIR}/CMakeExternalLibs.cmake)




set(CC_PLUGINS_SOURCE_DIR "${CC_SOURCE_DIR}/qCC/plugins")
set(CC_PLUGINS_BUILD_DIR "${CC_BUILD_DIR}/qCC/plugins")

link_directories(${CC_BUILD_DIR}/qCC/plugins/qPCL/PclUtils/)



#for mocketized files
include_directories(${CMAKE_CURRENT_BINARY_DIR}/tools)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/tools/dialogs)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/visualization)
include_directories(${CMAKE_CURRENT_BINARY_DIR})


include_directories(${SPC_BUILD_INCLUDE_DIRS})


include_directories(${CC_SOURCE_DIR}/libs/qCC_db/)
include_directories(${CC_SOURCE_DIR}/qCC/db_tree/)

include_directories(${CC_SOURCE_DIR}/qCC/)
include_directories(${CC_SOURCE_DIR}/qCC/dialogs)

include_directories(${CC_PLUGINS_SOURCE_DIR})




include_directories(${CC_BUILD_DIR}/qCC) #for mocketized files that cc created

include_directories(${CC_PLUGINS_SOURCE_DIR}) # in this way we can get acces to headers from other plugins
include_directories(${CC_SOURCE_DIR}/CC/include/)
#include_directories(${QGEO_PLUGIN_DLL_BINARY_DIR}/geoutils) #for including moc'ed headers

include_directories(tools)
#include_directories(${QPCL_PLUGIN_DLL_SOURCE_DIR}/../) #for accessing other plugins headers


add_subdirectory(tools)
add_subdirectory(visualization)


file( GLOB header_list *.h)
file( GLOB source_list *.cpp)
file( GLOB ui_list *.ui )
file( GLOB qrc_list *.qrc )
file( GLOB rc_list *.rc )

# find Qt mocable files
find_mocable_files( mocable_list ${header_list} )
qt4_wrap_cpp( moc_list ${mocable_list} )
QT4_WRAP_UI( generated_ui_list ${ui_list} )
QT4_ADD_RESOURCES( generated_qrc_list ${qrc_list} )


add_library( ${PROJECT_NAME} SHARED ${header_list} ${source_list} ${moc_list} ${generated_ui_list} ${generated_qrc_list})

target_link_libraries(${PROJECT_NAME} PclUtils qGEOTools qGEOVis ${SPC_LIBRARIES} ${QT_LIBRARIES} boost_serialization)

install(TARGETS ${PROJECT_NAME} DESTINATION ${QGEO_INSTALL_DIR})
