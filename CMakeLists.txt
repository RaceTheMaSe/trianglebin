cmake_minimum_required(VERSION 3.0)
# Consider if MSVC, cross-compile MinGW or MinGW with explicit toolchain path provided as -DTOOLCHAIN_ROOT=<path-to-mingw-bin-folder-with-trailing-slash>
if(NOT (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows") OR TOOLCHAIN_ROOT)
  if(NOT TOOLCHAIN_ROOT)
    set(TOOLCHAIN_ROOT /usr/bin/)
  endif()
  set(TOOLCHAIN_PREFIX ${TOOLCHAIN_ROOT}x86_64-w64-mingw32)
  include(MinGW64.cmake)
endif()
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(triangleBin LANGUAGES CXX)

file(GLOB SOURCES_MAIN *.cpp)
file(GLOB_RECURSE SOURCES_IMGUI imgui/*.cpp)
file(GLOB SHADERS *.hlsl)
set(SOURCES ${SOURCES_IMGUI} ${SOURCES_MAIN})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC imgui)
target_link_libraries(${PROJECT_NAME} PUBLIC dxgi d3d11 d3dcompiler imm32)
install(FILES ${SHADERS} DESTINATION .)
install(TARGETS ${PROJECT_NAME} DESTINATION .)

if(NOT MSVC)
target_compile_definitions(${PROJECT_NAME} PUBLIC WINVER=0x0600 _WIN32_WINNT=0x0600)
  if(CMAKE_COMPILER_ID STREQUAL "GNU" AND NOT CMAKE_HAVE_LIBC_PTHREAD EQUAL 1 AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 13) # refine if needed: MinGW GCC8 and 10 needs it, MinGW GCC13 not, MinGW Clang 16 provides std::threads / std::mutex, so not considered
          option(MINGW_STDTHREADS_GENERATE_STDHEADERS "" ON)
          add_subdirectory(mingw-std-threads)
          target_link_libraries(${PROJECT_NAME} PUBLIC mingw_stdthreads)
  endif()
endif()
