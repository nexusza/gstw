function(add_app app_name)
    set (APP_SOURCES "${app_name}.cpp")
    list (APPEND APP_SOURCES ${GSTW_SOURCES})

    add_executable (${app_name} ${APP_SOURCES})
    target_include_directories(${app_name} PRIVATE ${GSTW_INCLUDE_DIRS})
    target_link_libraries(${app_name} PUBLIC
                                    PkgConfig::GST)

endfunction()

add_app("rtsp-launch")