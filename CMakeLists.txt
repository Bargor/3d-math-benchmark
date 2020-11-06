# Author: Karol Kontny

cmake_minimum_required(VERSION 3.13)

project (GLM-benchmark CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Google benchmark tests")
set(GLM_TEST_ENABLE OFF CACHE BOOL "Build unit tests")

add_subdirectory(benchmark)
add_subdirectory(glm)

set(TEST_CODE 
    src/glm_vec4.cpp
    src/glm_vec4_simd.cpp
)


foreach(SOURCE_FILE ${TEST_CODE})
	get_filename_component(TEST_NAME ${SOURCE_FILE} NAME_WE)

	#Compile files and link with objects
	add_executable(${TEST_NAME} "" "${SOURCE_FILE}")
    
    source_group(${TEST_NAME} FILES ${SOURCE_FILE})
    
    target_sources(${TEST_NAME} PRIVATE ${SOURCE_FILE})
    
    target_compile_options(${TEST_NAME} PUBLIC "$<$<CONFIG:DEBUG>:${DEBUG_COMPILE_OPTIONS}>")
    target_compile_options(${TEST_NAME} PUBLIC "$<$<CONFIG:RELEASE>:${RELEASE_COMPILE_OPTIONS}>")
    target_compile_options(${TEST_NAME} PUBLIC "$<$<CONFIG:RELWITHDEBINFO>:${RELWITHDEBINFO_COMPILE_OPTIONS}>")

    target_compile_definitions(${TEST_NAME} PUBLIC "$<$<CONFIG:DEBUG>:${DEBUG_COMPILE_DEFINITIONS}>")
    target_compile_definitions(${TEST_NAME} PUBLIC "$<$<CONFIG:RELEASE>:${RELEASE_COMPILE_DEFINITIONS}>")
    target_compile_definitions(${TEST_NAME} PUBLIC "$<$<CONFIG:RELWITHDEBINFO>:${RELWITHDEBINFO_COMPILE_DEFINITIONS}>")

	target_link_libraries(${TEST_NAME} PRIVATE benchmark glm)
	if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		target_link_libraries(${TEST_NAME} PRIVATE -lpthread)
	endif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
endforeach(SOURCE_FILE)