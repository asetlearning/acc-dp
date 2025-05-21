cmake_minimum_required(VERSION 3.5)

add_library(disjoint_subsets INTERFACE)

add_executable(crag.disjoint_subsets.test_disjoint_subsets test_disjoint_subsets.cpp)
target_link_libraries(crag.disjoint_subsets.test_disjoint_subsets gtest_main)


