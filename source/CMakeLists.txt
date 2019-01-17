cmake_minimum_required(VERSION 3.2)

option(with-tests "Build ip_filter-tests" OFF)

project(homework-02 VERSION 1.0.$ENV{TRAVIS_BUILD_NUMBER})

add_executable(ip_filter ip_filter.cpp)
set_target_properties(ip_filter PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

install(TARGETS ip_filter RUNTIME DESTINATION bin)

if (with-tests)
  set(CMAKE_THREAD_PREFER_PTHREAD ON)
  find_package(Threads REQUIRED)
  find_package(GTest REQUIRED)

  add_executable(ip_filter_tests ip_filter.cpp)
  target_compile_definitions(ip_filter_tests PRIVATE AUTOTESTS_MODE)
  set_target_properties(ip_filter_tests PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
    INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIRS}
  )
  target_link_libraries(ip_filter_tests ${GTEST_BOTH_LIBRARIES} Threads::Threads)

  enable_testing()
  add_test(general_tests ip_filter_tests)
endif (with-tests)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT ziminas1990@gmail.com)
include(CPack)
