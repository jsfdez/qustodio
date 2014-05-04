#include "activity.h"

#include <ios>
#include <iostream>

std::istream& operator>>(std::istream &is, Activity &a)
{
    std::string key;
    is >> key >> a.address;
    if (key != "device:")
    {
        is.setstate(std::ios_base::failbit);
        return is;
    }
    is >> key >> a.url;
    if (key != "url:")
    {
        is.setstate(std::ios_base::failbit);
        return is;
    }
    is >> key >> a.timestamp;
    if (key != "timestamp:")
        is.setstate(std::ios_base::failbit);
    return is;
}

std::ostream& operator<<(std::ostream &os, const Activity &a)
{
    os << "{address: " << a.address << ", url: " << a.url << ", timestamp: "
        << a.timestamp << "}" << std::endl;
    return os;
}
