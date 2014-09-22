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














