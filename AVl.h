#ifndef ASSIGN33_AVL_H
#define ASSIGN33_AVL_H
#include "Student.h"
#include "Node.h"

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
            cout<<node->student;
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
#endif //ASSIGN33_AVL_H
