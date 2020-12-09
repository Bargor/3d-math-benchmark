# Author: Karol Kontny

cmake_minimum_required(VERSION 3.13)

project (3d-math-benchmark CXX)

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

#Compiler specific options
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	#General Win compile options
	message("Visual Studio compiler")
	set(BENCHMARK_COMPILE_OPTIONS /W3 /WX /MP /std:c++latest)
	set(TEMPEST_COMPILE_DEFINITIONS NOMINMAX)
	set(DEBUG_COMPILE_OPTIONS ${BENCHMARK_COMPILE_OPTIONS} /MDd)
	set(RELEASE_COMPILE_OPTIONS ${BENCHMARK_COMPILE_OPTIONS} /Oi /MD /GL /Ob2)
	set(RELWITHDEBINFO_COMPILE_OPTIONS ${BENCHMARK_COMPILE_OPTIONS} /Oi /MD /Ob2)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	message("GCC compiler")
	set(BENCHMARK_COMPILE_OPTIONS -Wall)
	set(TEMPEST_COMPILE_DEFINITIONS)
	set(DEBUG_COMPILE_OPTIONS ${BENCHMARK_COMPILE_OPTIONS} -O0 -march=native)
	set(RELEASE_COMPILE_OPTIONS ${BENCHMARK_COMPILE_OPTIONS} -O3 -funsafe-loop-optimizations -m64 -march=native -mfpmath=sse)
	set(RELWITHDEBINFO_COMPILE_OPTIONS ${BENCHMARK_COMPILE_OPTIONS} -O3 -funsafe-loop-optimizations -m64 -march=native -mfpmath=sse)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	message("Clang compiler")
	set(BENCHMARK_COMPILE_OPTIONS -Wall)
	set(DEBUG_COMPILE_OPTIONS ${BENCHMARK_COMPILE_OPTIONS} -O0 -mno-sse4.2)
	set(RELEASE_COMPILE_OPTIONS ${BENCHMARK_COMPILE_OPTIONS} -O3 -m64 -mno-sse4.2 -mfpmath=sse)
	set(RELWITHDEBINFO_COMPILE_OPTIONS ${BENCHMARK_COMPILE_OPTIONS} -O3 -m64 -mno-sse4.2 -mfpmath=sse)
endif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")

set(TEST_CODE 
    src/glm_vec4.cpp
    src/glm_vec4_simd.cpp
    src/eigen_vec4.cpp
    src/blaze_vec4.cpp
    src/mathfu_vec4.cpp
    src/mango_vec4.cpp
    src/glm_swizzle.cpp
    src/glm_simd_swizzle.cpp
    src/mango_swizzle.cpp
    src/glm_mat4.cpp
    src/glm_mat4_simd.cpp
    src/eigen_mat4.cpp
    src/blaze_mat4.cpp
    src/mathfu_mat4.cpp
    src/mango_mat4.cpp
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
