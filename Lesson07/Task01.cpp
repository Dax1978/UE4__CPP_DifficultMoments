////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Задание 1                                                                                                      //
// Установить библиотеку protobuf.                                                                                //
// Задание 2                                                                                                      //
// С помощью компилятора protobuf в отдельном пространстве имен сгенерировать классы:                             //
//      a. FullName с полями имя, фамилия, отчество (отчество опционально).                                       //
//      b. Student с полями полное имя, массив оценок, средний балл.                                              //
//      c. StudentsGroup с полем массив студентов.                                                                //
// Задание 3                                                                                                      //
// Создать класс StudentsGroup, который реализует интерфейсы:                                                     //
//    class IRepository {                                                                                         //
//       virtual void Open() = 0; // бинарная десериализация в файл                                               //
//       virtual void Save() = 0; // бинарная сериализация в файл                                                 //
//    };                                                                                                          //
//    class IMethods {                                                                                            //
//       virtual double GetAverageScore(const FullName& name) = 0;                                                //
//       virtual string GetAllInfo(const FullName& name) = 0;                                                     //
//       virtual string GetAllInfo() = 0;                                                                         //
//    };                                                                                                          //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "Task02.hpp"
#include "Task_03.hpp"

int main()
{
    setlocale(LC_ALL, "Russian");

    std::cout << "Задание 2" << std::endl;
    task02();
    std::cout << std::endl << std::endl << "Задание 3" << std::endl;
    task03();
}