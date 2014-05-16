cmake_minimum_required (VERSION 2.8)
project( VOMBATLIB )

#requires PCL
find_package(PCL REQUIRED)

if( NOT MSVC )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -lpthread" )
endif()

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )
include_directories( ${CloudComparePlugins_SOURCE_DIR} )
include_directories( ${CMAKE_CURRENT_BINARY_DIR} )
include_directories( ${EXTERNAL_LIBS_INCLUDE_DIR} )
include_directories( ${CC_CORE_LIB_SOURCE_DIR}/include )
include_directories( ${QCC_DB_LIB_SOURCE_DIR} )
if( MSVC )
  include_directories( ${QCC_DB_LIB_SOURCE_DIR}/msvc )
endif()

include_directories(${PCL_INCLUDE_DIRS})



file( GLOB_RECURSE header_list ccoutofcore/*.h external/*.h dialogs/*.h plotter2d/*.h tools/*.h visualization/*.h helpers/*.h)
file( GLOB_RECURSE source_list ccoutofcore/*.cpp external/*.cpp dialogs/*.cpp plotter2d/*.cpp tools/*.cpp visualization/*.cpp helpers/*.cpp)
file( GLOB_RECURSE impl_list ccoutofcore/*.hpp external/*.hpp dialogs/*.hpp  plotter2d/*.hpp tools/*.hpp visualization/*.hpp helpers/*.hpp)
file( GLOB_RECURSE ui_list dialogs/*.ui visualization/*.ui helpers/*.ui)
#file( GLOB qrc_list icons/*.qrc )
#file( GLOB rc_list *.rc )


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ccoutofcore)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/dialogs)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/plotter2d)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/tools)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/visualization)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/helpers)

#for mocked files and ui_
include_directories(${CMAKE_CURRENT_BINARY_DIR}/ccoutofcore)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/dialogs)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/plotter2d)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/tools)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/visualization)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/helpers)


# find Qt mocable files
find_mocable_files( mocable_list ${header_list} )
qt4_wrap_cpp( moc_list ${mocable_list} )
QT4_WRAP_UI( generated_ui_list ${ui_list} )
#QT4_ADD_RESOURCES( generated_qrc_list ${qrc_list} )

add_library( ${PROJECT_NAME} STATIC ${header_list} ${source_list} ${impl_list} ${moc_list} ${generated_ui_list} )

# Default preprocessors
set_default_cc_preproc( ${PROJECT_NAME} )


# Add custom prepocessor definitions
if (WIN32)
	set_property( TARGET ${PROJECT_NAME} APPEND PROPERTY COMPILE_DEFINITIONS CC_USE_AS_DLL QCC_DB_USE_AS_DLL )
endif()

#define the PCL_VER_1_6_OR_OLDER preprocessor to compile qPCL with older versions of PCL
if ( PCL_VERSION VERSION_LESS  1.7 ) # VERSION_GREATER Works just like "greater or equal"
        set_property( TARGET ${PROJECT_NAME} APPEND PROPERTY COMPILE_DEFINITIONS PCL_VER_1_6_OR_OLDER )
endif()

# Luca's PCL patch support
if( PCL_VERSION VERSION_GREATER  1.7 ) #from 1.7 the patch was merged
	set_property( TARGET ${PROJECT_NAME} APPEND PROPERTY COMPILE_DEFINITIONS LP_PCL_PATCH_ENABLED )
endif()

link_directories( ${PCL_LIBRARY_DIRS} )
add_definitions( ${PCL_DEFINITIONS} )
target_link_libraries( ${PROJECT_NAME} ${PCL_LIBRARIES} ${EXTERNAL_LIBS_LIBRARIES})