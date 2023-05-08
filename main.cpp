#include <iostream>
#include <cctype>
#include "AVL.h"
#include "BST.h"
#include "MaxHeap.h"
#include "MinHeap.h"
int main() {
    avlTree avl;
    BST bst;
    MaxHeap maxHeap;
    MinHeap minHeap;
    ifstream File("Students.txt");
    if (!File) {
        cerr << "Failed to open file" << endl;
        return 1;
    }
    int  numberOfStudents;
    File >> numberOfStudents;
    File.ignore();
    for (int i = 0; i < numberOfStudents; i++) {
        int id;
        string name, department;
        double gpa;
        File >> id;
        File.ignore();
        getline(File, name);
        File >> gpa;
        File.ignore();
        getline(File, department);
        avl.addStudent(id, name, gpa, department);
        Student obj;
        obj.id = id;
        obj.name = name;
        obj.GPA = gpa;
        obj.department = department;
        bst.addStudent(obj);
        maxHeap.AddStudent(obj);
        minHeap.AddStudent(obj);
    }

    File.close();
    int dataStructureChoice;
    int choice;
    int id;
    string name;
    double gpa;
    Student obj2;
    string department;
    while (true) {
        cout << "Choose Data Structure:" << endl;
        cout << "1. BST" << endl;
        cout << "2. AVL" << endl;
        cout << "3. Max Heap" << endl;
        cout << "4. Min Heap" << endl;
        cout << "5. Exit Program" << endl;
        cin >> dataStructureChoice;
        switch (dataStructureChoice) {
            case 1:
                while (true){
                    cout << "Choose one of the following options:" << endl;
                    cout << "1. Add student" << endl;
                    cout << "2. Remove student" << endl;
                    cout << "3. Search student" << endl;
                    cout << "4. Print All (sorted by id)" << endl;
                    cout << "5. Return to main menu" << endl;
                    cin >> choice;
                    switch (choice) {
                        case 1:
                            cout << "Enter the student's ID, name, GPA and department :" << endl;
                            cin >> id >> name >> gpa >> department;
                            if(bst.validate(id, gpa, department)){
                                obj2.id = id;
                                obj2.name = name;
                                obj2.GPA = gpa;
                                transform(department.begin(), department.end(),department.begin(), ::toupper);
                                obj2.department = department;
                                bst.addStudent(obj2);
                            }
                            break;
                        case 2:
                            cout << "Enter the ID of the student to remove:" << endl;
                            cin >> id;
                            bst.Delete(bst.search(id));
                            break;
                        case 3:
                            cout << "Enter the ID of the student to search for:" << endl;
                            cin >> id;
                            if(bst.search(id)!= nullptr)
                            {
                                cout<<"FOUND\n";
                                cout<<bst.search(id)->student;
                            }
                            else{
                                cout<<"NOT FOUND\n";
                            }
                            break;
                        case 4:
                            bst.Traverse(bst.root);
                            bst.departmentReport(bst.root);
                            break;
                        case 5:
                            break;
                        default:
                            cout << "Invalid choice." << endl;
                            break;
                    }
                    if (choice == 5) {
                        break;
                    }
                }
                break;
            case 2:
                while (true) {
                    cout << "Choose one of the following options:" << endl;
                    cout << "1. Add student" << endl;
                    cout << "2. Remove student" << endl;
                    cout << "3. Search student" << endl;
                    cout << "4. Print All (sorted by id)" << endl;
                    cout << "5. Return to main menu" << endl;
                    cin >> choice;
                    switch (choice) {
                        case 1:
                            cout << "Enter the student's ID, name, GPA and department :" << endl;
                            cin >> id >> name >> gpa >> department;
                            if(avl.validate(id, gpa, department)){
                                obj2.id = id;
                                obj2.name = name;
                                obj2.GPA = gpa;
                                transform(department.begin(), department.end(),department.begin(), ::toupper);
                                obj2.department = department;
                                avl.addStudent(id, name, gpa, department);
                            }
                            break;
                        case 2:
                            cout << "Enter the ID of the student to remove:" << endl;
                            cin >> id;
                            avl.removeStudent(id);
                            break;
                        case 3:
                            cout << "Enter the ID of the student to search for:" << endl;
                            cin >> id;
                            avl.searchStudent(id);
                            break;
                        case 4:
                            avl.printAll(avl.root);
                            avl.departmentReport(avl.root);
                            break;
                        case 5:
                            break;
                        default:
                            cout << "Invalid choice." << endl;
                            break;
                    }
                    if (choice == 5) {
                        break;
                    }
                }
                break;
            case 3:
                while (true){
                    cout << "Choose one of the following options:" << endl;
                    cout << "1. Add student" << endl;
                    cout << "2. Remove student" << endl;
                    cout << "3. Print All (sorted by GPA)" << endl;
                    cout << "4. Return to main menu" << endl;
                    cin >> choice;
                    switch (choice) {
                        case 1:
                            cout << "Enter the student's ID, name, GPA and department :" << endl;
                            cin >> id >> name >> gpa >> department;
                            if(maxHeap.validate(id, gpa, department)){
                                obj2.id = id;
                                obj2.name = name;
                                obj2.GPA = gpa;
                                transform(department.begin(), department.end(),department.begin(), ::toupper);
                                obj2.department = department;
                                maxHeap.AddStudent(obj2);
                            }
                            break;
                        case 2:
                            cout << "Enter the ID of the student to remove:" << endl;
                            cin >> id;
                            maxHeap.RemoveStudent(id);
                            break;
                        case 3:
                            maxHeap.Print();
                            maxHeap.Dep_Report();
                            break;
                        case 4:
                            break;
                        default:
                            cout << "Invalid choice." << endl;
                            break;
                    }
                    if (choice == 4) {
                        break;
                    }
                }
                break;
            case 4:
                while (true){
                    cout << "Choose one of the following options:" << endl;
                    cout << "1. Add student" << endl;
                    cout << "2. Remove student" << endl;
                    cout << "3. Print All (sorted by GPA)" << endl;
                    cout << "4. Return to main menu" << endl;
                    cin >> choice;
                    switch (choice) {
                        case 1:
                            cout << "Enter the student's ID, name, GPA and department :" << endl;
                            cin >> id >> name >> gpa >> department;
                            if(minHeap.validate(id, gpa, department)){
                                obj2.id = id;
                                obj2.name = name;
                                obj2.GPA = gpa;
                                transform(department.begin(), department.end(),department.begin(), ::toupper);
                                obj2.department = department;
                                minHeap.AddStudent(obj2);
                            }
                            break;
                        case 2:
                            cout << "Enter the ID of the student to remove:" << endl;
                            cin >> id;
                            minHeap.RemoveStudent(id);
                            break;
                        case 3:
                            minHeap.Print();
                            minHeap.Dep_Report();
                            break;
                        case 4:
                            break;
                        default:
                            cout << "Invalid choice." << endl;
                            break;
                    }
                    if (choice == 4) {
                        break;
                    }
                }
                break;
            case 5:
                exit(0);
            default:
                // Invalid choice
                cout << "Invalid choice." << endl;
                break;
        }
    }
}
