#include "Task_03.hpp"
#include <numeric>

void task03() {
    FullName fn;
    fn.set_name("John");
    fn.set_surname("Gorbunov");
    // fn.set_patronymic("Alexandrovich");

    Student s;
    *s.mutable_name() = fn;
    s.add_grades(5);
    s.add_grades(2);
    s.add_grades(4);
    s.add_grades(3);
    s.add_grades(4);
    s.add_grades(3);
    s.add_grades(4);
    s.add_grades(3);
    s.set_avg_score(std::accumulate(s.grades().begin(), s.grades().end(), 0) / s.grades().size());

    SG::StudentsGroup sg;
    sg.add_student(s);
    sg.Save();

    SG::StudentsGroup new_sg;
    new_sg.Open();
    std::cout << new_sg.GetAllInfo(fn) << std::endl;
}