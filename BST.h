#ifndef ASSIGNMENT_3_BST_H
#define ASSIGNMENT_3_BST_H

#include "Student.h"
#include "Node.h"
class BST {
public:
    Node* root = nullptr;
    // (left -> root -> right)
    void Traverse(Node* p ) {
        if(p!=nullptr){
            Traverse(p->left);
            cout<<p->student;
            Traverse(p->right);
        }
    }

    //Insertion in a binary search tree
    [[nodiscard]] Node* search(int el) const{
        Node* cur = root;
        while(cur != nullptr && cur->student.id != el){
            if(el < cur ->student.id){
                cur = cur ->left;
            }else{
                cur = cur->right;
            }
        }
        if(cur != nullptr && cur->student.id == el){
            return cur;
        }
        return nullptr;
    }
    //Insertion in a binary search tree
    void addStudent(const Student& stu){
        if(search(stu.id) != nullptr){
            cout << "Can't Insert Student..ID Already Exists\n";
            return;
        }
        Node* cur = root;
        Node* pr = nullptr;
        while(cur != nullptr)
        {
            pr = cur;
            if(stu.id < cur ->student.id)
            {
                cur = cur ->left;
            }
            else
            {
                cur = cur->right;
            }
        }
        Node* newnode = new Node();
        newnode->student = stu ;
        newnode->right = nullptr;
        newnode->left = nullptr;
        //if tree is empty
        if(pr == nullptr)
        {
            root = newnode;
        }
        else if(pr-> student.id < stu.id  )
        {
            pr->right =  newnode;
        }
        else
        {
            pr->left =newnode;
        }
    }
    //Deletion in a binary search tree
    void Delete(Node *node)
    {
        if(node == nullptr){
            cout << "Student Not Found\n";
            return;
        }
        //get node prev
        Node* prev = root;
        while((prev->left != node && prev->right != node) && prev != node){
            if(node->student.id < prev ->student.id){
                prev = prev ->left;
            }else{
                prev = prev->right;
            }
        }
        //node is a leaf
        if(node->left == nullptr && node->right == nullptr )
        {
            if(prev->left == node )
            {
                prev -> left = nullptr;
            }
            else
            {
                prev -> right = nullptr;
            }
            return;
        }
        //node has no left child
        if(node->left == nullptr)
        {
            node->student.id = node->right->student.id;
            node->left = node->right->left;
            node->right = node->right->right;
        }
            //node has no right child
        else if(node->right == nullptr)
        {
            node->student.id= node->left->student.id;
            node->right = node->left->right;
            node->left = node->left->left;
        }
            //node has two children
        else
        {
            Node* p = node->right;
            while(p -> left!=nullptr){
                p = p->left;
            }
            Node* prevp = node->right;
            while(prevp->left != p){
                prevp = prevp->left;
            }
            node -> student.id = p->student.id;
            prevp -> left = nullptr;


        }

    }
    void departmentReport(Node *node) {
        map<string, int> count;
        countStudentsPerDepartment(node, count);
        for (auto [department, county] : count) {
            cout << department << ": " << county << " students." << endl;
        }
    }
    void countStudentsPerDepartment(Node *node, map<string, int>& count) {
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
#endif //ASSIGNMENT_3_BST_H
