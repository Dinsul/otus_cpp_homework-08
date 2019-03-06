#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include <iostream>
#include <algorithm>

#include "bayan.h"
#include "options.h"

namespace bf = boost::filesystem;

bool getComparatorsFromSettings(std::list<FileComparator> &filenames)
{
    bf::path curPath;

    for(const auto &el : BayanSettings::get().scanDir)
    {
        curPath = bf::path(el).normalize();

        if (bf::exists(curPath))
        {
            try {
                addAllFilseFromDir(curPath, filenames, BayanSettings::get().deep);
            }
            catch (const bf::filesystem_error& ex)
            {
                std::cerr << ex.what() << std::endl;
            }
        }
    }

    return true;
}

void addAllFilseFromDir(const boost::filesystem::path &dir,
                        std::list<FileComparator> &filenames,
                        size_t deep)
{
    bf::directory_iterator it{dir};

    if (bf::is_directory(dir))
    {
        while (it != bf::directory_iterator{})
        {
            if (bf::is_regular_file(it->path()) && bf::file_size(it->path()) >= BayanSettings::get().minSize)
            {
                filenames.emplace_back(bf::complete(it->path()).normalize().string());
            }

            if (bf::is_directory(it->path()) && deep)
            {
                // Проверяем нету ли текущей директории в списке исключения.
                if (std::find_if(BayanSettings::get().notScanDir.begin(),
                                 BayanSettings::get().notScanDir.end(),
                                 [&it](std::string &el) {

                                 auto first  = bf::absolute(it->path()).normalize().string();
                                 auto second = bf::absolute(bf::path(el)).normalize().string();

                                 return first == second ;}) == BayanSettings::get().notScanDir.end())
                {
                    addAllFilseFromDir(it->path(), filenames, deep - 1);
                }
            }

            ++it;
        }

    }
}
