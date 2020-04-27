function(add_demo demo_name)
    set (DEMO_SOURCES "${demo_name}.cpp")
    list (APPEND DEMO_SOURCES ${GSTW_SOURCES})

    add_executable (${demo_name} ${DEMO_SOURCES})
    target_include_directories(${demo_name} PRIVATE ${GSTW_INCLUDE_DIRS})
    target_link_libraries(${demo_name} PUBLIC
                                    PkgConfig::GST)

endfunction()

add_demo("udpsinknvidia")