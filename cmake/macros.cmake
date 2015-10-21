

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








