#ifndef COMMON_HPP_INCLUDED
#define COMMON_HPP_INCLUDED
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <sstream>

#include "global_defines.hpp"

namespace common
{
    inline void cls()
    {
        HANDLE                     hStdOut;
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        DWORD                      count;
        DWORD                      cellCount;
        COORD                      homeCoords = { 0, 0 };

        hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
        if (hStdOut == INVALID_HANDLE_VALUE) return;

        /* Get the number of cells in the current buffer */
        if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
        cellCount = csbi.dwSize.X *csbi.dwSize.Y;

        /* Fill the entire buffer with spaces */
        if (!FillConsoleOutputCharacter(
             hStdOut,
            (TCHAR) ' ',
            cellCount,
            homeCoords,
            &count
          )) return;

        /* Fill the entire buffer with the current colors and attributes */
        if (!FillConsoleOutputAttribute(
          hStdOut,
          csbi.wAttributes,
          cellCount,
          homeCoords,
          &count
          )) return;

        /* Move the cursor home */
        SetConsoleCursorPosition( hStdOut, homeCoords );
    }
    
    inline void cl()
    {
        Sleep(10);
        while(kbhit()) getch();
    }
    
    inline void ccin()
    {
        std::cin.rdbuf()->in_avail();
    }
    
    bool is_letter(const char&);
    bool is_number(const char&);
    bool is_special(const char&);
    bool is_char(const char&);
    
    inline void center(const std::string& message)
    {
        int cent((int(HCENTER) - (message.size() / 2)));
        if(cent < 0)
        {
            cent = 0;
        }
        for(short x = 0; x < cent; x++) std::cout<< " ";
        std::cout<< message;
        ccin();
    }
    
    namespace input
    {
        inline bool is_control_char(const char& ch)
        {
            return (int(ch) <= 0);
        }
        
        inline void ccin()
        {
            std::cin.rdbuf()->in_avail();
        }
        
        inline char gkey()
        {
            cl();
            return getch();
        }
        
        std::string get_user_string(const std::string&);
        
        template<class type>
        inline void guser_string_toany(const std::string& s, type& t)
        {
            std::string *temps(new std::string(get_user_string(s)));
            std::stringstream *ss(new std::stringstream());
            if((*temps) != GSTRING_CANCEL)
            {
                (*ss)<< (*temps);
                (*ss)>> t;
            }
            temps->erase();
            delete ss;
            delete temps;
        }
    }
    
    inline void wait()
    {
        for(short x = 0; x < 3; x++) std::cout<< '\n';
        std::cout<< "Press anything to continue...\n";
        cl();
        getch();
        cl();
    }
    
    
}

#endif