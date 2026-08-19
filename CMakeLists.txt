cmake_minimum_required(VERSION 3.25...4.4)

project(
    argus
    VERSION 0.1.0
    DESCRIPTION "low latency matching engine in c++"
    LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_library(argus INTERFACE)

target_include_directories(argus INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(argus INTERFACE cxx_std_23)

target_compile_options(argus INTERFACE
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wconversion
        -Wsign-conversion
        -Wnull-dereference
        -fno-exceptions
        -fno-rtti
        $<$<CONFIG:Release>:-O3 -march=native>
    >
    $<$<CXX_COMPILER_ID:MSVC>:
        /W4
        /permissive-
        /EHs-c-
        $<$<CONFIG:Release>:/O2>
    >
)

target_compile_definitions(argus INTERFACE
    $<$<CXX_COMPILER_ID:MSVC>:_HAS_EXCEPTIONS=0>
)

# Core engine
add_executable(argus_app src/engine.cpp)
target_link_libraries(argus_app PRIVATE argus)

set_target_properties(argus_app PROPERTIES
    OUTPUT_NAME "argus"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Trader terminal
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/iris.cpp")
    add_executable(iris src/iris.cpp)
    target_link_libraries(iris PRIVATE argus)

    set_target_properties(iris PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
endif()

# Liquidity bot
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/plutus.cpp")
    add_executable(plutus src/plutus.cpp)
    target_link_libraries(plutus PRIVATE argus)

    set_target_properties(plutus PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
endif()

# Benchmarking
option(ARGUS_BUILD_BENCHMARKS "Build latency benchmarks" ON)

if(ARGUS_BUILD_BENCHMARKS)
    include(Dependencies)

    add_library(matching_bench INTERFACE)
    target_link_libraries(matching_bench INTERFACE
        argus
        benchmark::benchmark_main
        hdr_histogram_static
    )

    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/benchmarks/bench_main.cpp")
        add_executable(argus_benchmark benchmarks/bench_main.cpp)
        target_link_libraries(argus_benchmark PRIVATE matching_bench)

        set_target_properties(argus_benchmark PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        )
    endif()
endif()
