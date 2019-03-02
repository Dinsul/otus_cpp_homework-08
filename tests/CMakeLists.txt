
link_directories(${CONAN_LIBS} "${CMAKE_BINARY_DIR}/lib")

link_libraries(${CONAN_LIBS})

add_executable("test_params"
    "test_params.cpp"
    )

enable_testing()

#add_test(test_1 "test_${PROJECT_NAME}")
