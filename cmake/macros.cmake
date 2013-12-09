function( find_mocable_files __out_var_name )   # + input list
    set( local_list )
    foreach( one_file ${ARGN} )
        file( READ ${one_file} stream )
        if( stream MATCHES "Q_OBJECT" )
            list( APPEND local_list ${one_file} )
        endif()
    endforeach()
    set( ${__out_var_name} ${local_list} PARENT_SCOPE )
endfunction()

MACRO(get_subdirectories result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
        SET(dirlist ${dirlist} ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

macro(find_relevant_files_recursive)
    file( GLOB_RECURSE header_list *.h)
    file( GLOB_RECURSE source_list *.cpp)
    file( GLOB_RECURSE ui_list *.ui)
    file( GLOB_RECURSE qrc_list *.qrc)
    file( GLOB_RECURSE rc_list *.rc)
endmacro()

macro(add_vombat_subdir dirname)
    get_filename_component(libname ${dirname}  NAME)
    set(mod_name "${PROJECT_NAME}_${libname}")
    set(VOMBAT_MODULES ${VOMBAT_MODULES} ${mod_name})
    set(VOMBAT_INCLUDE_DIRS ${VOMBAT_INCLUDE_DIRS} "${CMAKE_CURRENT_BINARY_DIR}/${libname}")
    set(VOMBAT_INCLUDE_DIRS ${VOMBAT_INCLUDE_DIRS} "${CMAKE_CURRENT_SOURCE_DIR}/${libname}")
endmacro()



macro(compile_vombat_submodule dependencies)
    get_filename_component(libname ${CMAKE_CURRENT_SOURCE_DIR}  NAME)
    set(mod_name "${PROJECT_NAME}_${libname}")

    find_relevant_files_recursive()
    # find Qt mocable files
    find_mocable_files( mocable_list ${header_list} )
    qt4_wrap_cpp( moc_list ${mocable_list} )
    QT4_WRAP_UI( generated_ui_list ${ui_list} )
    QT4_ADD_RESOURCES( generated_qrc_list ${qrc_list} )

    add_library( ${mod_name} SHARED ${header_list} ${source_list} ${moc_list} ${generated_ui_list} ${generated_qrc_list} ${rc_list})

    target_link_libraries(${mod_name} ${QT_LIBRARIES} ${SPC_LIBRARIES} PclUtils ${dependencies})

    install(TARGETS ${mod_name} DESTINATION lib)
endmacro()








