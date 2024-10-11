cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(foo VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
set(CMAKE_CONFIG_DIR ${PROJECT_SOURCE_DIR}/config)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

SET(CHECK_FILES
    ${PROJECT_SOURCE_DIR}/include/*.h*
    ${PROJECT_SOURCE_DIR}/src/*.c*)

# ------------------------------------------------------------------------------
# Astyle
# ------------------------------------------------------------------------------

if(ENABLE_ASTYLE)

    find_program(ASTYLE_BIN astyle)

    if(ASTYLE_BIN STREQUAL "ASTYLE_BIN-NOTFOUND")
        message(FATAL_ERROR "unable to locate astyle")
    endif()

    message(STATUS "astyle binary: ${ASTYLE_BIN}")

    list(APPEND ASTYLE_ARGS
        --style=google
        --lineend=linux
        --suffix=none
        --pad-oper
        --unpad-paren
        --break-closing-brackets
        --align-pointer=name
        --align-reference=name
        --indent-preproc-define
        --indent-switches
        --indent-col1-comments
        --keep-one-line-statements
        --keep-one-line-blocks
        --pad-header
        --convert-tabs
        --min-conditional-indent=0
        --indent=spaces=4
        --close-templates
        --add-brackets
        --break-after-logical
        ${CHECK_FILES}
    )

    add_custom_target(
        format
        COMMAND ${ASTYLE_BIN} ${ASTYLE_ARGS}
        COMMENT "running astyle"
    )


endif()

add_executable(bar ${SOURCES})

include (${CMAKE_MODULE_PATH}/init_local_projects.cmake)
