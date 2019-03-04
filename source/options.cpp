#include <boost/program_options.hpp>
#include <iostream>

#include "options.h"


BayanSettings::BayanSettings() :
    blockSize(512 * 16),
    minSize(1024 * 1024 * 1024),
    deep(0),
    hash_type(HashTypes::md5)
{}

BayanSettings &BayanSettings::get()
{
    static BayanSettings bayanSettings;

    return bayanSettings;
}

bool intBayanOptions(int argc, char **argv, BayanSettings &settings)
{
    namespace po     = boost::program_options;
    using str_vector = std::vector<std::string>;

    po::options_description bayan_opt("bayan options");

    try
    {
        po::options_description required_opt("Required parameters");
        required_opt.add_options()
                ("scan,s",      po::value<str_vector>(&(settings.scanDir)),     "Directory for scanning.");

        po::options_description main_opt("Bayan options");
        main_opt.add_options()
                ("exclude,e",   po::value<str_vector>(&(settings.notScanDir)),  "Directory to exclude from scanning.")
                ("deep,D",      po::value<unsigned int>(&(settings.deep)),      "Deep of scanning.")
                ("minsize,m",   po::value<size_t>(&(settings.minSize)),         "Minimal file size to scanning.")
                ("blocksize,S", po::value<size_t>(&(settings.blockSize)),       "Size of block.");

        po::options_description help_opt("Help options\nПодсказка на https://habr.com/ru/post/174347/");
        help_opt.add_options()("help,h", "This screen.");

        po::variables_map vm;

        bayan_opt.add(required_opt);
        bayan_opt.add(main_opt);
        bayan_opt.add(help_opt);

        auto parsed = po::command_line_parser(argc, argv).options(bayan_opt).allow_unregistered().run();

        po::store(parsed, vm);

        if (!vm.count("scan") || vm.count("help"))
        {
          std::cout << "Basic command line parameter app" << std::endl
                    << bayan_opt << std::endl;

          return false;
        }

        po::notify(vm);
    }
    catch(std::exception& e)
    {
        std::cerr << "ERROR: " << e.what() << std::endl ;
        std::cerr << bayan_opt << std::endl;
        return false;
    }

    return true;
}
