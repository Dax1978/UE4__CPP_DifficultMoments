#pragma once

#include <iostream>
#include <chrono>

class Time
{
private:
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1> >;

    std::string m_name;
    std::chrono::time_point<clock_t> m_beg;
    double delta_time = 0.0;

public:
    Time() : m_beg(clock_t::now()) { }
    Time(std::string name) : m_name(name), m_beg(clock_t::now()) { }

    double elapsed();
    void start(std::string name);
    void print();
    double get_time();
};
