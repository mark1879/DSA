cmake_minimum_required(VERSION 3.1)

project(DSA)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(common/)

add_definitions(-w)

# add_subdirectory(B+Tree/)
# add_subdirectory(LinkedList/)
# add_subdirectory(InvertedIndex/)
# add_subdirectory(BSTree/)
# add_subdirectory(AVLTree/)
# add_subdirectory(Sort/)  
# add_subdirectory(Heap/)
# add_subdirectory(BinarySearch/)
# add_subdirectory(HashTable/)
# add_subdirectory(SkipList/)
# add_subdirectory(Stack/)
# add_subdirectory(Queue/)
# add_subdirectory(MassiveDataDeduplication/)
# add_subdirectory(TrieTree/)
# add_subdirectory(ConsistentHash/)
# add_subdirectory(Vector/)
# add_subdirectory(Backtracking/)
# add_subdirectory(TopK/)
add_subdirectory(Graph/)