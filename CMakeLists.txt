cmake_minimum_required(VERSION 3.0.0)
project(GSTW VERSION 0.1.0)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

find_package(PkgConfig)

pkg_check_modules(GST REQUIRED IMPORTED_TARGET 
                                                gstreamer-video-1.0
                                                gstreamer-audio-1.0
                                                gstreamer-pbutils-1.0
                                                gstreamer-1.0)

file(GLOB_RECURSE GSTW_SOURCES "src/*.cpp")
file(GLOB_RECURSE GSTW_HEADERS "include/*.h")

set (GSTW_INCLUDE_DIRS "")
foreach (_headerFile ${GSTW_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND GSTW_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES GSTW_INCLUDE_DIRS)

add_subdirectory("apps/demos/gstreamer-tutorials")