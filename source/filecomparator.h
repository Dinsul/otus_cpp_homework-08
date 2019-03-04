#pragma once

#include <string>
#include <vector>
#include <memory>

std::string createHash(const unsigned char *data, size_t size);
size_t getFileSize(const char *filename);

class FileComparator
{
    std::string _filename;

    bool _isFull;
    bool _isOpen;
    size_t _size;
    size_t _seek;

    std::unique_ptr<FILE, int(*)(FILE*)> _file;
    std::vector<std::string> _hashes;

public:
    FileComparator(const std::string &filename);

    bool open();
    void close();

    bool operator == (FileComparator &other);

    bool isFull() const;
    bool isOpen() const;
    size_t size() const;
    size_t seek() const;

    bool createNextHash(size_t size, std::string &hash);
    bool getHash(size_t num, std::string &hash) const;
};
