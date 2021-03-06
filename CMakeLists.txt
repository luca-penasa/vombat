cmake_minimum_required(VERSION 2.8)

option( INSTALL_vombat_PLUGIN "Check to install vombat plugin" OFF )

if (INSTALL_vombat_PLUGIN)

    project(vombat)

	add_definitions(-DELPP_THREAD_SAFE) # for thread safe loggin


    option(BUILD_VOMBAT_MONOLITHIC "Build vombat plugin all-in-one" OFF)
	option (VOMBAT_ENABLE_EXPERIMENTAL_TOOLS "enable all the available tools, for developing porpuses" OFF )


	if (VOMBAT_ENABLE_EXPERIMENTAL_TOOLS)
		add_definitions(-DVOMBAT_EX_TOOLS)
	endif(VOMBAT_ENABLE_EXPERIMENTAL_TOOLS)

    include(cmake/macros.cmake) # load some macros


        add_subdirectory(external/qtpropertybrowser_qt5)
        include_directories("external/qtpropertybrowser_qt5")

    include_directories("external/qtpropertybrowser")

 #   if(USE_QT5)
 #       find_package(Qt5Widgets)
 #       include_directories(${Qt5Widgets_INCLUDE_DIRS})
 #   endif()


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
	include_directories( ${QCC_IO_LIB_SOURCE_DIR} )
	include_directories( ${CloudCompare_SOURCE_DIR}/db_tree )
include_directories( ${qcustomplot_SOURCE_DIR} )

    if( MSVC )
        include_directories( ${QCC_DB_LIB_SOURCE_DIR}/msvc )
    endif()

    include_directories( ${QCC_GL_LIB_SOURCE_DIR} )


	if (MSVC)
        add_definitions("-DNOMINMAX")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -wd4996") #pcl::SHOOT warn
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -wd4521") # pcl/eigen multiple copy constructors warn
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -wd4305") # some conversion / possible data-loss
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated -Wno-narrowing")  #get rid of annoying warns
    endif()

	option (SPC_AS_STATIC "compile spc as static lib, instead that shared" ON)

	if (${SPC_AS_STATIC})
		# Force spc to be build as a static lib
		set(SPC_BUILD_SHARED OFF CACHE BOOL "Build spc library as a shared lib." FORCE)
		set(SPC_ENABLE_INSTALL OFF CACHE BOOL "Enable/Disable the install target" FORCE)
	else()
		set(SPC_BUILD_SHARED ON CACHE BOOL "Build spc library as a shared lib." FORCE)
		set(SPC_ENABLE_INSTALL ON CACHE BOOL "Enable/Disable the install target" FORCE)
	endif()

	# and force disable gflags wich is not needed by cloudcompare
	set(SPC_GFLAGS OFF CACHE BOOL "Enable Google Flags. Needed by the tools" FORCE)



	add_subdirectory(spc)


#	set(SPC_INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")


    #################### SPC ###########################################
    #it also automatically find PCL and other required libraries
	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "cmake" )

#	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/spc )

find_package(SPC 0.1.0 REQUIRED
	        PATHS ${CMAKE_CURRENT_BINARY_DIR}/spc
		NO_DEFAULT_PATH )

	message("SPC INCLUDE DIR ${SPC_INCLUDE_DIRS}")

	include_directories(${SPC_INCLUDE_DIRS})
	link_directories(${SPC_LIBRARY_DIRS})
	add_definitions(${SPC_DEFINITIONS})

    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/vombatlib)
    include_directories(${CMAKE_CURRENT_BINARY_DIR}/vombatlib)

    set (SUBDIRS ccoutofcore dialogs plotter2d tools visualization helpers)

    foreach (dir ${SUBDIRS})
        include_directories(${CMAKE_CURRENT_SOURCE_DIR}/vombatlib/${dir})
        message("here: ${CMAKE_CURRENT_SOURCE_DIR}/vombatlib/${dir}")
    endforeach()

    add_subdirectory(vombatlib)

    include( ../../CMakePluginTpl.cmake )

	target_link_libraries(${PROJECT_NAME} ${PCL_LIBRARIES} ${SPC_LIBRARIES} VOMBATLIB ${QT_LIBRARIES} )

    target_link_libraries(${PROJECT_NAME} VOMBATLIB)

    target_link_libraries( ${PROJECT_NAME} CC_CORE_LIB )
    target_link_libraries( ${PROJECT_NAME} QCC_DB_LIB )

#    target_link_libraries( ${PROJECT_NAME} QPCL_PLUGIN_UTILS_LIB)

#    ADD_DEPENDENCIES(  vombat CC_CORE_LIB QCC_DB_LIB QCC_GL_LIB QPCL_PLUGIN QCC_IO_LIB CloudCompare)
    ADD_DEPENDENCIES(  vombat CC_CORE_LIB QCC_DB_LIB QCC_GL_LIB QCC_IO_LIB CloudCompare)


endif() #main if ends here



