cmake_minimum_required(VERSION 2.8)
project(QtPropertyBrowser)

find_package(Qt5Widgets)
include_directories(${Qt5Widgets_INCLUDE_DIRS})


message("using qt5"  ${USE_QT5}  )


SET(KIT_SRCS
qtbuttonpropertybrowser.cpp
qtbuttonpropertybrowser.h
qteditorfactory.cpp
qteditorfactory.h
qtgroupboxpropertybrowser.cpp
qtgroupboxpropertybrowser.h
qtpropertybrowser.cpp
qtpropertybrowser.h
qtpropertybrowserutils.cpp
qtpropertybrowserutils_p.h
qtpropertymanager.cpp
qtpropertymanager.h
qttreepropertybrowser.cpp
qttreepropertybrowser.h
qtvariantproperty.cpp
qtvariantproperty.h
)
SET(KIT_MOC_SRCS
qtpropertybrowserutils_p.h
)
SET(KIT_UI_FORMS
)
SET(KIT_resources
qtpropertybrowser.qrc
)
INCLUDE_DIRECTORIES(
${CMAKE_CURRENT_SOURCE_DIR}
${CMAKE_CURRENT_BINARY_DIR}
)


if ( USE_QT5 )
	qt5_wrap_ui( KIT_UI_CPP ${KIT_UI_FORMS} )
	qt5_add_resources( KIT_QRC_SRCS ${KIT_resources} )
else()
	# find Qt mocable file
	QT4_WRAP_UI(KIT_UI_CPP ${KIT_UI_FORMS})
	QT4_WRAP_CPP(KIT_MOC_CPP ${KIT_MOC_SRCS})
	QT4_ADD_RESOURCES(KIT_QRC_SRCS ${KIT_resources})
endif()





SET(libname ${PROJECT_NAME})
ADD_LIBRARY(${libname} STATIC
${KIT_SRCS}
${KIT_UI_CPP}
${KIT_MOC_CPP}
${KIT_QRC_SRCS}
)
SET(${PROJECT_NAME}_LINK_LIBRARIES ${QT_LIBRARIES})
TARGET_LINK_LIBRARIES(${libname} ${${PROJECT_NAME}_LINK_LIBRARIES} )


# List of header that should go though moc
SET(KIT_HEADERS_MOC_SRCS
qtbuttonpropertybrowser.h
qteditorfactory.h
qtgroupboxpropertybrowser.h
qtpropertybrowser.h
qtpropertybrowserutils_p.h
qtpropertymanager.h
qttreepropertybrowser.h
qtvariantproperty.h
)
SET(KIT_MOC_CPP)
FOREACH(file ${KIT_HEADERS_MOC_SRCS})
get_filename_component(filename_we ${file} NAME_WE)
SET(output_file moc_${filename_we}.cpp)

if (USE_QT5)
	QT5_GENERATE_MOC(${file} ${output_file})
else()
	QT4_GENERATE_MOC(${file} ${output_file})
endif()

LIST(APPEND KIT_MOC_CPP ${output_file})
ENDFOREACH()
# List of cpp files that should go though moc
SET(KIT_CPP_MOC_SRCS
qteditorfactory.cpp
qtpropertymanager.cpp
qttreepropertybrowser.cpp
)
FOREACH(file ${KIT_CPP_MOC_SRCS})
get_filename_component(filename_we ${file} NAME_WE)
SET(output_file ${filename_we}.moc)


if (USE_QT5)
	QT5_GENERATE_MOC(${file} ${output_file})
else()
	QT4_GENERATE_MOC(${file} ${output_file})
endif()

#QT4_GENERATE_MOC(${file} ${output_file})
LIST(APPEND KIT_MOC_CPP ${output_file})
ENDFOREACH()
add_custom_target(${libname}GenerateMoc
DEPENDS ${KIT_MOC_CPP}
)
add_dependencies(${libname} ${libname}GenerateMoc)
