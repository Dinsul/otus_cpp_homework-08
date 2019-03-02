#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include <iostream>

#include "bayan.h"

using bf = boost::filesystem;


BayanSettings &BayanSettings::operator ()()
{
    static BayanSettings bayanSettings;

    return &bayanSettings;
}

bool FileComparator::isOpen() const
{
    return _isOpen;
}

size_t FileComparator::size() const
{
    return _size;
}

bool FileComparator::operator ==(FileComparator &other)
{
    if (size() == other.size())
    {
        //Погнали

    }

    return false;
}

bool FileComparator::isFull() const
{
    return _isFull;
}
