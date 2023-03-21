#include<iostream>
using namespace std;

struct Node{
    int key;
    Node *left, *right, *parent;

};

class BST{
    Node *root;

    Node* insert(int key, Node *node){
        Node* add = new Node();
        add->key = key;

        if(node == nullptr){
            root = add;
            return add;
        }

        Node* it = root;
        Node* par = nullptr;

        while(it != nullptr){
            par = it;
            if(add->key < it->key){
                it=it->left;
            }else{
                it=it->right;
            }
        }

        add->parent = par;
        if(add->key < par->key){
            par->left = add;
            return add;
        } else{
            par->right = add;
            return add;
        }
    }

    void inorder(Node* node){
        if(node != nullptr){
            inorder(node->left);
            cout << node->key << " ";
            inorder(node->right);
        }
    }

    Node* search(int key, Node* node){
        if(node == nullptr){
            return nullptr;
        }
        if(node->key == key){
            return node;
        } else if(node->key < key){
            search(key, node->right);
        } else{
            search(key, node->left);
        }
    }

    Node* find_min(Node* node){
        while(node->left != nullptr){
            node = node->left;
        }

        return node;
    }

    Node* find_max(Node* node){
        while(node->right != nullptr){
            node = node->right;
        }

        return node;
    }

    Node* successor(Node *node){
        if(node->right != nullptr){
            return find_min(node->right);
        }

        Node* y = node->parent;
        while( y != nullptr && node == y->right){
            node = y;
            y = y->parent;
        }

        return y;
    }

    Node* predecessor(Node* node){
        if(node->left != nullptr){
            return find_max(node->left);
        }

        Node* y = node->parent;
        while( y != nullptr && node == y->left){
            node = y;
            y = y->parent;
        }

        return y;
    }

    void transplant(Node* u, Node* v){
        if(u->parent == nullptr){
            root = v;
        } else if(u == u->parent->left){
            u->parent->left = v;
        } else{
            u->parent->right = v;
        }
    
        if(v != nullptr){
            v->parent= u->parent;
        }
    }

    Node* BSTdelete(int key, Node* node){
        Node* n = search(key, node);
        if(n == nullptr){
            return nullptr;
        }

        if(n->right == nullptr) {
            Node* ret = n->left;
            transplant(n, n->left);
            delete n;
            return ret;
            
        }else if(n->left == nullptr) {
            Node* ret = n->right;
            transplant(n, n->right);
            delete n;
            return ret;
        } else{
            Node* y = successor(n);
            if(y->parent != n) {
                transplant(y, y->parent);
                y->right = n->right;
                y->right->parent = y;
            }
            transplant(n, y);
            y->left = n->left;
            y->left->parent = y;

            return y;
        }
    }

public:
    BST() : root(nullptr){};

    void print(){
        inorder(root);
        cout << endl;
    }

    void insert(int key){
        insert(key, root);
    }

    bool search(int key){
        if(search(key,root) == nullptr){
            return false;
        }else{
            return true;
        }
    }

    int find_min(){
        Node* min = find_min(root);
        return(min->key);
    }

    int find_max(){
        Node* max = find_max(root);
        return(max->key);
    }

    int successor(int key){
        Node* n = search(key,root);
        Node* succ = successor(n);
        return(succ->key);
    }

    int predecessor(int key){
        Node* n = search(key,root);
        Node* prede = predecessor(n);
        return(prede->key);
    }

    void BSTdelete(int key){
        BSTdelete(key, root);
    }
};

int main(){
    BST bst;
    bst.insert(5);
    bst.insert(10);
    bst.insert(4);
    bst.insert(8);
    bst.insert(9);
    bst.insert(1);
    bst.insert(11);
    bst.insert(15);
    bst.insert(3);

    bst.print();

    cout << bst.find_min() << endl;
    cout << bst.find_max() << endl;

    cout << bst.successor(8) << endl;
    cout << bst.predecessor(10) << endl;

    bst.BSTdelete(10);

    bst.print();

    return 0;
}