cmake_minimum_required(VERSION 3.2)

if(WIN32 AND MSVC AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "c:/Users/$ENV{USERNAME}/Downloads/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif()

project(learnopengl)

set(CMAKE_CXX_STANDARD 20)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-Wall -Wextra -pedantic -Werror)
    add_compile_options(-Wno-gnu-anonymous-struct -Wno-nested-anon-types)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wall -Wextra -pedantic -Werror)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/W3 /WX)
endif()

find_package(glfw3 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_subdirectory(tinygl)
include_directories(src tinygl/include tinygl/imgui)
link_libraries(fmt::fmt spdlog::spdlog tinygl)

macro(SUBDIRLIST result curdir)
    file(GLOB children RELATIVE ${curdir} ${curdir}/*)
    set(dirlist "")
    foreach(child ${children})
        if(IS_DIRECTORY ${curdir}/${child})
            list(APPEND dirlist ${child})
        endif()
    endforeach()
    set(${result} ${dirlist})
endmacro()

set(CHAPTERS
    01_getting_started
)

function(create_project_from_sources chapter demo)
    file(GLOB SOURCE
        src/${chapter}/${demo}/*.cpp
    )
    set(NAME "${demo}")
    add_executable(${NAME} ${SOURCE})
    set_target_properties(${NAME}
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${NAME}"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${NAME}"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${NAME}")
    target_compile_definitions(${NAME} PRIVATE NAME="${NAME}")
    # copy shader files to build directory
    file(GLOB SHADERS
        "src/${chapter}/${demo}/*.vert"
        "src/${chapter}/${demo}/*.frag"
        "src/${chapter}/${demo}/*.geom"
    )
    foreach(SHADER ${SHADERS})
        add_custom_command(TARGET ${NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${SHADER} $<TARGET_FILE_DIR:${NAME}>)
    endforeach(SHADER)
    add_custom_command(TARGET ${NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/tinygl/fonts $<TARGET_FILE_DIR:${NAME}>/fonts)
endfunction()

foreach(CHAPTER ${CHAPTERS})
    message(STATUS "Configuring examples for chapter ${CHAPTER}")
    SUBDIRLIST(EXAMPLES ${CMAKE_SOURCE_DIR}/src/${CHAPTER})
    foreach(EXAMPLE ${EXAMPLES})
        message(STATUS "Configuring example ${EXAMPLE}")
        create_project_from_sources(${CHAPTER} ${EXAMPLE})
    endforeach(EXAMPLE)
endforeach(CHAPTER)
