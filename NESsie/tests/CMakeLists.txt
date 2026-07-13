add_executable(NESsieTest
    instructions/LoadStoreTransferTests.cpp
    instructions/StackTests.cpp
    "TestCpu.h"
    instructions/LogicalTests.cpp
    ../cpu.cpp
    ../mainbus.cpp
    instructions/ArithmeticTests.cpp "instructions/ShiftTests.cpp" "instructions/CompareTests.cpp" "instructions/BranchTests.cpp" "instructions/JumpTests.cpp" "instructions/FlagTests.cpp" "TestMapper.h"
        ../TestMapper.cpp
        ../TestMapper.h
        ../mapper.h
        ../mapper.cpp
        ../ppu.cpp
        ../ppu.h)

target_include_directories(NESsieTest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(NESsieTest PRIVATE
    GTest::gtest_main
)

if(TARGET  NESsieTest)
    include(GoogleTest)
    gtest_discover_tests(NESsieTest)
endif()