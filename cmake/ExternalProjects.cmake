include(ExternalProject)
ExternalProject_Add(
  QtPropertyBrowser

  GIT_REPOSITORY "git@github.com:commontk/QtPropertyBrowser.git"
  GIT_TAG "master"

  UPDATE_COMMAND ""
  PATCH_COMMAND ""

  SOURCE_DIR "${CMAKE_SOURCE_DIR}/3rdparty/QtPropertyBrowser"
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/3rdparty/QtPropertyBrowser

  TEST_COMMAND ""
)

#ExternalProject_Add_Step(
#  QtPropertyBrowser CopyToBin
##  COMMAND ${CMAKE_COMMAND} -E copy_directory ${GLOBAL_OUTPUT_PATH}/humblelogging/bin ${GLOBAL_OUTPUT_PATH}
##  COMMAND ${CMAKE_COMMAND} -E copy_directory ${GLOBAL_OUTPUT_PATH}/humblelogging/lib ${GLOBAL_OUTPUT_PATH}
#  DEPENDEES install
#)

#set(HumbleLogging_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/3rdparty/humblelogging/include")
#set(HumbleLogging_LIBRARIES "${CMAKE_SHARED_LIBRARY_PREFIX}humblelogging${CMAKE_SHARED_LIBRARY_SUFFIX}")
#include_directories(${HumbleLogging_INCLUDE_DIRS})


#include(ExternalProject)
#set(ExternalProjectCMakeArgs
#    -DCMAKE_INSTALL_PREFIX=${CMAKE_SOURCE_DIR}/external
#    -DCMAKE_Fortran_COMPILER=${CMAKE_Fortran_COMPILER}
#    -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
#    -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
#    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
#    -DCBLAS_ROOT=${CBLAS_ROOT}
#    -DEIGEN3_ROOT=${EIGEN3_ROOT}
#    )

#add_external(QtPropertyBrowser)
#add_dependencies(vombat QtPropertyBrowser)

set(QtPropertyBrowser_DIR ${CMAKE_CURRENT_BINARY_DIR}/3rdparty/QtPropertyBrowser)
find_package(QtPropertyBrowser)
include_directories(${QtPropertyBrowser_INCLUDE_DIRS})
link_directories(${QtPropertyBrowser_LIBRARY_DIRS})
