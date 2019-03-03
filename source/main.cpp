#include <iostream>
#include <boost/program_options.hpp>
#include <iostream>

#include "bayan.h"

namespace po = boost::program_options;

int main(int argc, char** argv)
{
    std::string testStr;
    int         TestInt = 0;

    if (argc < 3)
    {
        std::cout << "Usage: bayan <filename1> <filename2>" << std::endl;
        return 1;
    }

    FileComparator fc1(argv[1]);
    FileComparator fc2(argv[2]);

    std::cout << (fc1 == fc2 ? "true" : "false") << std::endl;


    po::options_description train_desc("bayan options\nПодсказка на https://habr.com/ru/post/174347/");
    train_desc.add_options()
            ("help,h", "Show help")
            ("test,T",      po::value<std::string>(&testStr), "String test")
            ("scan,s",      po::value<std::vector<std::string> >(&(BayanSettings::get().scanDir)),  "Directory for scanning.")
            ("exclude,e",   po::value<std::vector<std::string> >(&(BayanSettings::get().scanDir)),  "Directory to exclude from scanning.")
            ("deep,D",      po::value<unsigned int>(&(BayanSettings::get().deep)),                  "Deep of scanning.")
            ("minsize,m",   po::value<size_t>(&(BayanSettings::get().minSize)),                     "Minimal file size to scanning.")
            ("blocksize,S", po::value<size_t>(&(BayanSettings::get().blockSize)),                   "Size of block.")
            ("int,I",       po::value<int>(&TestInt), "Int test");

    po::variables_map vm;
    po::parsed_options parsed = po::command_line_parser(argc, argv).options(train_desc).allow_unregistered().run();

    po::store(parsed, vm);
    po::notify(vm);

    std::cout << train_desc << std::endl;

    std::cout << testStr << " " << TestInt << std::endl;

    return 0;
}
