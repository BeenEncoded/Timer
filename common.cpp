#include <iostream>
#include "common.hpp"
#include <string>
#include <conio.h>
#include "global_defines.hpp"

using namespace std;

namespace
{
    inline bool char_match(const char& ch, const string& s)
    {
        for(string::const_iterator it = s.begin(); it != s.end(); ++it)
        {
            if(ch == *it)
            {
                return true;
            }
        }
        return false;
    }
}

namespace common
{
    
    bool is_letter(const char& ch)
    {
        return char_match(ch, LETTERS);
    }
    
    bool is_number(const char& ch)
    {
        return char_match(ch, NUMBERS);
    }
    
    bool is_special(const char& ch)
    {
        return char_match(ch, SPECIALS);
    }
    
    bool is_char(const char& ch)
    {
        return (is_letter(ch) || is_number(ch) || is_special(ch));
    }
    
    namespace input
    {
        string get_user_string(const string& message)
        {
            char ch;
            string input("");
            while(true)
            {
                cls();
                for(short x = 0; x < 10; x++) cout<< endl;
                cout<< ((message.size() > 0) ? message : ">> ");
                cout<< input;
                common::input::ccin();
                
                do
                {
                    ch = gkey();
                    switch(is_control_char(ch))
                    {
                        case false:
                        {
                            switch(is_char(ch))
                            {
                                case true:
                                {
                                    input += ch;
                                }
                                break;
                                
                                case false:
                                {
                                    switch(int(ch))
                                    {
                                        case ENTER_KEY:
                                        {
                                            return input;
                                        }
                                        break;
                                        
                                        case BACKSPACE_KEY:
                                        {
                                            if(input.size() > 0)
                                            {
                                                input.resize((input.size() - 1));
                                            }
                                        }
                                        break;
                                                    
                                        case ESCAPE_KEY:
                                        {
                                            input.erase();
                                            return GSTRING_CANCEL;
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
                        break;
                        
                        default:
                        {
                        }
                        break;
                    }
                }
                while(kbhit());
                
            }
            return GSTRING_CANCEL;
        }
        
        
    }
}