cmake_minimum_required(VERSION 2.8)

option( INSTALL_vombat_PLUGIN "Check to install vombat plugin" OFF )

if (INSTALL_vombat_PLUGIN)


project(vombat)

include(cmake/macros.cmake) # load some macros






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
include_directories( ${QCC_GL_LIB_SOURCE_DIR} )
include_directories( ${EXTERNAL_LIBS_INCLUDE_DIR} )


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




if (UNIX)
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}"   )
endif()







# standard includes
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})



#add_subdirectory(vombatlib)

include( ../CMakePluginTpl.cmake )

#add_library( ${PROJECT_NAME} SHARED ${header_list} ${source_list} ${moc_list} ${generated_qrc_list})

target_link_libraries(${PROJECT_NAME} ${PCL_LIBRARIES})

#target_link_libraries(${PROJECT_NAME} VOMBATLIB )

#target_link_libraries( ${PROJECT_NAME} CC_CORE_LIB )
#target_link_libraries( ${PROJECT_NAME} QCC_DB_LIB )

#target_link_libraries( ${PROJECT_NAME}  )

message( "${CMAKE_CXX_FLAGS}" )
#ADD_DEPENDENCIES(  vombat CC_CORE_LIB QCC_DB_LIB QCC_GL_LIB QPCL_PLUGIN QCC_IO_LIB CloudCompare qcustomplot)


#add_subdirectory(tests)

endif() #main if ends here
