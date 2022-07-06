////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Задание 2                                                                                                      //
// Реализовать функцию, возвращающую i-ое простое число (например, миллионное простое число равно 15485863).      //
// Вычисления реализовать во вторичном потоке. В консоли отображать прогресс вычисления (в основном потоке).      //
//                                                                                                                //
// Версия 2                                                                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// https://habr.com/ru/post/182610/?ysclid=l56yi28dcz441493065
// https://habr.com/ru/post/121244/?ysclid=l573r1hp2s203378141
// https://www.linux.org.ru/forum/development/13446634?ysclid=l572mi44lx199863375

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include "Timer.hpp"

#include "windows.h"

class pBar {
public:
    void update(double newProgress) {
        currentProgress += newProgress;
        amountOfFiller = (int)((currentProgress / neededProgress) * (double)pBarLength);
    }
    void clear() {
        currentProgress = 0;
    }
    void print() {
        currUpdateVal %= pBarUpdater.length();
        std::cout << "\r" //Bring cursor to start of line
            << firstPartOfpBar; //Print out first part of pBar
        for (int a = 0; a < amountOfFiller; a++) { //Print out current progress
            std::cout << pBarFiller;
        }
        std::cout << pBarUpdater[currUpdateVal];
        for (int b = 0; b < pBarLength - amountOfFiller; b++) { //Print out spaces
            std::cout << " ";
        }
        std::cout << lastPartOfpBar //Print out last part of progress bar
            << " (" << (int)(100 * (currentProgress / neededProgress)) << "%)" //This just prints out the percent
            << std::flush;
        currUpdateVal += 1;
    }
    std::string firstPartOfpBar = "[", //Change these at will (that is why I made them public)
        lastPartOfpBar = "]",
        pBarFiller = "|",
        pBarUpdater = "/-\\|";
private:
    int amountOfFiller,
        pBarLength = 50, //I would recommend NOT changing this
        currUpdateVal = 0; //Do not change
    double currentProgress = 0, //Do not change
        neededProgress = 100; //I would recommend NOT changing this
};

class PrimeNumber {
private:
    // Целое для хранения максимального значения ряда, в котором ищем простое число
    int maxValue;
    // Вектор для хранения найденных простых чисел
    std::vector<int> v;
    // Действительные для хранения значения текущего и предыдущего прогресса
    double curr_percent = 0.0;
    double prev_percent = 0.0;
    // Объект - прогресс выполнения поиска простых чисел
    pBar bar;

    std::recursive_mutex _lock;

    // Метод определяющий, является ли указанное число простым
    bool isPrime(int num) {
        int limit = num / 2;
        if (num > 2) {
            for (int i = 2; i <= limit; ++i) {
                if (num % i == 0) {
                    return false;
                }
            }
        }
        return true;
    }    

public:
    PrimeNumber(int max_value) : maxValue(max_value) { }
    // Метод поиска простых чисел и отображения прогресса поиска
    void find_prime_progress() {
        prev_percent = 0.0;
        double delta_percent = 0.0;
        for (size_t i = 0; i < maxValue; ++i) {
            if (isPrime(i)) { v.push_back(i); }
            double curr_percent = ((i + 1.0) / static_cast<double>(maxValue)) * 100.0;
            if (curr_percent - prev_percent >= 0.9999999) {
                delta_percent = curr_percent - prev_percent;
                bar.update(delta_percent);
                bar.print();
                prev_percent = curr_percent;
            }
        }
        std::cout << std::endl;
        print_result();
    }
    // Метод выводящий итоги поиска простых чисел в указанном ряду
    void print_result() {
        std::cout << "В диапазоне от 0 до " << maxValue << " количество простых чисел " << v.size() << std::endl;
        std::vector<int>::iterator iter = v.end() - 1;
        std::cout << "Последнее найденное простое число = " << *iter << std::endl;
    }
    // Метод сброса свойств в исходное состояние
    void clear_v() {
        bar.clear();
        v.clear();
        v.shrink_to_fit();
    }


    // Сначала выполняется поток 1 только потом поток 2, что не позволяет считывать параллельно значение процента выполнения...
    // Метод поиска простых чисел
    void find_prime() {
        double delta_percent = 0.0;
        std::lock_guard<std::recursive_mutex> locker(_lock);
        double prev_percent = 0.0;
        for (size_t i = 0; i < maxValue; ++i) {            
            if (isPrime(i)) { v.push_back(i); }
            double curr_percent = ((i + 1.0) / static_cast<double>(maxValue)) * 100.0;
            delta_percent = curr_percent - prev_percent;
            prev_percent = curr_percent;
            std::cout << "find: " << curr_percent << std::endl;
        }        
    }
    // Метод отображения прогресса
    void progress() {
        double delta_percent = 0.0;
        std::lock_guard<std::recursive_mutex> locker(_lock);
        double sum = 0.0;
        double prev_percent = 0.0;
        while (sum <= 100.0) {
            delta_percent = curr_percent - prev_percent;
            std::cout << "progress: " << curr_percent << std::endl;
            if (delta_percent >= 0.9999999) {
                bar.update(delta_percent);
                bar.print();
                prev_percent = curr_percent;
            }
            bar.update(delta_percent);
            bar.print();
            // Sleep(100);
            sum += delta_percent;
        }        
    }
};


int main()
{
    setlocale(LC_ALL, "Russian");

    int countDigits = 1000000;
    PrimeNumber pn(countDigits);

    Timer timer("Время на поиск простых чисел в одном главном потоке main составило");
    pn.find_prime_progress();
    timer.print();

    std::cout << std::endl << std::endl << std::endl;
    pn.clear_v();

    timer.start("Время на поиск простых чисел в отдельном потоке составило");
    std::thread t1(&PrimeNumber::find_prime_progress, &pn);
    // std::thread t2(&PrimeNumber::progress, &pn);
    t1.join();
    // t2.detach();
    // t2.detach();
    std::cout << std::endl;
    pn.print_result();
    timer.print();

    ////Setup:
    //pBar bar;
    ////Main loop:
    //for (int i = 0; i < 100; i++) { //This can be any loop, but I just made this as an example
    //    //Update pBar:
    //    bar.update(1); //How much new progress was added (only needed when new progress was added)
    //    //Print pBar:
    //    bar.print(); //This should be called more frequently than it is in this demo (you'll have to see what looks best for your program)
    //    Sleep(1);
    //}
    
    return 0;
}