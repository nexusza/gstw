function(add_demo demo_name)
    #message(STATUS "Simple arguments: ${REQUIRED_ARG}, followed by ${ARGV}")
    #set(${REQUIRED_ARG} "From SIMPLE" PARENT_SCOPE)

    set (TUT_SOURCES "${demo_name}.cpp")
    list (APPEND TUT_SOURCES ${GSTW_SOURCES})

    add_executable (${demo_name} ${TUT_SOURCES})
    target_include_directories(${demo_name} PRIVATE ${GSTW_INCLUDE_DIRS})
    target_link_libraries(${demo_name} PUBLIC
                                    PkgConfig::GST)

endfunction()

add_demo("tutorial1")
add_demo("tutorial2")
add_demo("tutorial3")
add_demo("tutorial4")                                