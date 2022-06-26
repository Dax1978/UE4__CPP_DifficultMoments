////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Задание 2                                                                                                      //
// Используя ассоциативный контейнер, напишите программу, которая будет считывать данные введенные пользователем  //
// из стандартного потока ввода и разбивать их на предложения.                                                    //
// Далее программа должна вывести пользователю все предложения, а также количество слов в них, отсортировав       //
// предложения по количеству слов.                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iterator>
#include <string>
#include <unordered_set>
#include <queue>

// https://proginfo.ru/getline/

std::string text_to_sentence(std::string& s) {
    // Переменная для найденного предложения
    std::string res;
    // Знаки конца предложения
    std::string sentence_end_marks{ ".?!;" };

    // Читаем посимвольно поток данных
    for (const char& c : s) {
        // Записываем каждый символ в переменную для предложения
        res.push_back(c);
        // Если нашли знак конца строки, заканчиваем поиск
        if (sentence_end_marks.find(c) != std::string::npos) {
            // Очистим поток
            s.erase(0, res.size());
            // Тримим пробел в начале предложения, если он есть там
            if (res[0] == ' ') { res.erase(0, 1); }
            // Вернем найденное предложение
            return res;
        }
    }
    // В противном случае ничего
    return {};
}

int main() {
    std::unordered_set<std::string, std::hash<std::string>> sentences;
    std::string string_current, string_temp;

    while (std::getline(std::cin, string_current)) {
        // Пустые строки пропускаем
        if (!string_current.empty()) {
            // Cуммируем в новом потоке все введённые предложения, если предыдущее не закончено
            string_temp += string_current + ' ';
            // добавляем разделитель, если предложение было перенесено на новую строку                                                     
            while (true) {
                // Ищем предложение из сформированного потока данных
                std::string sentence(std::move(text_to_sentence(string_temp)));
                // Прекращаем поиск, если нет ни одного найденного предложения
                if (sentence.empty()) { break; }
                // Иначе сохраняем найденное предложение и продолжаем поиск другого
                sentences.insert(std::move(sentence));
            }
        }
    }

    // Работаем с набором наших строк
    std::priority_queue<std::pair<size_t, std::string>> pq;
    for (const auto& sentence : sentences) {
        pq.push({ sentence.size(), sentence });
    }
    while (!pq.empty()) {
        std::cout << pq.top().first << ": " << pq.top().second << '\n';
        pq.pop();
    }

    return 0;
}