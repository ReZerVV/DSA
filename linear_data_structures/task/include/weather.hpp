#ifndef WEATHER_H_
#define WEATHER_H_

#include <stddef.h>

enum wdir_t : uint8_t {
    N   = 0,
    NE  = 1,
    E   = 2,
    SE  = 3,
    S   = 4,
    SW  = 5,
    W   = 6,
    NW  = 7
};

const char* wdir_t_to_string(const wdir_t& dir) {
    
}

enum month_t : uint8_t {
    January     = 0, 
    February    = 1,
    March       = 2,
    April       = 3,
    May         = 4,
    June        = 5,
    July        = 6,
    August      = 7,
    September   = 8,
    October     = 9,
    November    = 10,
    December    = 11
};

const char* month_t_to_string(const month_t &month) {
    switch (month) {
    case month_t::January:
        return "January";
        break;
    case month_t::February:
        return "February";
        break;
    case month_t::March:
        return "March";
        break;
    case month_t::April:
        return "April";
        break;
    case month_t::May:
        return "May";
        break;
    case month_t::June:
        return "June";
        break;
    case month_t::July:
        return "July";
        break;
    case month_t::August:
        return "August";
        break;
    case month_t::September:
        return "September";
        break;
    case month_t::October:
        return "October";
        break;
    case month_t::November:
        return "November";
        break;
    case month_t::December:
        return "December";
        break;
    }
}

struct date_t {
    size_t  _day;
    month_t _month;
    size_t  _year;
};

struct weather_t {
    date_t  _date;
    size_t  _temperature;
    wdir_t  _wind_direction;
    size_t  _wind_force;
    size_t  _pressure;
    bool    _rain;
};

#endif // WEATHER_H_