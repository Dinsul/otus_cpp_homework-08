#include <iostream>
#include <boost/program_options.hpp>

using po = boost::program_options;

int main(int argc, char** argv)
{
    std::string testStr;
    int         TestInt;

    po::options_description desc("General options");
    desc.add_options()
      ("help,h", "Show help");

    po::options_description train_desc("Train options");
    train_desc.add_options()
      ("test,T", po::value<std::string>(), "Input .dat file");

    std::cout << testStr << std::endl;

    return 0;
}
