#ifndef COMMON_HPP_INCLUDED
#define COMMON_HPP_INCLUDED
#include <string>
#include <windows.h>
#include <conio.h>

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
    
    bool is_letter(const char&);
    bool is_number(const char&);
    bool is_special(const char&);
    bool is_char(const char&);
    
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
        
        inline void gkey()
        {
            cl();
            return getch();
        }
        
        std::string get_user_string(const std::string&);
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