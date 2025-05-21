cmake_minimum_required(VERSION 3.5)

include("cmake/HunterGate.cmake")
option(HUNTER_TLS_VERIFY "TLS Verify" ON)


#HunterGate(
#    URL "https://github.com/cpp-pm/hunter/archive/v0.24.0.tar.gz"
#    SHA1 "a3d7f4372b1dcd52faa6ff4a3bd5358e1d0e5efd"
#)
#HunterGate(
#        URL "https://github.com/cpp-pm/hunter/archive/v0.25.0.tar.gz"
#        SHA1 "a1296b351dbfaf036c92d85c1bdb461f615849fa"
#)

#HunterGate(
#    URL "https://github.com/ruslo/hunter/archive/v0.14.23.tar.gz"
#    SHA1 "999f07d004649f5f549953f74f21e46b48d53931"
#)

HunterGate(
   URL "https://github.com/cpp-pm/hunter/archive/v0.25.8.tar.gz"
   SHA1 "26c79d587883ec910bce168e25f6ac4595f97033"
   LOCAL
)


project(acc)

# guard against in-source builds

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. ")
endif()

# to make things easier, we require c++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)

# guard against bad build-type strings

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

string(TOLOWER "${CMAKE_BUILD_TYPE}" cmake_build_type_tolower)
if(    NOT cmake_build_type_tolower STREQUAL "debug"
    AND NOT cmake_build_type_tolower STREQUAL "release"
    AND NOT cmake_build_type_tolower STREQUAL "relwithdebinfo"
    AND NOT cmake_build_type_tolower STREQUAL "minsizerel")
  message(FATAL_ERROR "Unknown build type \"${CMAKE_BUILD_TYPE}\". Allowed values are Debug, Release, RelWithDebInfo, MinSizeRel (case-insensitive).")
endif()

enable_testing()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang"
    OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
#  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -fsanitize=address -fno-omit-frame-pointer -Wall -Werror")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -fsanitize=address -fno-omit-frame-pointer -Wall -Werror")
  set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -g -fsanitize=address")
endif()

include_directories(.)

add_subdirectory(googletest/googletest)
target_include_directories(gtest INTERFACE googletest/googletest/include)

add_subdirectory(crag)
