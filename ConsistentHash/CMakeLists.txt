
add_executable(test_consistent_hash test_consistent_hash.cpp md5.cc)
target_link_libraries(test_consistent_hash ${GTEST_BOTH_LIBRARIES})



