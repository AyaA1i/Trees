#include<bits/stdc++.h>
using namespace std;
/////////////////////BinaryTreeTraverse///////////////////
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
        void Traverse(Node* p ) {
            if(p!=nullptr){
                Traverse(p->left);
                cout<<p->item<<" ";
                Traverse(p->right);
            }
        }

        //Insertion in a binary search tree
         Node* search(int el) const{
            Node* cur = root;
            while(cur != nullptr && cur->item != el){
                if(el < cur ->item){
                    cur = cur ->left;
                }else{
                    cur = cur->right;
                }
            }
            if(cur != nullptr && cur->item == el){
                return cur;
            }
            return nullptr;
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
        //Deletion in a binary search tree
        void Delete(Node *node)
        {
            //get node prev
            Node* prev = root;
            while((prev->left != nullptr && prev->right!= nullptr)
            && (prev->left->item != node->item && prev->right->item != node->item)){
                if(node->item < prev ->item){
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
                node->item = node->right->item;
                node->left = node->right->left;
                node->right = node->right->right;
            }
            //node has no right child
            else if(node->right == nullptr)
            {
                node->item = node->left->item;
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
                node -> item = p->item;
                prevp -> left = nullptr;


            }

        }
    };
}
int main(){
    tree :: BST obj;
    obj.insert(5);
    obj.insert(7);
    obj.insert(6);
    obj.insert(4);
    obj.insert(29);
    obj.insert(-1);
    obj.insert(30);
    obj.insert(28);
    obj.Traverse(obj.root);
    cout<<endl;
    if(obj.search(-1)!= nullptr)
    {
        cout<<"FOUND";
    }else{
        cout<<"NOT FOUND";
    }
    cout<<endl;
    obj.Delete(obj.search(5));
    obj.Traverse(obj.root);

}
