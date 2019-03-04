#pragma once

#include <string>
#include <vector>

class BayanSettings
{
    BayanSettings();

public:
    size_t blockSize;
    size_t minSize;
    unsigned int deep;

    enum class HashTypes
    {
        unknown,
        md5
    } hash_type;

    std::vector<std::string> scanDir;
    std::vector<std::string> notScanDir;

    static BayanSettings &get ();
};

bool intBayanOptions(int argc, char **argv, BayanSettings &settings);
