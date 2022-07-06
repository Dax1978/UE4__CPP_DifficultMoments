////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Задание 2                                                                                                      //
// Реализовать функцию, возвращающую i-ое простое число (например, миллионное простое число равно 15485863).      //
// Вычисления реализовать во вторичном потоке. В консоли отображать прогресс вычисления (в основном потоке).      //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// https://ru.stackoverflow.com/questions/232452/%D0%A4%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D1%8F-%D0%BF%D1%80%D0%BE%D0%B2%D0%B5%D1%80%D1%8F%D1%8E%D1%89%D0%B0%D1%8F-%D0%BF%D1%80%D0%BE%D1%81%D1%82%D0%BE%D0%B5-%D0%BB%D0%B8-%D1%87%D0%B8%D1%81%D0%BB%D0%BE
// 

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include "Timer.hpp"

int maxValue = 10000;

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

std::vector<int> prime_without_threads(std::vector<int>& v) {
    for (int i = 0; i < maxValue; ++i) {
        if (isPrime(i)) {
            v.push_back(i);
        }
    }
    return v;
}

std::vector<int> prime_with_threads(std::vector<int>& v) {
    std::mutex m;
    unsigned nthreads = std::thread::hardware_concurrency();    

    for (int i = 0; i < maxValue;) {
        std::vector<std::thread> threads;

        for (unsigned j = i + nthreads; i <= j; ++i) {
            threads.push_back(std::thread([=, &m, &v]() {
                if (isPrime(i)) {
                    std::lock_guard lg(m);
                    v.push_back(i);
                }
                }));
        }

        for (auto& t : threads)
            t.join();
    }

    return v;
}

int main() {
    setlocale(LC_ALL, "Russian");

    std::vector<int> v;

    Timer timer("Without threads");
    v = prime_without_threads(v);
    // std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "В диапазоне до " << maxValue << " количество простых чисел " << v.size() << std::endl;
    std::vector<int>::iterator iter = v.end() - 1;
    std::cout << "Последнее найденное простое число без использования потоков: " << *iter << std::endl;
    timer.print();

    v.clear();
    v.shrink_to_fit();

    timer.start("With threads");
    v = prime_with_threads(v);
    std::cout << "В диапазоне до " << maxValue << " количество простых чисел " << v.size() << std::endl;
    iter = v.end() - 1;
    std::cout << "Последнее найденное простое число с использованием потоков: " << *iter << std::endl;
    timer.print();
}