#ifndef ASSIGN33_NODE_H
#define ASSIGN33_NODE_H
#include "Student.h"
class Node {
public:
    Student student;
    Node* left;
    Node* right;
    int height;
};
#endif //ASSIGN33_NODE_H
