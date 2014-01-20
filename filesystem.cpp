#include <iostream>
#include <boost/filesystem.hpp>
#include <string>

#include "filesystem.hpp"

namespace filesystem
{
    bool is_file(const std::string& s)
    {
        using namespace boost::filesystem;
        return is_regular_file(path(s));
    }
    
    std::string current_directory()
    {
        return boost::filesystem::current_path().string();
    }
    
    
}
