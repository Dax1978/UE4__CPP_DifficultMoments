////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Задание 1                                                                                                      //
// Создайте потокобезопасную оболочку для объекта cout. Назовите ее pcout. Необходимо, чтобы несколько потоков    //
// могли обращаться к pcout и информация выводилась в консоль. Продемонстрируйте работу pcout.                    //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <thread>
#include <mutex>

static std::mutex mtx_cout;

class pcout {
private:
    std::lock_guard<std::mutex> lg;
public:
    pcout() : lg(std::lock_guard<std::mutex>(mtx_cout)) { }

    template<typename T>
    pcout& operator<<(const T& data) {
        std::cout << data;
        return *this;
    }

    pcout& operator<<(std::ostream& (*fp)(std::ostream&)) {
        std::cout << fp;
        return *this;
    }
};

void doSomething(int number) {
    pcout() << "start thread " << number << std::endl;
    pcout() << "stop thread " << number << std::endl;
}

int main()
{
    std::thread th1(doSomething, 1);
    std::thread th2(doSomething, 2);
    std::thread th3(doSomething, 3);
    th1.join();
    th2.join();
    th3.join();
}