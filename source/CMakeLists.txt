cmake_minimum_required(VERSION 3.2)

option(with-tests "Build autotests" OFF)

set(PROJECT_NAME matrix)
set(PROJECT_TESTS_NAME ${PROJECT_NAME}_tests)

project(${PROJECT_NAME} VERSION 1.0.$ENV{TRAVIS_BUILD_NUMBER})

add_executable(${PROJECT_NAME} main.cpp matrix.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

if (with-tests)
  set(CMAKE_THREAD_PREFER_PTHREAD ON)
  find_package(Threads REQUIRED)
  find_package(GTest REQUIRED)

  add_executable(${PROJECT_TESTS_NAME} autotests.cpp)
  target_compile_definitions(${PROJECT_TESTS_NAME} PRIVATE AUTOTESTS_MODE)
  set_target_properties(${PROJECT_TESTS_NAME} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
    INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIRS}
  )
  target_link_libraries(${PROJECT_TESTS_NAME} ${GTEST_BOTH_LIBRARIES} Threads::Threads)

  enable_testing()
  add_test(general_tests ${PROJECT_TESTS_NAME})
endif (with-tests)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT ziminas1990@gmail.com)
include(CPack)
