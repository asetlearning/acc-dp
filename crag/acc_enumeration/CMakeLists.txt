cmake_minimum_required(VERSION 3.5)

hunter_add_package(fmt)
find_package(fmt CONFIG REQUIRED)

hunter_add_package(nlohmann_json)
find_package(nlohmann_json REQUIRED)

#hunter_add_package(Boost)
#find_package(Boost CONFIG REQUIRED)

hunter_add_package(Boost COMPONENTS filesystem iostreams system thread)
find_package(Boost CONFIG REQUIRED filesystem iostreams system thread)


add_library(acc_enumerate_utils
    STATIC
    acc_class.h acc_class.cpp
    acc_classes.h acc_classes.cpp
    boost_filtering_stream.h
    config.h config.cpp
    convert_byte_count.cpp convert_byte_count.h
    external_sort.cpp external_sort.h
    state_dump.h state_dump.cpp
    Terminator.cpp Terminator.h ACIndex.cpp ACIndex.h)

find_package(Threads)

target_link_libraries(acc_enumerate_utils
  PUBLIC
    Boost::filesystem
    Boost::iostreams
    Boost::system

    Threads::Threads

    fmt::fmt
    nlohmann_json::nlohmann_json

    crag_compressed_word_tuple_normal_form
    crag_folded_graph
    crag_folded_graph_complete
    crag_folded_graph_harvest
    crag_multithreading
    disjoint_subsets
)

#target_compile_options(acc_enumerate_utils PUBLIC -g -O1)

add_executable(crag.acc_enumeration.acc_enumerate
    ACPairProcessQueue.h
    acc_enumerate.cpp
    ACWorker.cpp ACWorker.h
    ACWorkerStats.cpp ACWorkerStats.h
    stopwatch.h stopwatch.cpp)

target_link_libraries(crag.acc_enumeration.acc_enumerate PRIVATE
    Boost::thread

    acc_enumerate_utils
    crag_multithreading
)

add_executable(crag.acc_enumeration.dump_cleanup
    dump_cleanup.cpp)

target_link_libraries(crag.acc_enumeration.dump_cleanup PRIVATE
    acc_enumerate_utils
)

set_target_properties(crag.acc_enumeration.acc_enumerate PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)

add_dependencies(crag.acc_enumeration.acc_enumerate crag.acc_enumeration.dump_cleanup)
