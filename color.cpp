#include <iostream>
#include <string>

#include "color.hpp"
#include "concol.h"

using namespace std;

namespace
{
    inline void setcol(const eku::concol& text, const eku::concol& back)
    {
        if((eku::textcol != text) || (eku::backcol != back))
        {
            eku::setcolor(text, back);
        }
    }
    
    inline void highlight(const eku::concol& text, const eku::concol& back, const string& message)
    {
        eku::concol deftext(eku::textcol), defback(eku::backcol);
        setcol(text, back);
        cout<< message;
        setcol(deftext, defback);
    }
}

namespace color
{
    namespace set
    {
        void blackwhite()
        {
            setcol(eku::black, eku::white);
        }
        
        
    }
}