#pragma once

#include <list>

namespace boost::filesystem {
class path;
}

class FileComparator;

bool getComparatorsFromSettings(std::list<FileComparator> &filenames);

void addAllFilseFromDir(const boost::filesystem::path &dir,
                        std::list<FileComparator> &filenames,
                        size_t deep);
