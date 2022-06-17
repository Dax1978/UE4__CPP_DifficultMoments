////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Практическое задание 1                                                                                         //
//                                                                                                                //
// Имеется база сотрудников и номеров их телефонов. Требуется написать соответствующие структуры для хранения     //
// данных, и заполнить контейнер записями из базы. Затем необходимо реализовать методы обработки данных, а также  //
// вывести на экран всю необходимую информацию.                                                                   //
// Важно! Имена переменным, классам и функциям давайте осознанные, состоящие из слов на английском языке.         //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <optional>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <optional>
#include <vector>
#include <algorithm>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Task 1                                                                                                         //
// Создайте структуру Person с 3 полями: фамилия, имя, отчество. Поле отчество должно быть опционального типа,    //
// т.к.не у всех людей есть отчество. Перегрузите оператор вывода данных для этой структуры.                      //
// Также перегрузите операторы < и == (используйте tie).                                                          //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Person {
    std::string firstname;
    std::string lastname;
    std::optional<std::string> patronymic;
};

std::ostream& operator<<(std::ostream& out, const Person& p) {
    out << std::setw(17) << p.firstname << std::setw(17) << p.lastname;

    if (p.patronymic.has_value()) { out << std::setw(17) << p.patronymic.value(); }
    else { out << std::setw(17); }

    return out;
}

bool operator<(const Person& p1, const Person& p2) {
    return tie(p1.firstname, p1.lastname, p1.patronymic) < tie(p2.firstname, p2.lastname, p2.patronymic);
}

bool operator==(const Person& p1, const Person& p2) {
    return tie(p1.firstname, p1.lastname, p1.patronymic) == tie(p2.firstname, p2.lastname, p2.patronymic);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Task 2                                                                                                         //
// Создайте структуру PhoneNumber с 4 полями:                                                                     //
//    · код страны (целое число)                                                                                  //
//    · код города (целое число)                                                                                  //
//    · номер (строка)                                                                                            //
//    · добавочный номер (целое число, опциональный тип)                                                          //
// Для этой структуры перегрузите оператор вывода. Необходимо, чтобы номер телефона выводился в формате :         //
//    +7(911)1234567 12, где 7 – это номер страны, 911 – номер города, 1234567 – номер, 12 – добавочный номер.    //
// Если добавочного номера нет, то его выводить не надо. Также перегрузите операторы < и == (используйте tie)     //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct PhoneNumber {
    int country_code;
    int city_code;
    std::string number;
    std::optional<int> additional_number;
};

std::ostream& operator<<(std::ostream& out, const PhoneNumber& p)
{
    out << std::setw(3) << '+' << p.country_code << '(' << p.city_code << ')' << p.number;

    if (p.additional_number.has_value()) { out << ' ' << p.additional_number.value(); }

    return out;
}

bool operator<(const PhoneNumber& p1, const PhoneNumber& p2) {
    return tie(p1.country_code, p1.city_code, p1.number, p1.additional_number) < tie(p2.country_code, p2.city_code, p2.number, p2.additional_number);
}

