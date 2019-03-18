#include <iostream>
#include <algorithm>
#include <openssl/md5.h>
#include <memory.h>

#include "filecomparator.h"
#include "options.h"

#if (__unix)
# include <sys/stat.h>
# include <errno.h>

size_t getFileSize(const char *filename)
{
    struct stat st;
    if (stat(filename, &st) < 0)
    {
        std::cerr << "Can not get fileinfo. Err:\"" << strerror(errno) << std::endl;

        return 0;
    }

    return static_cast<size_t>(st.st_size);
}

#elif (WIN32)
# include <Windows.h>

size_t getFileSize(const char *filename)
{
    auto hFile = CreateFile(filename,
                       GENERIC_READ,
                       0,
                       nullptr,
                       OPEN_EXISTING,
                       FILE_ATTRIBUTE_NORMAL,
                       nullptr);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        std::cerr << "hFile is NULL" << std::endl;
        return 0;
    }

    size_t size = GetFileSize(hFile, nullptr);

    CloseHandle(hFile);

    return size;
}

#else

size_t getFileSize(const char *filename)
{
    FILE *f;

    fopen(filename, "r");
    fseek(f, 0, SEEK_END);

    size_t size = ftell(f);

    fclose(f);

    return size;
}
#endif



bool FileComparator::isOpen() const
{
    return _isOpen;
}

size_t FileComparator::size() const
{
    return _size;
}

size_t FileComparator::seek() const
{
    return _seek;
}

const std::string &FileComparator::getFilename() const
{
    return _filename;
}

FileComparator::FileComparator(const std::string &filename) :
    _filename(filename),
    _isFull(false),
    _isOpen(false),
    _size(getFileSize(filename.c_str())),
    _seek(0),
    _file(nullptr, [](FILE*)->int{return 0;})
{}

bool FileComparator::createNextHash(size_t size, std::string &hash)
{
    unsigned char *bulkData;

    if (_seek < _size && open())
    {
        bulkData = new unsigned char[size];

        fseek(_file.get(), static_cast<long>(_seek), SEEK_SET);

        auto readSize = fread(bulkData, 1, size, _file.get());

        _seek += readSize;

        if (_seek >= _size)
        {
            _isFull = true;
        }

        if (readSize < size)
        {
            memset(bulkData + readSize, 0, size - readSize);
        }

        hash = createHash(bulkData, size);

        _hashes.emplace_back(hash);

        delete [] bulkData;

        return true;
    }

    hash = std::string();

    return false;
}

bool FileComparator::getHash(size_t num, std::string &hash) const
{
    if (num < _hashes.size()) {
        hash = _hashes[num];
        return true;
    }

    return false;
}

bool FileComparator::open()
{
    if (!_file.get())
    {
        _file.release();
        _file = std::unique_ptr<FILE, int(*)(FILE*)>(fopen(_filename.c_str(), "r"), fclose);

        if (_file)
        {
            _isOpen = true;
        }
    }

    return _isOpen;
}

void FileComparator::close()
{
    _file.release();

    _isOpen = false;
}

bool FileComparator::operator ==(FileComparator &other)
{
    if (size() == other.size())
    {
        if (size() == 0)
        {
            return true;
        }

        size_t counter = 0;

        do
        {
            std::string hash1;
            std::string hash2;

            if (!this->getHash(counter, hash1))
            {
                this->createNextHash(BayanSettings::get().blockSize, hash1);
            }

            if (!other.getHash(counter, hash2))
            {
                other.createNextHash(BayanSettings::get().blockSize, hash2);
            }

            if (!std::equal(hash1.begin(), hash1.end(), hash2.begin()))
            {
                return false;
            }

            ++counter;
        }
        while (!(this->isFull()) || !(other.isFull()));

        return true;
    }

    return false;
}

bool FileComparator::isFull() const
{
    return _isFull;
}

std::string createHash(const unsigned char *data, size_t size)
{
    switch (BayanSettings::get().hash_type)
    {
    case BayanSettings::HashTypes::md5:
        unsigned char md5[MD5_DIGEST_LENGTH];

        MD5(data, size, md5);

        char mdString[MD5_DIGEST_LENGTH * 2 + 1];

        mdString[MD5_DIGEST_LENGTH * 2] = 0;

        for(int i = 0; i < 16; ++i){
            sprintf(&mdString[i * 2], "%02x", static_cast<unsigned int>(md5[i]));
        }
        return std::string(mdString);

    default:
        break;
    }

    return std::string();
}
