cmake_minimum_required(VERSION 2.8)

option( INSTALL_vombat_PLUGIN "Check to install vombat plugin" OFF )

if (INSTALL_vombat_PLUGIN)


project(vombat)

set( CMAKE_VERBOSE_MAKEFILE on )


include(cmake/macros.cmake) # load some macros

if (USE_QT5)
    add_subdirectory(external/qtpropertybrowser_qt5)
    include_directories("external/qtpropertybrowser_qt5")
else()
    add_subdirectory(external/qtpropertybrowser_qt4)
    include_directories("external/qtpropertybrowser_qt4")
endif()

#find_package(QtPropertyBrowser)
#message("INCLUDE: ${QtPropertyBrowser_SOURCE_DIR}")
include_directories("external/qtpropertybrowser")
#link_directories(${QtPropertyBrowser_BINARY_DIR})


#add_subdirectory(external/spc)
#include_directories(external/spc)
#include_directories(external/spc/submodules/cereal/include)
#link_directories(${SPC_BINARY_DIR}/lib)

if(USE_QT5)
find_package(Qt5Widgets)
include_directories(${Qt5Widgets_INCLUDE_DIRS})
else()
FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})
endif()


include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )
include_directories( ${CMAKE_CURRENT_BINARY_DIR} )
include_directories( ${CloudComparePlugins_SOURCE_DIR} )
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/../../qCC")
include_directories( "${CMAKE_CURRENT_BINARY_DIR}/../../qCC")
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/../")
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/../../qCC/db_tree")
include_directories( "${CMAKE_CURRENT_BINARY_DIR}/../../qCC/db_tree")
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/qCC_io")
include_directories( "${CMAKE_CURRENT_BINARY_DIR}/../../libs/qCC_io")
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/qcustomplot")
include_directories( ${GLEW_LIB_SOURCE_DIR}/include )
include_directories( ${CC_FBO_LIB_SOURCE_DIR}/include )
include_directories( ${CC_CORE_LIB_SOURCE_DIR}/include )
include_directories( ${QCC_DB_LIB_SOURCE_DIR} )

include_directories("vombatlib/")
include_directories( "${CMAKE_CURRENT_BINARY_DIR}/vombatlib")
include_directories( "${CMAKE_CURRENT_BINARY_DIR}/vombatlib/dialogs")
include_directories( "${CMAKE_CURRENT_BINARY_DIR}/vombatlib/tools")



if( MSVC )
    include_directories( ${QCC_DB_LIB_SOURCE_DIR}/msvc )
endif()

include_directories( ${QCC_GL_LIB_SOURCE_DIR} )
include_directories( ${EXTERNAL_LIBS_INCLUDE_DIR} )


option(BUILD_WITH_CLANG "Build vombat plugin using clang isntead of gcc. it is EXPERIMENTAL stuff!" OFF)
if(BUILD_WITH_CLANG)
    message("Using Clang as compiler! This may not work properly")
    set(CMAKE_C_COMPILER "clang")
    set(CMAKE_CXX_COMPILER "clang++")
endif()

option(BUILD_VOMBAT_MONOLITHIC "Build vombat plugin all-in-one" OFF)


#FIND_PACKAGE( OpenMP REQUIRED)
#if(OPENMP_FOUND)
#    message("OPENMP FOUND")
#    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
#    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
#endif()

if (WIN32)
	add_definitions("-DNOMINMAX") 
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -wd4996") #pcl::SHOOT warn
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -wd4521") # pcl/eigen multiple copy constructors warn
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -wd4305") # some conversion / possible data-loss
else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated -Wno-narrowing")  #get rid of annoying warns
endif()

set(VOMBAT_MODULES) #this will be populated with all the modular libs needed by vombat
set(VOMBAT_INCLUDE_DIRS) # and this with the include directories

# finding cloudcompare things
#find_package(CCP REQUIRED) # CloudCompareProjects
#include_directories(${CCP_INCLUDE_DIRS})

#if( NOT MSVC )
#        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -lpthread " )
#endif()

#if (UNIX)
#        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x ${CCP_CXX_FLAGS} -Wno-narrowing"  )
#endif()


# verify if qPCL plugin was compiled or not
if(NOT TARGET QPCL_PLUGIN)
    message( FATAL_ERROR "CloudCompare must be compiled with qPCL plugin enabled for vombat to work")
endif()


#################### SPC ###########################################
#it also automatically find PCL and other required libraries
find_package(SPC 0.1.0 REQUIRED)
include_directories(${SPC_INCLUDE_DIRS})

link_directories(${SPC_LIBRARY_DIRS})
add_definitions(${SPC_DEFINITIONS})

message("spc includes: ${SPC_INCLUDE_DIRS}")
message("spc libs: ${SPC_LIBRARIES}")
####################################################################

find_package(PCL 1.6 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

# this is needed for being able to correctly include the pcl_plugin_utils_lib stuff
if( NOT PCL_VERSION VERSION_GREATER  1.7 ) #from 1.7 the patch was merged
	message(" PCL is ${PCL_VERSION} -> PCL is lower than 1.7")
	add_definitions( "-D PCL_VER_1_6_OR_OLDER" )
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/vombatlib/ccoutofcore)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/vombatlib/dialogs)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/vombatlib/plotter2d)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/vombatlib/tools)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/vombatlib/visualization)

#for mocked files and ui_
include_directories(${CMAKE_CURRENT_BINARY_DIR}/vombatlib/ccoutofcore)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/vombatlib/dialogs)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/vombatlib/plotter2d)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/vombatlib/tools)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/vombatlib/visualization)


# standard includes
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

include_directories(${VOMBATLIB_INCLUDE_DIRS})




################ PLUGIN ITSELF ############################
#set(header_list vombat.h)
#set(source_list vombat.cpp)
#set(qrc_list vombat.qrc)

#qt4_wrap_cpp( moc_list ${header_list} )
#QT4_ADD_RESOURCES( generated_qrc_list ${qrc_list} )
############################################################


if( NOT MSVC )
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -lpthread" )
endif()


add_subdirectory(vombatlib)

include( ../CMakePluginTpl.cmake )

#add_library( ${PROJECT_NAME} SHARED ${header_list} ${source_list} ${moc_list} ${generated_qrc_list})

#target_link_libraries(${PROJECT_NAME} ${PCL_LIBRARIES} ${SPC_LIBRARIES} VOMBATLIB ${QT_LIBRARIES})

target_link_libraries(${PROJECT_NAME} VOMBATLIB)

#target_link_libraries( ${PROJECT_NAME} CC_CORE_LIB )
#target_link_libraries( ${PROJECT_NAME} QCC_DB_LIB )

target_link_libraries( ${PROJECT_NAME} QPCL_PLUGIN_UTILS_LIB)

message( "${CMAKE_CXX_FLAGS}" )
ADD_DEPENDENCIES(  vombat CC_CORE_LIB QCC_DB_LIB QCC_GL_LIB QPCL_PLUGIN QCC_IO_LIB CloudCompare qcustomplot)


#add_subdirectory(tests)

endif() #main if ends here
