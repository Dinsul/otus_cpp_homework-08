#include <iostream>

#include "options.h"
#include "filecomparator.h"


int main(int argc, char** argv)
{
    if (!intBayanOptions(argc, argv, BayanSettings::get())) {
        return 1;
    }
//    if (argc < 3)
//    {
//        std::cout << "Usage: bayan <filename1> <filename2>" << std::endl;
//        return 1;
//    }

    FileComparator fc1(BayanSettings::get().scanDir[0]);
    FileComparator fc2(BayanSettings::get().scanDir[1]);

    std::cout << (fc1 == fc2 ? "true" : "false") << std::endl;

//    std::cout << desc << std::endl;

    std::cout << "deep:      " << BayanSettings::get().deep      << "\n"
              << "minSize:   " << BayanSettings::get().minSize   << "\n"
              << "blockSize: " << BayanSettings::get().blockSize << "\n";


    std::cout << "Scan dirs:\n";
    for (auto &el : BayanSettings::get().scanDir)
    {
        std::cout << "\t" << el << "\n";
    }

    std::cout << "Not scan dirs:\n";
    for (auto &el : BayanSettings::get().notScanDir)
    {
        std::cout << "\t" << el << "\n";
    }

    std::cout << std::endl;

    return 0;
}
