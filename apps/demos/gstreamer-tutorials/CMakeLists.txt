pkg_check_modules(GTK QUIET IMPORTED_TARGET 
                                            gtk+-3.0)

function(add_demo demo_name)
    set (TUT_SOURCES "${demo_name}.cpp")
    
    list (APPEND TUT_SOURCES ${GSTW_SOURCES})

    add_executable (${demo_name} ${TUT_SOURCES})
    
    target_include_directories(${demo_name} PRIVATE ${GSTW_INCLUDE_DIRS})

    target_link_libraries(${demo_name} PUBLIC
                                    PkgConfig::GST)

    if(${GTK}_INCLUDE_DIRS)
        target_link_libraries(${demo_name} PUBLIC
            PkgConfig::GTK)
    endif()

endfunction()

add_demo("tutorial1")
add_demo("tutorial2")
add_demo("tutorial3")
add_demo("tutorial4")
add_demo("tutorial6")
add_demo("tutorial7")
add_demo("tutorial8")
add_demo("tutorial9")
add_demo("tutorial12")
add_demo("tutorial13")

if(${GTK}_INCLUDE_DIRS)
    add_demo("tutorial5")
endif()