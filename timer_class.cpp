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
    
    /* Displays a number with preceding zeros if it doesn't have the specified
     number of digits:
     
     @digits: number of digits the number should be
     @i: number to display*/
    inline string display_number(const int& i, const short& digits)
    {
        string temps(conv<int, string>(i));
        while(temps.size() < unsigned(digits))
        {
            temps = ("0" + temps);
        }
        return temps;
    }
}

/** stream operators: */
namespace timer
{
    //clock_class:
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
    
    //Timer_class:
    ostream& operator<<(ostream& out, timer_class& t)
    {
        char delim(DATADELIM);
        out<< t.start_time<< delim;
        out<< t.time_length<< delim;
        return out;
    }
    
    istream& operator>>(istream& in, timer_class& t)
    {
        t = timer_class();
        char delim(DATADELIM);
        string *temps(new string(""));
        if(in.good())
        {
            getline(in, *temps, delim);
            if(!in.fail())
            {
                t.start_time = conv<string, clock_t>(*temps);
            }
        }
        temps->erase();
        if(in.good())
        {
            getline(in, *temps, delim);
            if(!in.fail())
            {
                t.time_length = conv<string, clock_t>(*temps);
            }
        }
        temps->erase();
        delete temps;
        return in;
    }
    
    
}

/** clock_class members: */
namespace timer
{
    string clock_class::display() const
    {
        string temps("");
        temps += (display_number(this->hours(), 2) + " : ");
        temps += (display_number((this->minutes() % 60), 2) + " : ");
        temps += (display_number((this->seconds() % 60), 2) + ".");
        temps += display_number((this->miliseconds() % 100), 2);
        return temps;
    }
    
}