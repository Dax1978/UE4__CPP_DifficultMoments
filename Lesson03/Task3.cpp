////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Задача 3                                                                                                       //
// Реализовать собственный класс итератора, с помощью которого можно будет проитерироваться по диапазону целых    //
// чисел в цикле for - range - based.                                                                             //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <iomanip>
#include <vector>

class MyVector {
private:
    const size_t vector_size;
    int* arr;

public:
    MyVector(const int size) : vector_size(size) {
        arr = new int[vector_size];
    };

    // заполнить массив случайными значениями
    void fill_random(const int n) {
        for (size_t i = 0; i < vector_size; i++) {
            arr[i] = (rand()) % n;
        }
    };

    // получить размер массива
    size_t size() const {
        return vector_size;
    };

    class Iterator
    {
    private:
        int* current;
    public:
        Iterator(int* pointer) : current(pointer) { };

        int& operator[](size_t i) {
            return *(current + i);
        };

        Iterator& operator ++() {
            ++current;
            return *this;
        };

        bool operator !=(const Iterator& iterator) {
            return current != iterator.current;
        };

        int& operator *() {
            return *current;
        };
    };

    Iterator operator[](size_t i) {
        return Iterator(arr + i * vector_size);
    };

    Iterator begin() {
        return Iterator(arr);
    };

    Iterator end() {
        return Iterator(arr + vector_size);
    };

    // распечатать массив
    void print() {
        /*for (size_t i = 0; i < vector_size; i++) {
            std::cout << " " << std::setw(5) << arr[i];
        }
        std::cout << std::endl;
        */
        
        for (size_t i = 0; i < vector_size;) {
            std::cout << " " << std::setw(5) << *(arr + i++);
        }
    };

    ~MyVector() {
        delete[] arr;
    };

};

int main()
{
    MyVector vec(7);
    vec.fill_random(77);
    std::cout << "Method Print() MyVector:" << std::endl;
    vec.print();

    std::cout << std::endl;
    std::cout << "Iterated MyVector:" << std::endl;
    for (const int& item : vec) {
        std::cout << " " << std::setw(5) << item;
    }

    return 0;

}