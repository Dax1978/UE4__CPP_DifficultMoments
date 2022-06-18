////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Задача 3                                                                                                       //
// Подсчитайте количество гласных букв в книге “Война и мир”. Для подсчета используйте 4 способа:                 //
//    - count_if и find                                                                                           //
//    - count_if и цикл for                                                                                       //
//    - цикл for и find                                                                                           //
//    - 2 цикла for                                                                                               //
// Замерьте время каждого способа подсчета и сделайте выводы.                                                     //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include "Time.hpp"
#include <string_view>
#include <vector>

// count_if - это алгоритмическая функция из STL, которая принимает 3 параметра: 
//    итератор на начало, итератор на конец и унарный предикат (функцию, принимающую один параметр и возвращающую тип bool).
// find - это метод класса string, который возвращает позицию символа (строки), переданного в качестве параметра, в исходной строке. 
//    Если символ не найден, то метод возвращает string::npos.

const std::string_view vowels { "aeiouAEIOU" };
std::vector<std::pair<double, std::string>> result;


// count_if и find
void search_vowels_1(const std::string_view& s) {
    Time time("Use count_if and find");
    size_t count = count_if(s.begin(), s.end(), [&](const auto& c) { return vowels.find(c) != std::string::npos; });
    std::cout << count << " vowels. ";
    time.print();
    
    // запишем время и метод для последующего анализа
    result.push_back(std::make_pair(time.get_time(), "count_if and find"));
}

// count_if и цикл for
void search_vowels_2(const std::string_view& s) {
    Time time("Use count_if and for");
    size_t count = count_if(s.begin(), s.end(), [&](const auto& c) {
        for (size_t i = 0; i < vowels.size(); ++i) {
            if (vowels[i] == c)
                return true;
        }
        return false;
    });
    std::cout << count << " vowels. ";
    time.print();

    // запишем время и метод для последующего анализа
    result.push_back(std::make_pair(time.get_time(), "count_if and for"));
}

// цикл for и find
void search_vowels_3(const std::string_view& s) {
    size_t count = 0;
    Time time("Use for anf find");
    for (size_t i = 0; i < s.size(); ++i) {
        if (vowels.find(s[i]) != std::string::npos)
            ++count;
    }
    std::cout << count << " vowels. ";
    time.print();

    // запишем время и метод для последующего анализа
    result.push_back(std::make_pair(time.get_time(), "for and find"));
}

// 2 цикла for
void search_vowels_4(const std::string_view& s) {
    size_t count = 0;
    Time time("Use two for");
    for (size_t i = 0; i < s.size(); ++i) {
        for (size_t j = 0; j < vowels.size(); ++j) {
            if (vowels[j] == s[i])
                ++count;
        }
    }
    std::cout << count << " vowels. ";
    time.print();

    // запишем время и метод для последующего анализа
    result.push_back(std::make_pair(time.get_time(), "for and for"));
}

void win_metod() {
    std::pair <double, std::string> winner = {1000000000.0, "nothing"};
    std::cout << "-------Win method is:-------" << std::endl;
    for (std::pair item : result) {
        if (item.first < winner.first) {
            winner.first = item.first;
            winner.second = item.second;
        }
    }
    std::cout << winner.first << " - " << winner.second << std::endl;
}

int main() {
    // std::ifstream file("War_and_peace_min.txt");
    std::ifstream file("War_and_peace.txt");
    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0);
    std::string s(size, ' ');
    file.read(&s[0], size);

    search_vowels_1(s);
    search_vowels_2(s);
    search_vowels_3(s);
    search_vowels_4(s);

    win_metod();

    return 0;
}