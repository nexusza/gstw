pkg_check_modules(GTK REQUIRED IMPORTED_TARGET 
                                                gtk+-3.0)

function(add_demo demo_name)
    set (TUT_SOURCES "${demo_name}.cpp")
    list (APPEND TUT_SOURCES ${GSTW_SOURCES})

    add_executable (${demo_name} ${TUT_SOURCES})
    target_include_directories(${demo_name} PRIVATE ${GSTW_INCLUDE_DIRS})
    target_link_libraries(${demo_name} PUBLIC
                                    PkgConfig::GST
                                    PkgConfig::GTK)

endfunction()

add_demo("tutorial1")
add_demo("tutorial2")
add_demo("tutorial3")
add_demo("tutorial4")
add_demo("tutorial5")