#ifndef TIMER_CLASS_HPP_INCLUDED
#define TIMER_CLASS_HPP_INCLUDED
#include <iostream>
#include <time.h>
#include <string>

namespace timer
{
    class clock_class;
    class timer_class;
    
    /** iostream operators for fil streams: */
    std::istream& operator>>(std::istream&, clock_class&);
    std::ostream& operator<<(std::ostream&, clock_class&);
    
    
    
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
        
        int hours() const
        {
            return (this->t / (CLOCKS_PER_SEC * 60 * 60));
        }
        
        int minutes() const
        {
            return (this->t / (CLOCKS_PER_SEC * 60));
        }
        
        int seconds() const
        {
            return (this->t / CLOCKS_PER_SEC);
        }
        
        int miliseconds() const
        {
            return (this->t / 10);
        }
        
        std::string display() const;
        
        /*
        const std::clock_t& gclock() const
        {
            return this->t;
        }*/
        
        friend std::istream& operator>>(std::istream&, clock_class&);
        friend std::ostream& operator<<(std::ostream&, clock_class&);
        
    private:
        clock_t t;
        
    };
    
    class timer_class
    {
    public:
        explicit timer_class() : start_time(clock()), time_length(clock()) {}
        ~timer_class(){}

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
        
        unsigned long int get_time_set() const
        {
            return this->time_length;
        }

    private:
        clock_t start_time, time_length;
    };
}

#endif