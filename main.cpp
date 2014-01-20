#include <iostream>
#include <string>
#include <sstream>
#include <time.h>
#include <conio.h>
#include <windows.h>

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
    
    inline void set_time(timer::timer_class& t)
    {
        using namespace common;
        timer::time_data tdata = t.get_time_data();
        char ch;
        while(true)
        {
            cls();
            cout<< endl;
            center("Set Timer");
            cout<< endl;
            for(short x = 0; x < 3; x++) cout<< endl;
            cout<< " 1 -  Hours: "<< tdata.hours<< endl;
            cout<< " 2 -  Minutes: "<< tdata.minutes<< endl;
            cout<< " 3 -  Seconds: "<< tdata.seconds<< endl;
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
                            input::guser_string_toany("Enter number of hours: ", tdata.hours);
                        }
                        break;
                        
                        case '2':
                        {
                            input::guser_string_toany("Enter number of minutes: ", tdata.minutes);
                        }
                        break;
                        
                        case '3':
                        {
                            input::guser_string_toany("Enter number of seconds: ", tdata.seconds);
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
                            t = timer::timer_class(tdata);
                            timer::file::save(t);
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
    }
    
    /* Main settings menu for setting the timer. */
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

inline void run_timer(timer::timer_class& t)
{
    using namespace common;
    t.start();
    cl();
    while(!kbhit())
    {
        cls();
        for(short x = 0; x < 10; x++) cout<< endl;
        center(t.display_time_left());
        Sleep((1000 / 30));
        if(t.finished())
        {
            Beep(1500, 150);
        }
    }
}

inline void main_menu()
{
    using namespace common;
    timer::timer_class t;
    timer::file::load(t);
    char ch;
    while(true)
    {
        cls();
        cout<< endl;
        center("Timer");
        cout<< endl;
        for(short x = 0; x < 3; x++) cout<< endl;
        cout<< " 1 -  Start Timer"<< endl;
        cout<< " 2 -  Set timer"<< endl;
        cout<< endl;
        cout<< " q -  Exit"<< endl;
        ch = input::gkey();
        switch(tolower(ch))
        {
            case '1':
            {
                run_timer(t);
            }
            break;
            
            case '2':
            {
                timer_setting(t);
            }
            break;
            
            case 'q':
            {
                return;
            }
            break;
            
            default:
                break;
        }
    }
}

int main()
{
    main_menu();
    return 0;
}