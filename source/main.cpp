#include <iostream>
#include <boost/program_options.hpp>

#include "bayan.h"

namespace po = boost::program_options;

int main(int argc, char** argv)
{
    BayanSettings().hash;

    std::string testStr;
    int         TestInt = 0;

    po::options_description train_desc("bayan options\nПодсказка на https://habr.com/ru/post/174347/");
    train_desc.add_options()
            ("help,h", "Show help")
            ("test,T", po::value<std::string>(&testStr), "String test")
            ("int,I", po::value<int>(&TestInt), "Int test");

    po::variables_map vm;
    po::parsed_options parsed = po::command_line_parser(argc, argv).options(train_desc).allow_unregistered().run();

    po::store(parsed, vm);
    po::notify(vm);

    std::cout << train_desc << std::endl;

    std::cout << testStr << " " << TestInt << std::endl;

    return 0;
}
