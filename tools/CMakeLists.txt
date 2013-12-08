set(MODULE_NAME "qGEOTools")


include_directories( ${CC_DLL_SOURCE_DIR}/include )
include_directories( ${CloudCompare_SOURCE_DIR} )
include_directories( ${CloudCompare_SOURCE_DIR}/db_tree )
include_directories( ${CloudCompare_BINARY_DIR} )
include_directories( ${QCC_DB_DLL_SOURCE_DIR} )

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR}/dialogs)





find_package(PCL REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

find_package(VTK REQUIRED)
include_directories(${VTK_INCLUDE_DIRS})
link_directories(${VTK_LIBRARY_DIRS})
add_definitions(${VTK_DEFINITIONS})


file( GLOB header_list *.h dialogs/*.h ccOutOfCore/*.h)
file( GLOB source_list *.cpp dialogs/*.cpp ccOutOfCore/*.cpp)
file( GLOB ui_list *.ui dialogs/*.ui)
file( GLOB qrc_list *.qrc )
file( GLOB rc_list *.rc )

# find Qt mocable files
find_mocable_files( mocable_list ${header_list} )
qt4_wrap_cpp( moc_list ${mocable_list} )
QT4_WRAP_UI( generated_ui_list ${ui_list} )
QT4_ADD_RESOURCES( generated_qrc_list ${qrc_list} )


include_directories(${SPC_INCLUDE_DIRS})

add_library( ${MODULE_NAME} SHARED ${header_list} ${source_list} ${moc_list} ${generated_ui_list} ${generated_qrc_list} ${rc_list})

target_link_libraries(${MODULE_NAME} ${PCL_LIBRARIES} ${QT_LIBRARIES} ${VTK_LIBRARIES} ${SPC_LIBRARIES} PclUtils qGEOVis)

install(TARGETS ${MODULE_NAME} DESTINATION lib)


