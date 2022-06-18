////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Задача 2                                                                                                       //
// Реализуйте шаблонную функцию SortPointers, которая принимает вектор указателей и сортирует указатели по        //
// значениям, на которые они указывают.                                                                           //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
void SortPointers(std::vector<T*> &v_pnt) {
    /*
    for (const auto elem : v_pnt) {
        std::cout << *elem << " / ";
    }
    std::cout << std::endl;
    */
    std::sort(v_pnt.begin(), v_pnt.end(), [](const auto value_1, const auto value_2) { return *value_1 < *value_2; });    
};

int main() {
    int length = 7;
    std::vector<int*> v_int;

    // Генерация и вывод сгенерированного вектора
    for (int i = 0; i < length; ++i)
    {
        int* value = new int;
        *value = rand() % 100;
        v_int.push_back(value);

        std::cout << *v_int[i] << " ";
    }
    std::cout << std::endl;

    // Сортировка
    SortPointers(v_int);

    // Вывод отсортированного вектора
    for (int i = 0; i < length; ++i) { std::cout << *v_int[i] << ' '; }
    std::cout << std::endl;

    return 0;
}