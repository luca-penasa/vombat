cmake_minimum_required(VERSION 2.8)

#option( INSTALL_vombat_PLUGIN "Check to install vombat plugin" OFF )

#include(CMakeDependentOption)
#CMAKE_DEPENDENT_OPTION(INSTALL_vombat_PLUGIN "Compile Vombat plugin" ON
#                         "INSTALL_QPCL_PLUGIN" OFF)

if (INSTALL_vombat_PLUGIN)


project(vombat)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


set( CMAKE_VERBOSE_MAKEFILE on )


include(cmake/macros.cmake) # load some macros

if(USE_QT5)
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


#################### SPC ###########################################
#it also automatically find PCL and other required libraries
find_package(SPC 0.1.0 REQUIRED)
include_directories(${SPC_INCLUDE_DIRS})

link_directories(${SPC_LIBRARY_DIRS})
add_definitions(${SPC_DEFINITIONS})

message("spc includes: ${SPC_INCLUDE_DIRS}")
message("spc libs: ${SPC_LIBRARIES}")
####################################################################



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


#set(needed_features
#    cxx_strong_enums
#    cxx_constexpr
#    cxx_auto_type)

#target_compile_features(${PROJECT_NAME} PRIVATE ${needed_features})



include( ../CMakePluginTpl.cmake )

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)


#add_library( ${PROJECT_NAME} SHARED ${header_list} ${source_list} ${moc_list} ${generated_qrc_list})

#target_link_libraries(${PROJECT_NAME} ${PCL_LIBRARIES} ${SPC_LIBRARIES} VOMBATLIB ${QT_LIBRARIES})

target_link_libraries(${PROJECT_NAME} VOMBATLIB)

#target_link_libraries( ${PROJECT_NAME} CC_CORE_LIB )
#target_link_libraries( ${PROJECT_NAME} QCC_DB_LIB )

#target_link_libraries( ${PROJECT_NAME} QPCL_PLUGIN_UTILS_LIB)

message( "cxx_flags are: ${CMAKE_CXX_FLAGS}" )
ADD_DEPENDENCIES(  vombat CC_CORE_LIB QCC_DB_LIB QCC_GL_LIB QPCL_PLUGIN QCC_IO_LIB CloudCompare qcustomplot)


#add_subdirectory(tests)

endif() #main if ends here



