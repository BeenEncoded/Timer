#include <iostream>
#include <time.h>
#include <sstream>
#include <fstream>
#include <string>

#include "timer_class.hpp"

using namespace std;

#define DATADELIM 1

namespace
{
    template<class type1, class type2>
    inline type2 conv(const type1& t1)
    {
        stringstream *ss(new stringstream());
        type2 t2;
        (*ss)<< t1;
        (*ss)>> t2;
        delete ss;
        return t2;
    }
}

namespace timer
{
    ostream& operator<<(ostream& out, clock_class& c)
    {
        out<< c.t<< char(DATADELIM);
        return out;
    }
    
    istream& operator>>(istream& in, clock_class& c)
    {
        cin.rdbuf()->in_avail();
        if(in.good())
        {
            string *temps(new string(""));
            getline(in, *temps, char(DATADELIM));
            if(!in.fail())
            {
                c.t = conv<string, clock_t>(*temps);
            }
            temps->erase();
            delete temps;
        }
        return in;
    }
}