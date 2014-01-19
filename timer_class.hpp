#ifndef TIMER_CLASS_HPP_INCLUDED
#define TIMER_CLASS_HPP_INCLUDED
#include <time.h>

namespace timer
{
    class timer_class
    {
    public:
        explicit timer_class() : start_time(std::clock()), time_length(std::clock()) {}
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
            this->end_time = (i * CLOCKS_PER_SEC);
        }

        /* Starts the timer by setting the start_time
         to the current time.*/
        void start()
        {
            this->start_time = std::clock();
        }
        
        unsigned long int get_time_set() const
        {
            return this->timer_length;
        }

    private:
        std::clock_t start_time, time_length;
    };
}

#endif