cmake_minimum_required(VERSION 3.2)

option(with-tests "Build ip-filter-tests" OFF)

project(homework-02)

add_executable(ip-filter ip_filter.cpp)
set_target_properties(ip-filter PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

install(TARGETS ip-filter RUNTIME DESTINATION bin)

if (with-tests)
  set(CMAKE_THREAD_PREFER_PTHREAD ON)
  find_package(Threads REQUIRED)
  find_package(GTest REQUIRED)

  add_executable(ip-filter-tests ip_filter.cpp)
  target_compile_definitions(ip-filter-tests PRIVATE AUTOTESTS_MODE)
  set_target_properties(ip-filter-tests PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
    INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIRS}
  )
  target_link_libraries(ip-filter-tests ${GTEST_BOTH_LIBRARIES} Threads::Threads)

  enable_testing()
  #add_test(test_version test_version)
endif (with-tests)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT ziminas1990@gmail.com)
include(CPack)
