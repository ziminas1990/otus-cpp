cmake_minimum_required(VERSION 3.2)

option(with-tests "Build allocator-tests" OFF)

project(allocator VERSION 1.0.$ENV{TRAVIS_BUILD_NUMBER})

add_executable(allocator main.cpp)
set_target_properties(allocator PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

install(TARGETS allocator RUNTIME DESTINATION bin)

if (with-tests)
  set(CMAKE_THREAD_PREFER_PTHREAD ON)
  find_package(Threads REQUIRED)
  find_package(GTest REQUIRED)

  add_executable(allocator_tests autotests.cpp)
  target_compile_definitions(allocator_tests PRIVATE AUTOTESTS_MODE)
  set_target_properties(allocator_tests PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
    INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIRS}
  )
  target_link_libraries(allocator_tests ${GTEST_BOTH_LIBRARIES} Threads::Threads)

  enable_testing()
  add_test(general_tests allocator_tests)
endif (with-tests)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT ziminas1990@gmail.com)
include(CPack)
