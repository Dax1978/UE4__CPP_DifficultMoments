////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Задание 3                                                                                                      //
// Промоделировать следующую ситуацию. Есть два человека (2 потока): хозяин и вор.                                //
// Хозяин приносит домой вещи (функция добавляющая случайное число в вектор с периодичностью 1 раз в секунду).    //
// При этом у каждой вещи есть своя ценность.                                                                     //
// Вор забирает вещи (функция, которая находит наибольшее число и удаляет из вектора с периодичностью 1 раз в 0.5 //
// секунд), каждый раз забирает вещь с наибольшей ценностью.                                                      //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>
#include <random>

std::mutex m;

std::vector<int> thing_add(std::vector<int>& v) {
    std::lock_guard lg(m);

    std::random_device random_device;
    std::mt19937 generator(random_device());
    /*
    int in1;
    std::cout << "in1 = ";
    std::cin >> in1;
    int in2;
    std::cout << "in2 = ";
    std::cin >> in2;
    std::uniform_int_distribution<> distribution(in1, in2);
    */
    std::uniform_int_distribution<> distribution(0, 1000);    
    int x = distribution(generator);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "Хозяин добавил вещь ценой = " << x << std::endl;
    v.push_back(x);
    return v;
}

std::vector<int> thing_pop(std::vector<int>& v) {
    std::lock_guard lg(m);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    if (v.size() > 0) {
        std::vector<int>::iterator iter = std::max_element(v.begin(), v.end());
        std::cout << "Вор стащил вещь ценой = " << *iter << std::endl;
        v.erase(iter);
    }
    else {
        std::cout << "Больше нечего украсть. Все уже украдено." << std::endl;
    }
    return v;
}

void things_view(std::vector<int>& v) {    
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}



int main() {
    setlocale(LC_ALL, "Russian");

    std::vector<int> v;
    size_t count = 10;

    while (count--) {
        std::thread owner([&]() { v = thing_add(v); });
        std::thread thief([&]() { v = thing_pop(v); });     
        owner.join();
        thief.join();

        things_view(v);


    }
}