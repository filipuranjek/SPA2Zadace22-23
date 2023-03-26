#include<iostream>
using namespace std;

struct Node{
    int key;
    int h;
    Node *left, *right, *parent;
};

class AVL{
private:
    Node* root;

    Node* Rotate_left(Node* x){
        Node* y = x->right;
        Node* z = y->left;

        y->left = x;
        x->right = z;

        if (z != nullptr)
            z->parent = x;

        x->h = max(height(x->left), height(x->right)) + 1;
        y->h = max(height(y->left), height(y->right)) + 1;

        y->parent = x->parent;
        x->parent = y;

        return y;
    }	

    Node* Rotate_right(Node* x){
        Node* y = x->left;
        Node* z = y->right;

    
        y->right = x;
        x->left = z;

        if(z != nullptr){
            z->parent = y;
        }
    
        x->h = max(height(x->left), height(x->right)) + 1;
        y->h = max(height(y->left), height(y->right)) + 1;

        y->parent = x->parent;
        x->parent = y;

        return y;
    }

    int Balance_Factor(Node* x){
        if(x == nullptr){
            return 0;
        }

        return height(x->left) - height(x->right);
    }

    Node* insert(int key, Node* node){
        if(node == nullptr){
            node = new Node{key, 0, nullptr, nullptr, nullptr};
        }else if(key < node->key){
            node->left = insert(key, node->left);
            node->left->parent = node;
        }else if(key > node->key){
            node->right = insert(key, node->right);
            node->right->parent = node;
        }else{
            return nullptr;
        }

        node->h = 1 + max(height(node->left), height(node->right));
        int balance = Balance_Factor(node);

        if(balance > 1 && key < node->left->key){
            return Rotate_right(node);
        }

        if(balance < -1 && key > node->right->key){
            return Rotate_left(node);
        }

        if(balance > 1 && key > node->left->key){
            node->left = Rotate_left(node->left);
            return Rotate_right(node);
        }

        if(balance < -1 && key < node->right->key){
            node->right = Rotate_right(node->right);
            return Rotate_left(node);
        }

        return node;
    }

    void inorder(Node* node){
        if(node == nullptr){
            return;
        }

        inorder(node->left);
        cout << node->key << " h:" << node->h << " " ;
        inorder(node->right);
    }

public:
    AVL(): root(nullptr) {};
    
    int height(Node* node){
        if(node == nullptr){
            return 0;
        }

        return node->h;
    }

    void print(){
        inorder(root);
    }

    void insert(int key){
        root = insert(key, root);
    }
    
};

int main(){
    AVL tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    tree.print();
    return 0;
}