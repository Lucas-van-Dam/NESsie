add_executable(NESsieTest
    instructions/LoadStoreTransferTests.cpp
    instructions/StackTests.cpp
    instructions/TestCpu.h
    instructions/LogicalTests.cpp
    ../cpu.cpp
    ../memory.cpp
)

target_include_directories(NESsieTest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(NESsieTest PRIVATE
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(NESsieTest)