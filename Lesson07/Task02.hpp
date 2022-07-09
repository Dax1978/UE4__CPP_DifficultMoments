#pragma once

#include <string>
#include <iostream>
#include <numeric>
#include <fstream>
#include "task_02.pb.h"

void task02() {
    // std::string patr = "Alexandrovich";

	FullName fn;
	fn.set_name("John");
	fn.set_surname("Gorbunov");
	// fn.set_allocated_patronymic(&patr);

	Student s;
    *s.mutable_name() = fn;
    s.add_grades(5);
    s.add_grades(5);
    s.add_grades(3);
    s.add_grades(4);
    s.add_grades(4);
    s.add_grades(5);
    s.add_grades(4);
    s.set_avg_score(std::accumulate(s.grades().begin(), s.grades().end(), 0) / s.grades().size());

    StudentsGroup sg;
    *sg.add_students() = s;

    std::ofstream out("student.bin", std::ios_base::binary);
    sg.SerializeToOstream(&out);
    out.close();

    StudentsGroup sg_new;
    std::ifstream in("student.bin", std::ios_base::binary);
    if (sg_new.ParseFromIstream(&in)) {
        std::cout << sg_new.students(0).name().surname() << std::endl;
        std::cout << sg_new.students(0).avg_score() << std::endl;
    } else {
        std::cout << "Error!" << std::endl;
    }
    in.close();
}