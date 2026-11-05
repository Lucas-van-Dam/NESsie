# CMakeList.txt : CMake project for NESsie, include source and define
# project specific logic here.
#
# Add source to this project's executable.
add_executable (NESsie "NESsie.cpp" "NESsie.h" "cpu.h" "mainbus.h" "defines.h" "mainbus.cpp" "cpu.cpp" "cartridge.h" "cartridge.cpp" "mapper.h" "mapper.cpp" "NROMMapper.cpp"
        TestMapper.cpp
        TestMapper.h
        ppu.cpp
        ppu.h
        VirtualScreen.cpp
        VirtualScreen.h
        Input.cpp
        Input.h)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET NESsie PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(NESsie PRIVATE SDL3::SDL3)

if(MSVC)
  execute_process(
          COMMAND ping www.google.com -n 2
          ERROR_QUIET
          RESULT_VARIABLE NO_CONNECTION
  )
else()
  execute_process(
          COMMAND ping www.google.com -c 2
          ERROR_QUIET
          RESULT_VARIABLE NO_CONNECTION
  )
endif()

if(NOT NO_CONNECTION EQUAL 0)
  set(FETCHCONTENT_FULLY_DISCONNECTED ON)
  message(WARNING "not fetching google test, need to have it locally to run tests")
else()
  set(FETCHCONTENT_FULLY_DISCONNECTED OFF)
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

