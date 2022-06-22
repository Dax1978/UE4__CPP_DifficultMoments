////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Задача 1                                                                                                       //
// Написать функцию, добавляющую в конец списка вещественных чисел элемент, значение которого равно среднему      //
// арифметическому всех его элементов.                                                                            //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <list>

void list_add_avg(std::list<double>& list1) {
    double sum(0);
    for (const double& value : list1) sum += value;
    list1.push_back(sum / list1.size());
}

void list_print(std::list<double>& list1) {
    for (const double& value : list1) std::cout << value << " ";
}

int main()
{
    std::list<double> l{ 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7 };
    list_add_avg(l);
    list_print(l);
}