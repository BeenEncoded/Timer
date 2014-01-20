#ifndef FILESYSTEM_HPP_INCLUDED
#define FILESYSTEM_HPP_INCLUDED
#include <string>

namespace filesystem
{
    bool is_file(const std::string&);
    std::string current_directory();
}

#endif