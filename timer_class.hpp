#ifndef TIMER_CLASS_HPP_INCLUDED
#define TIMER_CLASS_HPP_INCLUDED
#include <iostream>
#include <time.h>
#include <string>
#include <fstream>

#include "filesystem.hpp"

namespace timer
{
    class clock_class;
    class timer_class;
    
    /** iostream operators for fil streams: */
    std::istream& operator>>(std::istream&, clock_class&);
    std::ostream& operator<<(std::ostream&, clock_class&);
    
    std::ostream& operator<<(std::ostream&, timer_class&);
    std::istream& operator>>(std::istream&, timer_class&);
    
    struct time_data
    {
        clock_t hours, minutes, seconds;
    };
    
    class clock_class
    {
    public:
        explicit clock_class(const clock_t& ti) : t(ti) {}
        explicit clock_class() : t() {}
        
        ~clock_class(){}
        
        void operator=(const clock_class& c)
        {
            if(this != &c)
            {
                this->t = c.t;
            }
        }
        
        bool operator==(const clock_class& c) const
        {
            return (this->t == c.t);
        }
        
        bool operator<(const clock_class& c) const
        {
            return (this->t < c.t);
        }
        
        bool operator<=(const clock_class& c) const
        {
            return (this->t <= c.t);
        }
        
        bool operator>(const clock_class& c) const
        {
            return (this->t > c.t);
        }
        
        bool operator>=(const clock_class& c) const
        {
            return (this->t >= c.t);
        }
        
        /* Total hours stored in this class. */
        int hours() const
        {
            return (this->t / (CLOCKS_PER_SEC * 60 * 60));
        }
        
        /* Total minutes stored in this class */
        int minutes() const
        {
            return (this->t / (CLOCKS_PER_SEC * 60));
        }
        
        /* Total seconds stored in this class */
        int seconds() const
        {
            return (this->t / CLOCKS_PER_SEC);
        }
        
        /* total miliseconds stored in this class */
        int miliseconds() const
        {
            return (this->t / 10);
        }
        
        /* Display the time in hours, minutes, seconds, and miliseconds as 
         a calculated, read-able time. */
        std::string display() const;
        
        friend std::istream& operator>>(std::istream&, clock_class&);
        friend std::ostream& operator<<(std::ostream&, clock_class&);
        
        friend class timer_class;
        
    private:
        clock_t t;
        
    };
    
    class timer_class
    {
    public:
        explicit timer_class(const time_data& td) : start_time(clock()), time_length(this->use_data(td)) {}
        explicit timer_class() : start_time(clock()), time_length(clock()) {}
        ~timer_class(){}

        void operator=(const timer_class& t)
        {
            if(this != &t)
            {
                this->start_time = t.start_time;
                this->time_length = t.time_length;
            }
        }

        /* Sets the end_time to (i) seconds. */
        void set(const unsigned int& i)
        {
            this->time_length = (i * CLOCKS_PER_SEC);
        }

        /* Starts the timer by setting the start_time
         to the current time.*/
        void start()
        {
            this->start_time = clock();
        }
        
        /* Returns the time for which the timer will run */
        clock_class get_time_set() const
        {
            return clock_class(this->time_length);
        }
        
        /* Returns the time which the timer shoudl end. */
        clock_class get_end_time() const
        {
            return clock_class((this->start_time + this->time_length));
        }
        
        /* Returns the amount of time that has passed since
         the timer was started.  Best used as a chronograph.*/
        clock_class time_passed() const
        {
            return clock_class((clock() - this->start_time));
        }
        
        /* Calculates the time left in hours, minutes, and seconds.  Returns
         a string that is a easy-to-read display. */
        std::string display_time_left() const
        {
            return clock_class(((this->start_time + this->time_length) - clock())).display();
        }
        
        bool finished() const
        {
            return (((this->start_time + this->time_length) - clock()) <= 0);
        }
        
        /* Returns a data structure which contains hours minutes and seconds. */
        time_data get_time_data() const
        {
            time_data td;
            td.hours = ((((this->time_length / CLOCKS_PER_SEC)/ 60) / 60));
            td.minutes = (((this->time_length / CLOCKS_PER_SEC) / 60) % 60);
            td.seconds = ((this->time_length / CLOCKS_PER_SEC) % 60);
            return td;
        }
        
        //file stream functions are our friends!  ;)
        friend std::ostream& operator<<(std::ostream&, timer_class&);
        friend std::istream& operator>>(std::istream&, timer_class&);
        
    private:
        
        //variables:
        clock_t start_time, time_length;
        
        //functions:
        clock_t use_data(const time_data& td)
        {
            clock_t newt(0);
            newt += (td.hours * 60 * 60);
            newt += (td.minutes * 60);
            newt += td.seconds;
            newt *= CLOCKS_PER_SEC;
            return newt;
        }
        
        int seconds_left() const
        {
            using namespace std;
            clock_t tempc((this->time_length + this->start_time) - clock());
            return (tempc / CLOCKS_PER_SEC);
        }

        int minutes_left() const
        {
            using namespace std;
            clock_t tempc((this->time_length + this->start_time) - clock());
            return ((tempc / CLOCKS_PER_SEC) / 60);
        }

        int hours_left() const
        {
            using namespace std;
            clock_t tempc((this->time_length + this->start_time) - clock());
            return (tempc / (CLOCKS_PER_SEC * 60 * 60));
        }

        int miliseconds_left() const
        {
            using namespace std;
            clock_t tempc((this->time_length + this->start_time) - clock());
            return ((tempc % CLOCKS_PER_SEC) / 10);
        }
    };
    
    namespace file
    {
        inline void save(timer_class& t)
        {
            std::string file((filesystem::current_directory() + "\\timer settings.dat"));
            std::ofstream out;
            out.open(file.c_str(), std::ios::out);
            out<< t;
            out.close();
        }
        
        inline void load(timer_class& t)
        {
            std::ifstream in;
            std::string file((filesystem::current_directory() + "\\timer settings.dat"));
            
            if(!filesystem::is_file(file))
            {
                t = timer_class();
                return;
            }
            in.open(file.c_str(), std::ios::in);
            in>> t;
            in.close();
        }
    }
}

#endif