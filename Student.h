#ifndef ASSIGN33_STUDENT_H
#define ASSIGN33_STUDENT_H
#include <bits/stdc++.h>
using namespace std;

struct Student{
    int id ;
    string name;
    string department;
    double GPA;
    friend std::ostream& operator<<(std::ostream& os, const Student& student) {
        os << "Student ID: " << student.id << "\nName: " << student.name << "\nGPA: " << student.GPA << "\nDep: " << student.department << '\n'<<'\n';
        return os;
    }
};
#endif //ASSIGN33_STUDENT_H
