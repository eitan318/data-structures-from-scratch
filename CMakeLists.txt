cmake_minimum_required(VERSION 3.14)
project(ds LANGUAGES CXX
    DESCRIPTION "Header-only C++ data-structures library"
    VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---- Header-only library --------------------------------------------------
add_library(ds INTERFACE)
target_include_directories(ds INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)
target_compile_features(ds INTERFACE cxx_std_17)

# ---- Examples -------------------------------------------------------------
option(DS_BUILD_EXAMPLES "Build the example executables" ON)

if(DS_BUILD_EXAMPLES)
    file(GLOB DS_EXAMPLE_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/examples/*.cpp")
    foreach(src IN LISTS DS_EXAMPLE_SOURCES)
        get_filename_component(name "${src}" NAME_WE)
        add_executable(example_${name} "${src}")
        target_link_libraries(example_${name} PRIVATE ds)
        set_target_properties(example_${name} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples")
    endforeach()
endif()

# ---- Doxygen --------------------------------------------------------------
find_package(Doxygen)
if(DOXYGEN_FOUND)
    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
endif()
