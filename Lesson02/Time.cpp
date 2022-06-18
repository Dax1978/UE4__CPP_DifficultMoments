#include <iostream>
#include <chrono>
#include "Time.hpp"

double Time::elapsed() {
    return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
}

void Time::start(std::string name) {
    m_name = name;
    m_beg = clock_t::now();
}

void Time::print() {
    delta_time = elapsed() * 1000;
    std::cout << m_name << ":\t" << delta_time << " ms" << '\n';
}

double Time::get_time() {
    return delta_time;
}