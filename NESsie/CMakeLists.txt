# CMakeList.txt : CMake project for NESsie, include source and define
# project specific logic here.
#
# Add source to this project's executable.
add_executable (NESsie "NESsie.cpp" "NESsie.h" "cpu.h" "memory.h" "defines.h" "memory.cpp" "cpu.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET NESsie PROPERTY CXX_STANDARD 20)
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

