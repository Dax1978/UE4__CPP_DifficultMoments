////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Задание 1                                                                                                      //
// Создать шаблонную функцию, которая принимает итераторы на начало и конец последовательности слов, и выводящую  //
// в консоль список уникальных слов (если слово повторяется больше 1 раза, то вывести его надо один раз).         //
// Продемонстрировать работу функции, передав итераторы различных типов.                                          //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iterator>
#include <string>
#include <unordered_set>
#include <vector>
#include <list>
#include <deque>

template<typename IT>
void printWords(IT it, IT end)
{
    std::unordered_set<std::string> countWords(it, end);
    std::copy(countWords.begin(), countWords.end(), std::ostream_iterator<std::string>(std::cout, "; "));
}

int main()
{
    setlocale(LC_ALL, "Russian");

    std::vector<std::string> v{ "Семь", "Три", "Два", "Пять", "Один", "Пять", "Шесть", "Два", "Два", "Один", "Семь", "Девять" };
    std::cout << "Вывод вектора:" << std::endl;
    printWords(v.begin(), v.end());

    std::deque<std::string> d(v.begin(), v.end());
    std::cout << "\nВывод деки:" << std::endl;
    printWords(d.begin(), d.end());

    std::list<std::string> l(v.begin(), v.end());
    std::cout << "\nВывод листа:" << std::endl;
    printWords(l.begin(), l.end());

    return 0;
}