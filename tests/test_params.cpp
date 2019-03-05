#define BOOST_TEST_MODULE test_bayan

#include "filecomparator.h"
#include <iostream>

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#define TEST_BUFFER_SIZE 1024 * 1024 * 3

BOOST_AUTO_TEST_SUITE(test_suite_bayan)

BOOST_AUTO_TEST_CASE(test_1)
{
    FILE * testFile;
    FILE * random;
    char buffer[TEST_BUFFER_SIZE];

    random = fopen("/dev/urandom", "r");

    BOOST_CHECK(random != nullptr);

    fread(buffer, 1, TEST_BUFFER_SIZE, random);

    fclose(random);

    testFile = fopen("/tmp/test.random", "w");

    BOOST_CHECK(testFile != nullptr);

    fwrite(buffer, 1, TEST_BUFFER_SIZE, testFile);

    fclose(testFile);


    FileComparator fc1{"/tmp/test.random"};
    FileComparator fc2{"/tmp/test.random"};


    BOOST_CHECK(fc1 == fc2);

    fc1.close();
    fc2.close();

    boost::filesystem::path to_delete;

    boost::filesystem::remove(to_delete);
}

BOOST_AUTO_TEST_SUITE_END()
