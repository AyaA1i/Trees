#ifndef ASSIGNMENT_3_MAXHEAP_H
#define ASSIGNMENT_3_MAXHEAP_H
#include "Student.h"
class MaxHeap {
public:
    int length = 0;
    Student* array = new Student[100];
    void MaxHeapify(int i){
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
            MaxHeapify(max);
        }
    }
    void AddStudent(Student NewS){
        array[length] = std::move(NewS);
        length++;
        for (int i = length/2 - 1; i >= 0; --i) {
            MaxHeapify(i);
        }
    }
    void RemoveStudent(int id) {
        bool found = false;
        int i;
        for (i = 0; i < length; ++i) {
            if (array[i].id == id) {
                found = true;
                break;
            }
        }
        if (found) {
            array[i] = array[length - 1];
            length--;
            MaxHeapify(i);
            for (int j = length/2 - 1; j >= 0; j--)
            {
                MaxHeapify(j);
            }
        }
        else {
            cout << "Student Not Found";
        }
    }
    void SortHeap(){
        int SortedL = -1;
        int L = length;
        auto* SortedStudents = new Student[length];
        for (int i = 0; i < L; ++i) {
            SortedStudents[++SortedL] = array[0];
            RemoveStudent(array[0].id);
        }
        for (int i = 0; i <= SortedL; ++i) {
            array[i] = SortedStudents[i];
            length++;
        }
    }
    void Dep_Report() const{
        map<string, int> Dep_Stud;
        for (int i = 0; i < length; ++i) {
            Dep_Stud[array[i].department]++;
        }
        for (auto & i : Dep_Stud) {
            cout << i.first << " Department Has " << i.second << " Students\n";
        }
    }
    void Print(){
        SortHeap();
        for (int i = 0; i < length; ++i) {
            cout << array[i] << '\n';
        }
    }
};

#endif //ASSIGNMENT_3_MAXHEAP_H
