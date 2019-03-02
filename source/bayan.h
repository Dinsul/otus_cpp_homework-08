#pragma once

#include <string>
#include <vector>

class BayanSettings
{
    BayanSettings() {}

public:
    size_t blockSize;
    enum class HashTypes
    {
        md5
    } hash;

    BayanSettings &operator ()();
};

class FileComparator
{
    std::string _filename;
    std::vector<std::string> _hashes;

    //TODO file descriptor
    size_t _size;
    size_t _seek;
    bool _isFull;
    bool _isOpen;

public:
    FileComparator();

    bool open();
    void close();

    bool operator == (FileComparator &other);

    bool isFull() const;
    bool isOpen() const;
    size_t size() const;
};
