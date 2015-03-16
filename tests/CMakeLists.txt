#FIND_PACKAGE(Qt4 REQUIRED)
#INCLUDE(${QT_USE_FILE})
#ADD_DEFINITIONS(${QT_DEFINITIONS})

#if (UNIX)
#        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ${CCP_CXX_FLAGS} "  )
#endif()

#if( NOT MSVC )
#        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -lpthread" )
#endif()




#add_executable(test1 compute_calibration_dataset.cpp)
#target_link_libraries(test1 ${SPC_LIBRARIES} ${PCL_LIBRARIES})


#target_link_libraries( test1 GLEW_LIB )
#target_link_libraries( test1 CC_FBO_LIB )
#target_link_libraries( test1 CC_CORE_LIB )
#target_link_libraries( test1 QCC_DB_LIB )
#target_link_libraries( test1 QCC_GL_LIB )
##target_link_libraries( test1 ${EXTERNAL_LIBS_LIBRARIES} )

#target_link_libraries(test1 VOMBATLIB )

##target_link_libraries( test1 CC_CORE_LIB )
##target_link_libraries( test1 QCC_DB_LIB )

#target_link_libraries( test1 QPCL_PLUGIN_UTILS_LIB )
