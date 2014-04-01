cmake_minimum_required(VERSION 2.8)
project(vombat)

include(cmake/macros.cmake) # load some macros

option(BUILD_WITH_CLANG "Build vombat plugin using clang isntead of gcc. it is EXPERIMENTAL stuff!" OFF)
if(BUILD_WITH_CLANG)
    message("Using Clang as compiler! This may not work properly")
    set(CMAKE_C_COMPILER "clang")
    set(CMAKE_CXX_COMPILER "clang++")
endif()


#FIND_PACKAGE( OpenMP REQUIRED)
#if(OPENMP_FOUND)
#    message("OPENMP FOUND")
#    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
#    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
#endif()

#add_definitions("") # not needed for now

set(VOMBAT_MODULES) #this will be populated with all the modular libs needed by vombat
set(VOMBAT_INCLUDE_DIRS) # and this with the include directories

# finding cloudcompare things
# set(CCP_DIR "/home/luca/Code/CloudCompare-git/build" CACHE STRING "Dir with CloudCompare config file")
find_package(CCP REQUIRED) # CloudCompareProjects
include_directories(${CCP_INCLUDE_DIRS})

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ${CCP_CXX_FLAGS}"  )


# verify if qPCL plugin was compiled or not
if(NOT TARGET QPCL_PLUGIN)
    message( FATAL_ERROR "CloudCompare must be compiled with qPCL plugin enabled for vombat to work")
endif()


#################### SPC ###########################################
#it also automatically find PCL and other required libraries
find_package(SPC 0.1.0 REQUIRED)
include_directories(${SPC_INCLUDE_DIRS})
message(${SPC_INCLUDE_DIRS})
link_directories(${SPC_LIBRARY_DIRS})
add_definitions(${SPC_DEFINITIONS})
####################################################################

# standard includes
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# make vombat aware of all the subdirs
add_vombat_subdir(tools)
add_vombat_subdir(visualization)
add_vombat_subdir(ccoutofcore)
add_vombat_subdir(dialogs)
add_vombat_subdir(plotter2d)

# now we can perform includes
include_directories("${VOMBAT_INCLUDE_DIRS}")

# and now also add-subdirectories
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


add_library( ${PROJECT_NAME} SHARED ${header_list} ${source_list} ${moc_list} ${generated_qrc_list})

target_link_libraries(${PROJECT_NAME} ${CCP_LIBRARIES} ${SPC_LIBRARIES} ${VOMBAT_MODULES} ${QT_LIBRARIES} boost_serialization)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CCP_PLUGIN_INSTALL_DIR})


message("${CMAKE_CXX_FLAGS}" )
