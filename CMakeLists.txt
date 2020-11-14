# Author: Karol Kontny

cmake_minimum_required(VERSION 3.13)

project (GLM-benchmark CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Google benchmark tests")
set(GLM_TEST_ENABLE OFF CACHE BOOL "Build glm unit tests")
set(BUILD_TESTING OFF CACHE BOOL "Build Eigen tests")
set(mathfu_build_benchmarks OFF CACHE BOOL "Build mathfu benchmark")
set(mathfu_build_tests OFF CACHE BOOL "Build mathfu tests")
set(USE_LAPACK OFF CACHE BOOL "use blaze lapack")


add_subdirectory(benchmark)
add_subdirectory(glm)
add_subdirectory(eigen)
add_subdirectory(mathfu)
add_subdirectory(blaze)
add_subdirectory(mango/build)

set(TEST_CODE 
    src/glm_vec4.cpp
    src/glm_vec4_simd.cpp
    src/eigen_vec4.cpp
    src/blaze_vec4.cpp
    src/mathfu_vec4.cpp
    src/mango_vec4.cpp
)

foreach(SOURCE_FILE ${TEST_CODE})
	get_filename_component(TEST_NAME ${SOURCE_FILE} NAME_WE)

	#Compile files and link with objects
	add_executable(${TEST_NAME} src/prepare_test_data.h "${SOURCE_FILE}")
    
    source_group(${TEST_NAME} FILES ${SOURCE_FILE})
    
    mathfu_configure_flags(${TEST_NAME})
    
    target_sources(${TEST_NAME} PRIVATE ${SOURCE_FILE})
    
    target_compile_options(${TEST_NAME} PUBLIC "$<$<CONFIG:DEBUG>:${DEBUG_COMPILE_OPTIONS}>")
    target_compile_options(${TEST_NAME} PUBLIC "$<$<CONFIG:RELEASE>:${RELEASE_COMPILE_OPTIONS}>")
    target_compile_options(${TEST_NAME} PUBLIC "$<$<CONFIG:RELWITHDEBINFO>:${RELWITHDEBINFO_COMPILE_OPTIONS}>")

    target_compile_definitions(${TEST_NAME} PUBLIC "$<$<CONFIG:DEBUG>:${DEBUG_COMPILE_DEFINITIONS}>")
    target_compile_definitions(${TEST_NAME} PUBLIC "$<$<CONFIG:RELEASE>:${RELEASE_COMPILE_DEFINITIONS}>")
    target_compile_definitions(${TEST_NAME} PUBLIC "$<$<CONFIG:RELWITHDEBINFO>:${RELWITHDEBINFO_COMPILE_DEFINITIONS}>")

	target_link_libraries(${TEST_NAME} PRIVATE benchmark glm Eigen3::Eigen blaze mango)
	if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		target_link_libraries(${TEST_NAME} PRIVATE -lpthread)
	endif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
endforeach(SOURCE_FILE)