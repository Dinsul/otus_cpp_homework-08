cmake_minimum_required(VERSION 3.2)

if ($ENV{TRAVIS_BUILD_NUMBER})
    project(bayan VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else ()
    project(bayan VERSION 0.0.0)
endif ()

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
                   "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include("${CMAKE_BINARY_DIR}/conan.cmake")

message(STATUS "Run 'conan install ...'")
conan_cmake_run(REQUIRES
    boost/1.68.0@conan/stable
    OPTIONS boost:shared=True
    BASIC_SETUP CMAKE_TARGETS
    BUILD missing)


include(${PROJECT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_custom_target(travis SOURCES ".travis.yml")

set(Boost_USE_STATIC_LIBS        OFF)
set(Boost_USE_MULTITHREADED      ON)

include_directories("${CONAN_INCLUDE_DIRS}" "${CMAKE_SOURCE_DIR}")

add_executable(${PROJECT_NAME} "main.cpp" "${PROJECT_NAME}.cpp" "${PROJECT_NAME}.h")
add_executable(test_${PROJECT_NAME} "test_${PROJECT_NAME}.cpp" "${PROJECT_NAME}.cpp" "${PROJECT_NAME}.h")

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
    )

target_link_libraries(${PROJECT_NAME}
    ${CONAN_LIBS}
    )

target_link_libraries(test_${PROJECT_NAME}
    ${CONAN_LIBS}
    )

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT dinsul2.0@gmail.com)

include (CPack)

enable_testing()

add_test(test_1 "bin/test_${PROJECT_NAME}")
