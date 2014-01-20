#include <iostream>
#include <string>
#include <sstream>
#include <time.h>

#include "timer_class.hpp"
#include "common.hpp"

using namespace std;

namespace
{
    template<class type1, class type2>
    inline type2 conv(const type1& t1)
    {
        stringstream ss;
        type2 t2;
        ss<< t1;
        ss>> t2;
        return t2;
    }
    
    inline string display_number(const int& x)
    {
        string disp("");
        if(x < 10)
        {
            disp += '0';
        }
        disp += conv<int, string>(x);
        return disp;
    }
    
    inline string display_timer(timer::timer_class& t)
    {
        string disp("");
        disp += display_number(t.hours_left());
        disp += " : ";
        disp += display_number(t.minutes_left());
        disp += (string(" : ") + display_number(t.seconds_left()) + "." + display_number(t.miliseconds_left()));
        return disp;
    }
}

void timer_setting(timer::timer_class& t)
{
    using namespace common;
    char ch;
    while(true)
    {
        cls();
        center("Settings");
        cout<< endl;
        for(short x = 0; x < 3; x++) cout<< endl;
        cout<< " 1 -  Time to count down: "<< t.get_time_set()<< endl; //write a time class to retrieve hours, minutes, etc.. from milisecs
    }
}

int main()
{
    return 0;
}