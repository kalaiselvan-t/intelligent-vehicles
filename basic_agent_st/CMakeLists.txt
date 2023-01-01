cmake_minimum_required(VERSION 3.5)
project(basic_agent_ST)

set(CMAKE_CXX_STANDARD 11)
# If you are on mac x86
#set(CMAKE_OSX_ARCHITECTURES x86_64)

include(lib/basic.cmake)

include_directories(
        matlab/
        lib
        log
        codegen/lib/pass_primitive
)

#target_include_directories(pass_primitive PUBLIC
#        "${PROJECT_BINARY_DIR}"
#        "${PROJECT_SOURCE_DIR}/codegen/lib/pass_primitive"
#        )

#find_package(pass_primitive REQUIRED)

link_directories(
        lib
        codegen
)

# ------------------------------- basic agent ------------------------------------
add_executable(basic_agent
        log/screen_print.c
        log/logvars.cc
        starting_point.cc
    )
target_link_directories(basic_agent PUBLIC codegen/lib/pass_primitive/build)
target_link_libraries(basic_agent agent_lib ${lib_ws32} pass_primitive )

target_compile_options(basic_agent
        PUBLIC -DNOT_INLINED -DSERVER
        )

set_target_properties(basic_agent PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${AGENT_FOLDER})
# ------------------------------------------------------------------------------------
