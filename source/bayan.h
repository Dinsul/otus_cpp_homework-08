#pragma once

#include <list>
#include <string>

#include <filecomparator.h>

namespace boost::filesystem {
class path;
}

bool getComparatorsFromSettings(std::list<FileComparator> &filenames);

void addAllFilseFromDir(const boost::filesystem::path &dir,
                        std::list<FileComparator> &filenames,
                        size_t deep);
