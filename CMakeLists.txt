cmake_minimum_required(VERSION 3.1)

if(WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "c:/Users/$ENV{USERNAME}/Downloads/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif()

project(learnopengl)

set(CMAKE_CXX_STANDARD 23)

if (MSVC)
    add_compile_options(/W3 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

find_package(glfw3 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_subdirectory(tinygl)
include_directories(src tinygl/include)
link_libraries(fmt::fmt spdlog::spdlog tinygl)

MACRO(SUBDIRLIST result curdir)
    FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
    SET(dirlist "")
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${curdir}/${child})
            LIST(APPEND dirlist ${child})
        ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO()

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
        add_custom_command(TARGET ${NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SHADER} $<TARGET_FILE_DIR:${NAME}>)
    endforeach(SHADER)
endfunction()

foreach(CHAPTER ${CHAPTERS})
    message(STATUS "Configuring examples for chapter ${CHAPTER}")
    SUBDIRLIST(EXAMPLES ${CMAKE_SOURCE_DIR}/src/${CHAPTER})
    foreach(EXAMPLE ${EXAMPLES})
        message(STATUS "Configuring example ${EXAMPLE}")
        create_project_from_sources(${CHAPTER} ${EXAMPLE})
    endforeach(EXAMPLE)
endforeach(CHAPTER)
