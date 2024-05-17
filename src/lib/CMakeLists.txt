aux_source_directory(. SRCS_LIB)
add_library(${lib_lib_name} SHARED ${SRCS_LIB})

if(UNIX)
    # 设置动态库生成目录
    set_target_properties(${lib_lib_name} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${lib_dir})
endif()

if(WIN32)
    add_custom_command(TARGET ${lib_lib_name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/${lib_lib_file_name} ${bin_dir}/
    )
endif()
