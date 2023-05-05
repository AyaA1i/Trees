#include <iostream>
#include<vector>
#include <map>
using namespace std;
struct Student{
    int id ;
    string name;
    string department;
    float GPA;
};
class Node {
public:
    Student student;
    Node* left;
    Node* right;
    int height;
};

class avlTree {
public:
    Node *root;

    avlTree() {
        root = NULL;
    }

    int heightOfNode(Node *node) {
        if (node == NULL)
            return 0;
        return node->height;
    }

    int balanceOfNode(Node *node) {
        if (node == NULL) {
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

    Node *insertNode(Node *node, Student stud) {
        if (node == NULL) {
            Node *newNode = new Node();
            newNode->student = stud;
            newNode->right = NULL;
            newNode->left = NULL;
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

    void addStudent(int id, string name, float gpa, string department) {
        if (id < 0 || id > 100) {
            cout << "InValiad Id . please write Id between 0 and 100 " << endl;
            return;
        }
        Student stud = {id, name, department, gpa};
        root = insertNode(root, stud);
    }

    Node *deleteNode(Node *root, int id) {
        if (root == NULL) {
            return NULL;
        }
        if (id < root->student.id) {
            root->left = deleteNode(root->left, id);
        } else if (id > root->student.id) {
            root->right = deleteNode(root->right, id);
        } else {
            if (root->left == NULL || root->right == NULL) {
                Node *temp = root->left ? root->left : root->right;
                if (temp == NULL) {
                    temp = root;
                    root = NULL;
                } else {
                    *root = *temp;
                }
                delete temp;
            } else {
                Node *temp = minValue(root->right);
                root->student = temp->student;
                root->right = deleteNode(root->right, temp->student.id);
            }
        }
        if (root == NULL) {
            return NULL;
        }
        root->height = 1 + max(heightOfNode(root->left), heightOfNode(root->right));
        int balance = balanceOfNode(root);

        if (balance > 1 && balanceOfNode(root->left) >= 0) {
            return rotateRight(root);
        }
        if (balance > 1 && balanceOfNode(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
        if (balance < -1 && balanceOfNode(root->right) <= 0) {
            return rotateLeft(root);
        }
        if (balance < -1 && balanceOfNode(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
        return root;
    }

    Node *minValue(Node *node) {
        Node *current = node;
        while (current->left != NULL) {
            current = current->left;
        }
        return current;
    }

    void removeStudent(int id) {
        root = deleteNode(root, id);
        cout << "Student with " << id << " is removed .\n";
    }

    Node *searchNode(Node *node, int id) {
        if (node == NULL || node->student.id == id) {
            return node;
        }
        if (id < node->student.id) {
            return searchNode(node->left, id);
        }
        return searchNode(node->right, id);
    }

    void searchStudent(int id) {
        Node *res = searchNode(root, id);
        if (res == NULL) {
            cout << "Student with ID " << id << " not found." << endl;
            return;
        } else
            cout << "Student ID: " << res->student.id << endl;
        cout << "Name: " << res->student.name << endl;
        cout << "Department: " << res->student.department << endl;
        cout << "GPA: " << res->student.GPA << endl;
        return;
    }void printAll(Node *node) {
        if (node != NULL) {
            printAll(node->left);
            cout << "Student ID: " << node->student.id << endl;
            cout << "Name: " << node->student.name << endl;
            cout << "Department: " << node->student.department << endl;
            cout << "GPA: " << node->student.GPA << endl << endl;
            printAll(node->right);
        }
    }

    void departmentReport(Node *node) {
        map<string, int> count;
        countStudentsPerDepartment(node, count);
        for (auto [department, count] : count) {
            cout << department << ": " << count << " students." << endl;
        }
    }
    void countStudentsPerDepartment(Node *node, map<string, int>& count) {
        if (node != NULL) {
            countStudentsPerDepartment(node->left, count);
            count[node->student.department]++;
            countStudentsPerDepartment(node->right, count);
        }
    }


};
int main() {
    avlTree avl;
    int dataStructureChoice;
    int avlchoice;
    int id;
    string name;
    double gpa;
    string department;
    while (true) {
        cout << "Choose Data Structure:" << endl;
        cout << "1. BST" << endl;
        cout << "2. AVL" << endl;
        cout << "3. Min Heap" << endl;
        cout << "4. Max Heap" << endl;
        cout << "5. Exit Program" << endl;
        cin >> dataStructureChoice;
        switch (dataStructureChoice) {
            case 1:

                break;
            case 2:
                while (true) {
                    cout << "Choose one of the following options:" << endl;
                    cout << "1. Add student" << endl;
                    cout << "2. Remove student" << endl;
                    cout << "3. Search student" << endl;
                    cout << "4. Print All (sorted by id)" << endl;
                    cout << "5. Return to main menu" << endl;
                    cin >> avlchoice;
                    switch (avlchoice) {
                        case 1:
                            cout << "Enter the student's ID, name, GPA and department :" << endl;
                            cin >> id >> name >> gpa >> department;
                            avl.addStudent(id, name, gpa, department);
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
                    if (avlchoice == 5) {
                        break;
                    }
                }
                break;
            case 3:
                //Heap
                break;
            case 4:
                //  Heap
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
