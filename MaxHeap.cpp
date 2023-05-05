#include <iostream>
#include <map>
#include <utility>
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
    void MaxHeapify(Student* array, int i){
        int left = 2*i + 1;
        int right = 2*i + 2;
        int max = i;
        if(left < length && array[max].GPA < array[left].GPA){
            max = left;
        }
        else if(right < length && array[max].GPA < array[right].GPA){
            max = right;
        }
        if(max != i){
            swap(array[max], array[i]);
            MaxHeapify(array, max);
        }
    }
    void insert(Student* array, Student NewS){
        array[length] = std::move(NewS);
        length++;
        for (int i = length/2 - 1; i >= 0; --i) {
            MaxHeapify(array, i);
        }
    }
    void remove(Student* array, const Student& S) {
        bool found = false;
        int i;
        for (i = 0; i < length; ++i) {
            if (array[i].id == S.id) {
                found = true;
                break;
            }
        }
        if (found) {
            array[i] = array[length - 1];
            length--;
            MaxHeapify(array, i);
            for (int j = length/2 - 1; j >= 0; j--)
            {
                MaxHeapify(array, j);
            }
        }
        else {
            cout << "Student Not Found";
        }
    }
    void SortHeap(Student* array){
        int SortedL = -1;
        int L = length;
        Student* SortedStudents = new Student[length];
        for (int i = 0; i < L; ++i) {
            SortedStudents[++SortedL] = array[0];
            remove(array, array[0]);
        }
        for (int i = 0; i <= SortedL; ++i) {
            array[i] = SortedStudents[i];
            length++;
        }
    }
    void Dep_Report(Student* array) const{
        map<string, int> Dep_Stud;
        for (int i = 0; i < length; ++i) {
            Dep_Stud[array[i].Dep]++;
        }
        for (auto & i : Dep_Stud) {
            cout << i.first << " Department Has " << i.second << " Students\n";
        }
    }
};


int main(){
    MinHeap myMaxH;
    Student students[10];
    Student s1;
    s1.Name = "Mariam";
    s1.Dep = "IS";
    s1.GPA = 0.99;
    s1.id = 1;
    Student s2;
    s2.Name = "Aya";
    s2.Dep = "IS";
    s2.GPA = 3.77;
    s2.id = 2;
    Student s3;
    s3.Name = "Habiba";
    s3.Dep = "DS";
    s3.GPA = 2.69;
    s3.id = 3;
    Student s4;
    s4.Name = "Khaled";
    s4.Dep = "AI";
    s4.GPA = 3.12;
    s4.id = 4;
    Student s5;
    s5.Name = "Mohammed";
    s5.Dep = "DS";
    s5.GPA = 1.93;
    s5.id = 5;
    Student s6;
    s6.Name = "Osama";
    s6.Dep = "CS";
    s6.GPA = 0.69;
    s6.id = 6;
    Student s7;
    s7.Name = "Ahmed";
    s7.Dep = "AI";
    s7.GPA = 1.65;
    s7.id = 7;
    myMaxH.insert(students, s1);
    myMaxH.insert(students, s2);
    myMaxH.insert(students, s3);
    myMaxH.insert(students, s4);
    myMaxH.insert(students, s5);
    myMaxH.insert(students, s6);
    myMaxH.insert(students, s7);
    for (int i = 0; i < myMaxH.length; ++i) {
        cout << "Student #" << i+1 << '\n' << students[i] << '\n';
    }
    cout << '\n';
    cout << "#################################\n";

    myMaxH.remove(students, s5);
    for (int i = 0; i < myMaxH.length; ++i) {
        cout << "Student #" << i+1 << '\n' << students[i] << '\n';
    }
    cout << "#################################\n";
    myMaxH.SortHeap(students);
    for (int i = 0; i < myMaxH.length; ++i){
        cout << "Student #" << i+1 << '\n' << students[i] << '\n';
    }
}
