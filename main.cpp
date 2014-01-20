#include <iostream>
#include <string>
#include <sstream>
#include <time.h>

#include "timer_class.hpp"
#include "common.hpp"
#include "filesystem.hpp"

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
    
    /*
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
    }*/
    
    inline void set_time(timer::timer_class& t)
    {
        using namespace common;
        timer::time_data tdata;
        char ch;
        while(true)
        {
            cls();
            cout<< endl;
            center("Set Timer");
            cout<< endl;
            for(short x = 0; x < 3; x++) cout<< endl;
            cout<< " 1 -  Hours: "<< t.get_time_set().hours()<< endl;
            cout<< " 2 -  Minutes: "<< (t.get_time_set().minutes() % 60)<< endl;
            cout<< " 3 -  Seconds: "<< (t.get_time_set().seconds() % 60)<< endl;
            cout<< endl;
            cout<< " [BACKSPACE] -  Done"<< endl;
            
            ch = input::gkey();
            switch(is_char(ch))
            {
                case true:
                {
                    switch(ch)
                    {
                        case '1':
                        {
                        }
                        break;
                        
                        case '2':
                        {
                        }
                        break;
                        
                        case '3':
                        {
                        }
                        break;
                        
                        default:
                            break;
                    }
                }
                break;
                
                case false:
                {
                    switch(int(ch))
                    {
                        case BACKSPACE_KEY:
                        {
                            return;
                        }
                        break;
                        
                        default:
                            break;
                    }
                }
                break;
                
                default:
                    break;
            }
        }
        return false;
    }
    
    inline void timer_setting(timer::timer_class& t)
    {
        using namespace common;
        char ch;
        while(true)
        {
            cls();
            center("Settings");
            cout<< endl;
            for(short x = 0; x < 3; x++) cout<< endl;
            cout<< " 1 -  Time to count down: "<< t.get_time_set().display()<< endl;
            cout<< " [BACKSPACE] -  Done"<< endl;

            ch = input::gkey();
            switch(is_char(ch))
            {
                case true:
                {
                    switch(ch)
                    {
                        case '1':
                        {
                            set_time(t);
                        }
                        break;

                        default:
                        {
                        }
                        break;
                    }
                }
                break;

                case false:
                {
                    switch(int(ch))
                    {
                        case BACKSPACE_KEY:
                        {
                            return;
                        }
                        break;

                        default:
                        {
                        }
                        break;
                    }
                }
                break;

                default:
                {
                }
                break;
            }
        }
    }
}

int main()
{
    return 0;
}