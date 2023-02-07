include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(processTests
  main.cpp
)
target_link_libraries(processTests
  GTest::gtest_main
  GTest::gmock_main
  wgmCoreLib
)
target_include_directories(processTests
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../includes/
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../includes/processes/
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../includes/systems/
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/
)
include(GoogleTest)
gtest_discover_tests(processTests)

enable_testing()
