#include<bits/stdc++.h>
using namespace std;
/////////////////////BinarySearchTree///////////////////
namespace tree{
    struct Node{
        int item;
        Node* left;
        Node* right;
    };
    class BST {
    public:
        Node* root = nullptr;
        // (left -> root -> right)
        void Traverse(Node *p){
            if(p!=nullptr){
                Traverse(p->left);
                cout<<p->item<<" ";
                Traverse(p->right);
            }
        }
        //Search in a binary search tree
        void search(int el){
            Node* cur = root;
            while(cur != nullptr && cur->item != el){
                if(el < cur ->item){
                    cur = cur ->left;
                }else{
                    cur = cur->right;
                }
            }
            if(cur == nullptr){
                cout<<"NOT FOUND.\n";
            }else{
                cout<<"Found.\n";
            }
        }
        //Insertion in a binary search tree
        void insert(int el){
            Node* cur = root;
            Node* pr = nullptr;
            while(cur != nullptr )
            {
                pr = cur;
                if(el < cur ->item)
                {
                    cur = cur ->left;
                }
                else
                {
                    cur = cur->right;
                }
            }
            Node* newnode = new Node();
            newnode->item = el;
            newnode->right = nullptr;
            newnode->left = nullptr;
            //if tree is empty
            if(pr == nullptr)
            {
                root = newnode;
            }
            else if(pr-> item < el )
            {
                pr->right =  newnode;
            }
            else
            {
                pr->left =newnode;
            }
        }

    };
}
int main(){
    tree :: BST obj;
    obj.insert(5);
//    obj.pre(obj.root);
    obj.insert(6);
//    obj.pre(obj.root);
    obj.insert(4);
    obj.insert(5);
    obj.search(0);
    obj.insert(29);obj.insert(-1);
    obj.Traverse(obj.root);
}
