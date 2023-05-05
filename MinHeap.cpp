#include <iostream>
#include <queue>
using namespace std;


struct Student{
    string Name;
    int id;
    double GPA;
    string Dep;
    Student(){
        Name = "";id = -1;GPA = -1;Dep = "";
    }
    friend std::ostream& operator<<(std::ostream& os, const Student& student) {
        os << "ID: " << student.id << "\nName: " << student.Name << "\nGPA: " << student.GPA << "\nDep: " << student.Dep << '\n';
        return os;
    }
};
class MinHeap {
public:
    int length = 0;
    void MinHeapify(Student* array, int i){
        int left = 2*i + 1;
        int right = 2*i + 2;
        int min = i;
        if(left < length && array[min].GPA > array[left].GPA){
            min = left;
        }
        else if(right < length && array[min].GPA > array[right].GPA){
            min = right;
        }
        if(min != i){
            swap(array[min], array[i]);
            MinHeapify(array, min);
        }
    }
    void insert(Student* array, Student NewS){
        array[length] = NewS;
        length++;
        for (int i = length/2 - 1; i >= 0; --i) {
            MinHeapify(array, i);
        }
    }
    Student* remove(Student* array, Student S) {
        bool found = false;
        int i = 0;
        for (i = 0; i < length; ++i) {
            if (array[i].id == S.id) {
                found = true;
                break;
            }
        }
        if (found) {
            array[i] = array[length - 1];
            length--;
            MinHeapify(array, i);
            for (int j = length/2 - 1; j >= 0; j--)
            {
                MinHeapify(array, j);
            }
        }
        else {
            cout << "Student Not Found";
        }
        return array;
    }

};


int main(){
    MinHeap myMinH;
    Student* students = new Student[10];
    Student s1;
    s1.Name = "Noha";
    s1.Dep = "IS";
    s1.GPA = 0.2;
    s1.id = 20210001;
    Student s2;
    s2.Name = "Naemat";
    s2.Dep = "IS";
    s2.GPA = 0.1;
    s2.id = 20210002;
    Student s3;
    s3.Name = "Ramly";
    s3.Dep = "DS";
    s3.GPA = 1.69;
    s3.id = 20210003;
    Student s4;
    s4.Name = "Khaled";
    s4.Dep = "AI";
    s4.GPA = 3.12;
    s4.id = 20210004;
    Student s5;
    s5.Name = "Mohammed";
    s5.Dep = "DS";
    s5.GPA = 1.23;
    s5.id = 20210005;
    Student s6;
    s6.Name = "Osama";
    s6.Dep = "CS";
    s6.GPA = 3.69;
    s6.id = 20210006;
    Student s7;
    s7.Name = "Ahmed";
    s7.Dep = "AI";
    s7.GPA = 1.65;
    s7.id = 20210007;
    myMinH.insert(students, s1);
    myMinH.insert(students, s2);
    myMinH.insert(students, s3);
    myMinH.insert(students, s4);
    myMinH.insert(students, s5);
    myMinH.insert(students, s6);
    myMinH.insert(students, s7);
    for (int i = 0; i < myMinH.length; ++i) {
        cout << "Student #" << i+1 << '\n' << students[i] << '\n';
    }
    cout << '\n';
    myMinH.remove(students, s2);
    for (int i = 0; i < myMinH.length; ++i) {
        cout << "Student #" << i+1 << '\n' << students[i] << '\n';
    }
}