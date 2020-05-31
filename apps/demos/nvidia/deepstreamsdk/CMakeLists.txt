
set(NVIDA_DS_INCLUDE_DIRS /home/nanonexusza/Downloads/deepstream_sdk_v4.0.2_jetson/sources/includes)
set(NVIDA_DS_ROOT /opt/nvidia/deepstream/deepstream-4.0)

link_directories(${NVIDA_DS_ROOT}/lib)

function(add_demo demo_name)
    set (TUT_SOURCES "${demo_name}.cpp")
    
    list (APPEND TUT_SOURCES ${GSTW_SOURCES})

    add_executable (${demo_name} ${TUT_SOURCES})
    
    target_include_directories(${demo_name} PRIVATE 
                                                ${GSTW_INCLUDE_DIRS}
                                                ${NVIDA_DS_INCLUDE_DIRS})

    target_link_libraries(${demo_name} PUBLIC
                                    PkgConfig::GST
                                    nvdsgst_meta
                                    nvds_meta)

endfunction()

add_demo("nvidiatest1")
add_demo("nvidiatest2")
add_demo("nvidiatest3")