bool operator==(const PhoneNumber& p1, const PhoneNumber& p2) {
    return tie(p1.country_code, p1.city_code, p1.number, p1.additional_number) == tie(p2.country_code, p2.city_code, p2.number, p2.additional_number);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Task 3                                                                                                         //
// Создайте класс PhoneBook, который будет в контейнере хранить пары: Человек – Номер телефона.                   //
// Конструктор этого класса должен принимать параметр типа ifstream – поток данных, полученных из файла.          //
// В теле конструктора происходит считывание данных из файла и заполнение контейнера.                             //
// Класс PhoneBook должен содержать перегруженный оператор вывода, для вывода всех данных из контейнера в консоль.//
//                                                                                                                //
// В классе PhoneBook реализуйте метод SortByName, который должен сортировать элементы контейнера по фамилии людей//
// в алфавитном порядке. Если фамилии будут одинаковыми, то сортировка должна выполняться по именам, если имена   //
// будут одинаковы, то сортировка производится по отчествам. Используйте алгоритмическую функцию sort.            //
//                                                                                                                //
// Реализуйте метод SortByPhone, который должен сортировать элементы контейнера по номерам телефонов. Используйте //
// алгоритмическую функцию sort.                                                                                  //
//                                                                                                                //
// Реализуйте метод GetPhoneNumber, который принимает фамилию человека, а возвращает кортеж из строки и           //
// PhoneNumber. Строка должна быть пустой, если найден ровно один человек с заданном фамилией в списке. Если не   //
// найден ни один человек с заданной фамилией, то в строке должна быть запись «not found», если было найдено      //
// больше одного человека, то в строке должно быть «found more than 1».                                           //
//                                                                                                                //
// Реализуйте метод ChangePhoneNumber, который принимает человека и новый номер телефона и, если находит заданного//
// человека в контейнере, то меняет его номер телефона на новый, иначе ничего не делает.                          //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class PhoneBook {
private:
    std::vector<std::pair<Person, PhoneNumber>> m_data;

public:
    PhoneBook(std::ifstream& file) {
        if (!file) {
            std::cout << "Error! File is not open..." << std::endl;
            exit(-1);
        }

        // getline(stream, string, separator);
        // где stream - это поток данных,
        // string – переменная, в которую запишется строка,
        // separator – строковый разделитель, показывающий на конец строки.
        // Последний параметр функции можно опустить, тогда будет задан сепаратор по умолчанию - '\n'.

        std::pair<Person, PhoneNumber> result;
        std::string str, item;        

        while (getline(file, str)) {
            std::stringstream ss(str);
            std::vector<int> numbers;

            int n_item = 0;
            int n_numbers = 0;
            while (getline(ss, item, ' ')) {
                if (item.size() > 0) {
                    switch (n_item) {
                    case 0:
                        result.first.firstname = item;
                        break;
                    case 1:
                        result.first.lastname = item;
                        break;
                    case 2:
                        if (not isInt(item)) {
                            result.first.patronymic = item;
                        }
                        else {
                            result.second.country_code = stoi(item);
                            n_numbers++;
                        }
                        break;
                    case 3:
                        if (n_numbers == 0) {
                            result.second.country_code = stoi(item);
                            n_numbers++;
                        }
                        else {
                            result.second.city_code = stoi(item);
                            n_numbers++;
                        }
                        break;
                    case 4:
                        if (n_numbers == 1) {
                            result.second.city_code = stoi(item);
                            n_numbers++;
                        }
                        else {
                            result.second.number = item;
                            n_numbers++;
                        }
                        break;
                    case 5:
                        if (n_numbers == 2) {
                            result.second.number = item;
                            n_numbers++;
                        }
                        else {
                            result.second.additional_number = stoi(item);
                            n_numbers++;
                        }
                        break;
                    case 6:
                        result.second.additional_number = stoi(item);
                        break;
                    }                    
                    n_item++;
                }
            }
            n_numbers = 0;
            n_item = 0;

            m_data.push_back(result);
        }
    }

    friend std::ostream& operator<<(std::ostream& out, const PhoneBook& pb) {
        for (const auto& [first, second] : pb.m_data) {
            out << first << ' ' << second << std::endl;
        }

        return out;
    }

    void SortByName() {
        sort(m_data.begin(), m_data.end(), [](const std::pair<Person, PhoneNumber>& fst, const std::pair<Person, PhoneNumber>& scn) {
                return fst.first < scn.first;
            });
    }

    void SortByPhone() {
        sort(m_data.begin(), m_data.end(), [](const std::pair<Person, PhoneNumber>& fst, const std::pair<Person, PhoneNumber>& scn) {
                return fst.second < scn.second;
            });
    }

    std::pair<std::string, PhoneNumber> GetPhoneNumber(const std::string& firstname) {
        PhoneNumber phone_number;
        int count = 0;

        for_each(m_data.begin(), m_data.end(), [&](const auto& result) {
                if (result.first.firstname == firstname) {
                    phone_number = result.second;
                    ++count;
                }
            });

        

        switch (count) {
        case 0:
            return { "not found", phone_number };
            break;
        case 1:
            return { "", phone_number };
            break;
        default:
            return { "found more than 1", phone_number };
            break;
        }
    }

    void ChangePhoneNumber(const Person& p, const PhoneNumber& pn) {
        auto result = find_if(m_data.begin(), m_data.end(), [&](const auto& result) {
                return result.first == p;
            });

        if (result != m_data.end()) { result->second = pn; }
    }

    bool isNumeric(std::string str)
    {
        std::stringstream stream;
        double number;

        stream << str;
        stream >> number;

        return stream.eof();
    }

    bool isInt(std::string str)
    {
        std::stringstream stream;
        int number;

        stream << str;
        stream >> number;

        return stream.eof();
    }
};


int main()
{
    std::ifstream file("PhoneBook.txt"); // путь к файлу PhoneBook.txt
    PhoneBook book(file);
    std::cout << book;

    std::cout << "------SortByPhone-------" << std::endl;
    book.SortByPhone();
    std::cout << book;

    std::cout << "------SortByName--------" << std::endl;
    book.SortByName();
    std::cout << book;

    std::cout << "-----GetPhoneNumber-----" << std::endl;
    // лямбда функция, которая принимает фамилию и выводит номер телефона этого человека, либо строку с ошибкой
    auto print_phone_number = [&book](const std::string& surname) {
        std::cout << surname << "\t";
        auto answer = book.GetPhoneNumber(surname);
        if (get<0>(answer).empty())
            std::cout << get<1>(answer);
        else
            std::cout << get<0>(answer);

        std::cout << std::endl;
    };

    // вызовы лямбды
    print_phone_number("Ivanov");
    print_phone_number("Petrov");

    std::cout << "----ChangePhoneNumber----" << std::endl;
    book.ChangePhoneNumber(Person{ "Kotov", "Vasilii", "Eliseevich" }, PhoneNumber{ 7, 123, "15344458", std::nullopt });
    book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" }, PhoneNumber{ 16, 465, "9155448", 13 });
    std::cout << book;


}