////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Задание 2                                                                                                      //
// Сгенерируйте вектор a, состоящий из 100 вещественный чисел, представляющий собой значения аналогового сигнала. //
// На основе этого массива чисел создайте другой вектор целых чисел b, представляющий цифровой сигнал, в котором  //
// будут откинуты дробные части чисел.                                                                            //
// Выведите получившиеся массивы чисел. Посчитайте ошибку, которой обладает цифровой сигнал по сравнению с        //
// аналоговым по формуле                                                                                          //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>    // pow
#include <numeric>  // accumulate

#include <random>
#include <chrono>

template<typename T, template <typename, typename = std::allocator<T>> class TContainer>
void print_vector(TContainer<T> v) {
    for (T elem : v) {
        std::cout << elem << " ";
    }
}

class Signals {
private:
    std::vector<double> m_vector1;
    std::vector<int> m_vector2;
    std::vector<double> m_vector_errors;

public:
    double random_number(const double from, const double to) {
        static std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        std::uniform_real_distribution<> distribution(from, to);
        return static_cast<double>(distribution(gen));
    }

    Signals(const int n) {
        m_vector1.resize(n);
        m_vector2.resize(n);
        m_vector_errors.resize(n);
        std::generate(m_vector1.begin(), m_vector1.end(), [&]() mutable {return random_number(0, n); });
        std::transform(m_vector1.begin(), m_vector1.end(), m_vector2.begin(), [](double s) { return static_cast<int>(s); });
        std::transform(m_vector1.begin(), m_vector1.end(), m_vector_errors.begin(), [](double s) { return pow(((s - static_cast<int>(s))), 2); });
    }

    std::vector<double> get_vector1() {
        return m_vector1;
    }

    std::vector<int> get_vector2() {        
        return m_vector2;
    }

    std::vector<double> get_vector_err() {
        return m_vector_errors;
    }

    double err() {
        double sum = 0;
        sum = std::accumulate(m_vector_errors.begin(), m_vector_errors.end(), sum);
        return sum;
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");

    Signals s(100);
    std::vector<double> v1 = s.get_vector1();
    std::cout << "Исходный вектор сигналов: " << std::endl;
    print_vector(v1);

    std::cout << std::endl;
    std::cout << std::endl;

    std::vector<int> v2 = s.get_vector2();
    std::cout << "Целочисленный вектор сигналов: " << std::endl;
    print_vector(v2);

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Вектор квадратов ошибок: " << std::endl;
    std::vector<double> e = s.get_vector_err();
    print_vector(e);

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Ошибка, которой обладает цифровой сигнал по сравнению с аналоговым равна " << s.err() << std::endl;
    std::cout << std::endl;

    return 0;
}