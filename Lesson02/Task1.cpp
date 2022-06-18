////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Задача 1                                                                                                       //
// Реализуйте шаблонную функцию Swap, которая принимает два указателя и обменивает местами значения, на которые   //
// указывают эти указатели (нужно обменивать именно сами указатели, переменные должны оставаться в тех же адресах //
// памяти).                                                                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// https://metanit.com/cpp/tutorial/4.2.php
// https://ru.stackoverflow.com/questions/1356933/%D0%9A%D0%B0%D0%BA-%D1%81%D0%BE%D1%81%D1%82%D0%B0%D0%B2%D0%B8%D1%82%D1%8C-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D1%8E-%D0%BA%D0%BE%D1%82%D0%BE%D1%80%D0%B0%D1%8F-%D0%BC%D0%B5%D0%BD%D1%8F%D0%B5%D1%82-%D1%83%D0%BA%D0%B0%D0%B7%D0%B0%D1%82%D0%B5%D0%BB%D0%B8-%D0%BC%D0%B5%D1%81%D1%82%D0%B0%D0%BC%D0%B8

#include <iostream>

template<typename T>
//void Swap(T* pnt1, T* pnt2)
//{
//    T temp = *pnt1;
//    *pnt1 = *pnt2;
//    *pnt2 = temp;
//}

void Swap(T **pnt1, T **pnt2)
{
    T* temp = *pnt1;
    *pnt1 = *pnt2;
    *pnt2 = temp;
}

int main()
{
    int a(0);
    int b(7);

    int* pa = &a;
    std::cout << "address of pointer pa = " << &pa << std::endl;        // адрес указателя
    std::cout << "address stored in pointer pa = " << pa << std::endl;  // адрес, который хранится в указателе - адрес переменной a         
    std::cout << "value on pointer pa = " << *pa << std::endl;          // значение по адресу в указателе - значение переменной a

    std::cout << std::endl;

    int* pb = &b;
    std::cout << "address of pointer pb = " << &pb << std::endl;        // адрес указателя
    std::cout << "address stored in pointer pb = " << pb << std::endl;  // адрес, который хранится в указателе - адрес переменной b         
    std::cout << "value on pointer pb = " << *pb << std::endl;          // значение по адресу в указателе - значение переменной b

    Swap(&pa, &pb);

    std::cout << std::endl << "<-----------------------------------------SWAP------------------------------------------>" << std::endl;

    std::cout << "address of pointer pa = " << &pa << std::endl;        // адрес указателя
    std::cout << "address stored in pointer pa = " << pa << std::endl;  // адрес, который хранится в указателе - адрес переменной a         
    std::cout << "value on pointer pa = " << *pa << std::endl;          // значение по адресу в указателе - значение переменной a

    std::cout << std::endl;

    std::cout << "address of pointer pb = " << &pb << std::endl;        // адрес указателя
    std::cout << "address stored in pointer pb = " << pb << std::endl;  // адрес, который хранится в указателе - адрес переменной b         
    std::cout << "value on pointer pb = " << *pb << std::endl;          // значение по адресу в указателе - значение переменной b
}