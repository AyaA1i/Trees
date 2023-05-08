#ifndef ASSIGNMENT_3_AVL_H
#define ASSIGNMENT_3_AVL_H
#include "Student.h"
#include "Node.h"

class avlTree {
public:
    Node *root;

    avlTree() {
        root = nullptr;
    }

    int heightOfNode(Node *node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    int balanceOfNode(Node *node) {
        if (node == nullptr) {
            return 0;
        }
        return heightOfNode(node->left) - heightOfNode(node->right);
    }

    Node *rotateRight(Node *y) {
        Node *x = y->left;
        Node *z = x->right;
        x->right = y;
        y->left = z;
        y->height = max(heightOfNode(y->left), heightOfNode(y->right)) + 1;
        x->height = max(heightOfNode(x->left), heightOfNode(x->right)) + 1;
        return x;
    }

    Node *rotateLeft(Node *x) {
        Node *y = x->right;
        Node *z = y->left;
        y->left = x;
        x->right = z;
        y->height = max(heightOfNode(y->left), heightOfNode(y->right)) + 1;
        x->height = max(heightOfNode(x->left), heightOfNode(x->right)) + 1;
        return y;
    }

    Node *insertNode(Node *node, const Student &stud) {
        if (node == nullptr) {
            Node *newNode = new Node();
            newNode->student = stud;
            newNode->right = nullptr;
            newNode->left = nullptr;
            newNode->height = 1;
            return newNode;
        }
        if (stud.id > node->student.id) {
            node->right = insertNode(node->right, stud);
        } else if (stud.id < node->student.id) {
            node->left = insertNode(node->left, stud);
        } else
            return node;
        node->height = max(heightOfNode(node->right), heightOfNode(node->left)) + 1;
        int treeBalance = balanceOfNode(node);
        if (treeBalance > 1 && node->left->student.id > stud.id) {
            return rotateRight(node);
        }
        if (treeBalance < -1 && node->right->student.id < stud.id) {
            return rotateLeft(node);
        }
        if (treeBalance > 1 && stud.id > node->left->student.id) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (treeBalance < -1 && stud.id < node->right->student.id) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    void addStudent(int id, string name, double gpa, string department) {
        if(searchNode(root, id)){
            cout << "Can't Insert Student..ID Already Exists\n";
            return;
        }
        Student stud = {id, std::move(name), department, gpa};
        root = insertNode(root, stud);
    }

    Node *deleteNode(Node *cur, int id) {
        if (cur == nullptr) {
            return nullptr;
        }
        if (id < cur->student.id) {
            cur->left = deleteNode(cur->left, id);
        } else if (id > cur->student.id) {
            cur->right = deleteNode(cur->right, id);
        } else {
            if (cur->left == nullptr || cur->right == nullptr) {
                Node *temp = cur->left ? cur->left : cur->right;
                if (temp == nullptr) {
                    temp = cur;
                    cur = nullptr;
                } else {
                    *cur = *temp;
                }
                delete temp;
            } else {
                Node *temp = minValue(cur->right);
                cur->student = temp->student;
                cur->right = deleteNode(cur->right, temp->student.id);
            }
        }
        if (cur == nullptr) {
            return nullptr;
        }
        cur->height = 1 + max(heightOfNode(cur->left), heightOfNode(cur->right));
        int balance = balanceOfNode(cur);

        if (balance > 1 && balanceOfNode(cur->left) >= 0) {
            return rotateRight(cur);
        }
        if (balance > 1 && balanceOfNode(cur->left) < 0) {
            cur->left = rotateLeft(cur->left);
            return rotateRight(cur);
        }
        if (balance < -1 && balanceOfNode(cur->right) <= 0) {
            return rotateLeft(cur);
        }
        if (balance < -1 && balanceOfNode(cur->right) > 0) {
            cur->right = rotateRight(cur->right);
            return rotateLeft(cur);
        }
        return cur;
    }

    Node *minValue(Node *node) {
        Node *current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    void removeStudent(int id) {
        root = deleteNode(root, id);
        cout << "Student with " << id << " is removed .\n";
    }

    Node *searchNode(Node *node, int id) {
        if (node == nullptr || node->student.id == id) {
            return node;
        }
        if (id < node->student.id) {
            return searchNode(node->left, id);
        }
        return searchNode(node->right, id);
    }

    void searchStudent(int id) {
        Node *res = searchNode(root, id);
        if (res == nullptr) {
            cout << "Student with ID " << id << " not found." << endl;
            return;
        } else{
            cout << "Student ID: " << res->student.id << endl;
            cout << "Name: " << res->student.name << endl;
            cout << "Department: " << res->student.department << endl;
            cout << "GPA: " << res->student.GPA << endl;
        }
    }

    void printAll(Node *node) {
        if (node != nullptr) {
            printAll(node->left);
            cout << node->student;
            printAll(node->right);
        }
    }

    void departmentReport(Node *node) {
        map<string, int> count;
        countStudentsPerDepartment(node, count);
        for (auto [department, county]: count) {
            cout << department << ": " << county << " students." << endl;
        }
    }

    void countStudentsPerDepartment(Node *node, map<string, int> &count) {
        if (node != nullptr) {
            countStudentsPerDepartment(node->left, count);
            count[node->student.department]++;
            countStudentsPerDepartment(node->right, count);
        }
    }

    bool validate(int id, double gpa, string d){
        transform(d.begin(), d.end(),d.begin(), ::toupper);
        if(id < 1 || id > 100){
            cout << "Invalid ID\n";
            return false;
        }
        if(gpa > 4 || gpa < 0){
            cout << "Invalid GPA\n";
            return false;
        }
        if(d != "IS" && d != "CS" && d != "AI" && d != "DS" && d != "IT"){
            cout << "Invalid Department..IS,CS,AI,DS,IT Valid\n";
            return false;
        }
        return true;
    }
};
#endif //ASSIGNMENT_3_AVL_H
