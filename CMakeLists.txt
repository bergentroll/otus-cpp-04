cmake_minimum_required(VERSION 3.12.4)

if($ENV{TRAVIS_BUILD_NUMBER})
  set(VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
  set(VERSION 0.0.0)
endif()
project(print_ip VERSION ${VERSION})

set(CMAKE_CXX_STANDARD 17)

### Dependencies ##############################################################

set(GTEST_SRCDIR "/usr/src/gtest/")
set(SRC_PATH "src/")
set(TEST_PATH "test/")
include_directories("inc/")
find_package(Doxygen COMPONENTS dot)

### Main targets ##############################################################

add_executable(print_ip ${SRC_PATH}/main.cpp)

### Tests #####################################################################

if(EXISTS "${GTEST_SRCDIR}/CMakeLists.txt")
  add_subdirectory(${GTEST_SRCDIR}/ ${CMAKE_BINARY_DIR}/gtest/ EXCLUDE_FROM_ALL)

  add_executable(test_suite ${TEST_PATH}/test.cpp)
  target_link_libraries(
    test_suite
    PRIVATE
    gtest)
  add_test(test_suite test_suite)
else()
  message(
    WARNING
    "Test suite will not be launched because GTest sources is not found at "
    "${GTEST_SRCDIR}.")
endif()

# Attribution https://stackoverflow.com/a/30191576/7486328
add_executable(test_static_assert_1 ${TEST_PATH}/test_static_asserts.cpp)
add_executable(test_static_assert_2 ${TEST_PATH}/test_static_asserts.cpp)
set_target_properties(
  test_static_assert_1 test_static_assert_2
  PROPERTIES
  EXCLUDE_FROM_ALL TRUE
  EXCLUDE_FROM_DEFAULT_BUILD TRUE)
target_compile_definitions(test_static_assert_1 PRIVATE TEST1)
target_compile_definitions(test_static_assert_2 PRIVATE TEST2)
add_test(
  NAME test_static_assert_1
  COMMAND ${CMAKE_COMMAND} --build . --target test_static_assert_1
    --config $<CONFIGURATION>
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
add_test(
  NAME test_static_assert_2
  COMMAND ${CMAKE_COMMAND} --build . --target test_static_assert_2
    --config $<CONFIGURATION>
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
set_tests_properties(
  test_static_assert_1 test_static_assert_2
  PROPERTIES WILL_FAIL TRUE)

enable_testing()

### Documentation #############################################################

if(DOXYGEN_FOUND)
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    @ONLY)
  add_custom_target(
    html
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Creating HTML documentation with Doxygen" VERBATIM)
endif()

### Packing ###################################################################

install(TARGETS print_ip RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_CONTACT bergentroll@insiberia.net)
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>=2.15)")
include(CPack)
