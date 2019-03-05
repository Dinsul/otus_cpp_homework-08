#include <iostream>

#include "options.h"
#include "filecomparator.h"
#include "bayan.h"

int main(int argc, char** argv)
{
    if (!intBayanOptions(argc, argv, BayanSettings::get())) {
        return 1;
    }

    std::list<FileComparator> list;

    getComparatorsFromSettings(list);

    for (auto first = list.begin(); first != list.end(); )
    {
        for (auto second = first; second != list.end(); )
        {
            ++second;
            if (*first == *second)
            {
                std::cout << first->getFilename()
                          << " == " << second->getFilename()
                          << std::endl;
            }

        }

        ++first;
    }

//    for (auto &el : list)
//    {

//        std::cout << el << std::endl;
//    }

/*123.654 [pos]

            -->*/

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
