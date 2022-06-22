////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Задача 2                                                                                                       //
// Создать класс, представляющий матрицу. Реализовать в нем метод, вычисляющий определитель матрицы.              //
// Для реализации используйте контейнеры из STL.                                                                  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include <vector>

// По условию задания должен вычисляться определитель (детерминант) матрицы, соответственно матрица должна быть квадратной.
// Что приводит к тому, что размер матрицы будет определяться 1 целым числом

// https://ru.onlinemschool.com/math/assistance/matrix/determinant/

template <class T>class Matrix {
private:
    const size_t m_size;
    const size_t m_capacity;
    std::vector<std::vector <T>> arr;
    double det { 0.0 };

public:
    Matrix(const size_t size) : m_size(size), m_capacity(size * size) {
        // vector<T> vector2(n, value); // последовательность из n копий значений value
        std::vector<T> arr_row(m_size, 0.0);
        for (size_t i = 0; i < m_size; i++) { arr.push_back(arr_row); }
    }

    void show() {
        for (std::vector<T> r : arr) {
            for (auto& c : r)
                std::cout << " " << std::setw(5) << c;
            std::cout << std::endl;
        }
    }

    void show(size_t n) {
        for (std::vector<T> r : arr) {
            for (auto& c : r)
                std::cout << " " << std::setw(n) << c;
            std::cout << std::endl;
        }
    }

    size_t size() {
        return m_size;
    }

    T at(const size_t& row, const size_t& col) const {
        return arr.at(row).at(col);
    }

    T& at(const size_t& row, const size_t& col) {
        return arr.at(row).at(col);
    }

    void fill_rand(const int n) {
        srand(time(NULL));
        /*for (std::vector<T> r : arr) {
            for (auto& c : r) {
                c = (double)(rand()) / RAND_MAX * n;
                std::cout << c << " ";
            }
            std::cout << std::endl;
        }*/

        for (size_t i = 0; i < m_size; i++) {
            for (size_t j = 0; j < m_size; j++) {
                arr[i][j] = (double)(rand()) / RAND_MAX * n;
            }
        }

        det = calc_determinant(arr);
    }

    std::vector<std::vector <T>> decomposition_matrix(std::vector<std::vector <T>> m, const size_t r) {        
        std::vector<std::vector <T>> new_arr;
        std::vector<T> new_vec;       

        for (size_t i = 0; i < m.size(); i++) {
            for (size_t j = 0; j < m.size() - 1; j++) {                
                if (i != r) { new_vec.push_back(m[i][j + 1]); }         
            }

            if (i != r) {
                new_arr.push_back(new_vec);
                new_vec.clear();
            }            
        }

        return new_arr;
    }

    double calc_determinant(std::vector<std::vector <T>> m) {
        double d = 0.0;

        /*std::cout << "-------------------------------------" << std::endl;
        for (std::vector<T> r : m) {
            for (auto& c : r)
                std::cout << " " << std::setw(5) << c;
            std::cout << std::endl;
        }
        std::cout << "-------------------------------------" << std::endl;*/

        if (m.size() == 1) {
            d = m[0][0];
        }
        else if (m.size() == 2) {
            d = m[0][0] * m[1][1] - m[1][0] * m[0][1];
        }
        else {
            int sign = 1;            

            for (size_t i = 0; i < m.size(); ++i) {
                std::vector<std::vector <T>> new_arr = decomposition_matrix(m, i);
                d += sign * m[i][0] * calc_determinant(new_arr);
                sign = -sign;
            }
        }

        return d;
    }

    double get_determinant() {
        return det;
    }
};

int main()
{ 
    Matrix<double> m(4);
    m.show();
    std::cout << std::endl;
    m.fill_rand(100);
    std::cout << std::endl;
    m.show();
    std::cout << std::endl;
    std::cout << "Determinant = " << m.get_determinant() << std::endl;

    return 0;
}