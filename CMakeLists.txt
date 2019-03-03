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
    OpenSSL/1.0.2@conan/stable

    OPTIONS boost:shared=True
    BASIC_SETUP CMAKE_TARGETS
    BUILD missing)


include(${PROJECT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GLIBCXX_USE_CXX11_ABI=0")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "GNU")
#    set(CMAKE_CXX_FLAGS "-Wpedantic;-Wall;-Wextra")
#endif()

add_custom_target(travis SOURCES ".travis.yml")

set(Boost_USE_STATIC_LIBS        OFF)
set(Boost_USE_MULTITHREADED      ON)

include_directories("${CONAN_INCLUDE_DIRS}" "${CMAKE_SOURCE_DIR}/source")

add_subdirectory(source)
add_subdirectory(tests)
