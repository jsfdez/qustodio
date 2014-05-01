#pragma once

#include <string>

struct Activity
{
    std::string address;
    std::string url;
    time_t timestamp;
};

std::istream& operator>>(std::istream &is, Activity &a);
std::ostream& operator<<(std::ostream &os, const Activity &a);
