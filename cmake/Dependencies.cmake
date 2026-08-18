include(FetchContent)

if(ARGUS_BUILD_BENCHMARKS)
    set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
    set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)
    set(BENCHMARK_ENABLE_WERROR  OFF CACHE BOOL "" FORCE)

    FetchContent_Declare(
        google_benchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG        v1.9.0
        SYSTEM
    )
    FetchContent_MakeAvailable(google_benchmark)

    set(HDR_HISTOGRAM_BUILD_PROGRAMS OFF CACHE BOOL "" FORCE)
    set(HDR_HISTOGRAM_BUILD_SHARED   OFF CACHE BOOL "" FORCE)
    set(HDR_HISTOGRAM_INSTALL_SHARED OFF CACHE BOOL "" FORCE)
    set(HDR_HISTOGRAM_BUILD_STATIC   ON  CACHE BOOL "" FORCE)
    set(HDR_HISTOGRAM_INSTALL_STATIC OFF CACHE BOOL "" FORCE)
    set(HDR_LOG_REQUIRED             "DISABLED" CACHE STRING "" FORCE)

    FetchContent_Declare(
        hdr_histogram
        GIT_REPOSITORY https://github.com/HdrHistogram/HdrHistogram_c.git
        GIT_TAG        0.11.8
        SYSTEM
    )
    FetchContent_MakeAvailable(hdr_histogram)
endif()
