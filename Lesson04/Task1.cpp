////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Задание 1                                                                                                      //
// Имеется отсортированный массив целых чисел. Необходимо разработать функцию insert_sorted, которая принимает    //
// вектор и новое число и вставляет новое число в определенную позицию в векторе, чтобы упорядоченность           //
// контейнера сохранялась.                                                                                        //
// Реализуйте шаблонную функцию insert_sorted, которая сможет аналогично работать с любым контейнером,            //
// содержащим любой тип значения.                                                                                 //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// https://ru.stackoverflow.com/questions/1102906/%D0%A8%D0%B0%D0%B1%D0%BB%D0%BE%D0%BD%D0%BD%D1%8B%D0%B9-%D0%BC%D0%B5%D1%82%D0%BE%D0%B4-%D0%B4%D0%BB%D1%8F-%D0%BA%D0%BE%D0%BD%D1%82%D0%B5%D0%B9%D0%BD%D0%B5%D1%80%D0%BE%D0%B2-%D1%81
// https://stackoverflow.com/questions/16596422/template-class-with-template-container

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <list>

#include <random>
#include <chrono>

class Task1_1 {
private:
    std::vector<int> m_v;

public:
    Task1_1(const int n) {
        m_v.resize(n);
        int i = 1;
        // std::generate(v.begin(), v.end(), []() {return (rand() % 100); });
        std::generate(m_v.begin(), m_v.end(), [i]() mutable {return i++; });        
    }

    std::vector<int> get_v() {
        return m_v;
    }

    void print(std::vector<int> v) {
        for (int elem : v) {
            std::cout << elem << " ";
        }
        // copy(v.begin(), v.end(), std::ostream_iterator<int>{std::cout, ", "});
    }

    std::vector<int> insert_sorted(std::vector<int> v, const int &num) {
        std::vector<int>::iterator it = std::find_if(v.begin(), v.end(), [&](int &cur) { return cur >= num; });
        /*if (it == v.end()) {
            std::cout << "Not found\n";
        }
        else {
            int val = *it;
            std::cout << "Found " << val << std::endl;
        }*/
        v.insert(it, num);

        return v;
    }

};

// template<template<typename, typename> class TContainer, typename TItem, typename TIterator, typename T>
template<typename T, template <typename, typename = std::allocator<T>> class TContainer>
class Task1_2 {
private:
    TContainer<T> m_v;

public:
    typedef typename TContainer<T>::iterator TIterator;

    T random_number(const T from, const T to) {
        static std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        std::uniform_real_distribution<> distribution(from, to);
        return static_cast<T>(distribution(gen));
    }

    Task1_2(const int n) {
        for (size_t i = 0; i < n; i++) { m_v.push_back(static_cast<T>(random_number(i * 10, (i + 1) * 10))); };
    }

    TContainer<T> get_v() {
        return m_v;
    }

    void print(TContainer<T> v) {
        for (T elem : v) {
            std::cout << elem << " ";
        }
    }

    TContainer<T> insert_sorted(TContainer<T> v, const T& num) {
        TIterator it = std::find_if(v.begin(), v.end(), [&](T& cur) { return cur >= num; });
        v.insert(it, num);
        return v;
    }
};



int main()
{
    Task1_1 task1_1 = Task1_1(13);
    std::vector<int> v = task1_1.get_v();
    task1_1.print(v);
    std::cout << std::endl;
    v = task1_1.insert_sorted(v, 7);
    task1_1.print(v);

    std::cout << std::endl;
    std::cout << std::endl;

    Task1_2<double, std::list> task1_2(13);
    std::list<double> v2 = task1_2.get_v();
    task1_2.print(v2);
    std::cout << std::endl;
    v2 = task1_2.insert_sorted(v2, 77.77);
    task1_2.print(v2);

    std::cout << std::endl;

    Task1_2<double, std::vector> task1_3(13);
    std::vector<double> v3 = task1_3.get_v();
    task1_3.print(v3);
    std::cout << std::endl;
    v3 = task1_3.insert_sorted(v3, 77.77);
    task1_3.print(v3);

    return 0;
}