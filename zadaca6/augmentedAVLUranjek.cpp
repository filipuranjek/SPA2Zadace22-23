#include <iostream>
#include <vector>

using namespace std;

struct Node
{
	int key;
    int height;
    int size;
	Node *left, *right, *parent;
};

class AVL
{
private:
    
    Node *root; 

	int height(Node *node)
	{
		if (node == nullptr)
			return 0;
		
        return node->height;
	}

    int size(Node* node){
        if (node == nullptr)
			return 0;
		
        return node->size;
    }

    Node* rightRotate(Node *y)
    {
        Node *x = y->left;
        Node *temp = x->right;

        auto temps = x->right->size;
        x->size = y->size;
        y->size = y->left->size + temps + 1;

        x->right = y;
        y->left = temp;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        if(temp != nullptr)
            temp->parent = y;

        x->parent = y->parent;
        y->parent = x;

        return x;
    }

    Node* leftRotate(Node *x)
    {
        Node *y = x->right;
        Node *temp = y->left;

        auto temps = y->left->size;
        y->size = x->size;
        x->size = x->left->size + temps + 1;

        y->left = x;
        x->right = temp;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        if(temp != nullptr)
            temp->parent = x;

        y->parent = x->parent;
        x->parent = y; 

        return y;
    }

    int balanceOfNode(Node *node)
    {
        if(node == nullptr)
            return 0;
        
        return height(node->left) - height(node->right);
    }

    Node* insert(Node *node, int key)
    {
        if(node == nullptr)
            node = new Node {key, 0, 1, nullptr, nullptr, nullptr};
        else if(key < node->key)
        {
            node->left = insert(node->left, key);
            node->left->parent = node;
            node->size++;
        }
        else if(key > node->key)
        {
            node->right = insert(node->right, key);
            node->right->parent = node;
            node->size++;
        }

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = balanceOfNode(node);

        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        if (balance < -1 && key > node->right->key)
            return leftRotate(node);
        
        if (balance > 1 && key > node->left->key)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && key < node->right->key)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    
        return node;
    }

    void inorder(Node *node)
    {
        if(node == nullptr)
            return;
        
        inorder(node->left);
        cout << "[K: " << node->key << ", H: " << node->height << ", B: " << balanceOfNode(node) << " , S: " << node->size << "] ";
        inorder(node->right);
    }

    void preorder(Node *node)
    {
        if(node == nullptr)
            return;
        
        cout << "[K: " << node->key << ", H: " << node->height << ", B: " << balanceOfNode(node) << " , S: " << node->size << "] ";
        inorder(node->left);
        inorder(node->right);
    }

    Node* OS_SELECT(Node* node, int i){
        if(node == nullptr){
            return nullptr;
        }

        int r = size(node->left) + 1;
        if(r == i){
            return node;
        }else if (i < r){
            return OS_SELECT(node->left, i);
        }else{
            return OS_SELECT(node->right, i - r);
        }
    }

    Node* search(int key, Node *node) {
        if (node == nullptr || key == node->key)
            return node;
        if (key > node->key)
            return search(key, node->right);
        return search(key, node->left);
    }

    int OS_RANK(Node* x) {
        int r;
        if(x->left == nullptr){
            r = 1;
        }else{
            r = x->left->size + 1;
        }
        Node* y = x;
        while(y != root) {
            if(y == y->parent->right) {
                int z;
                if(y->parent->left == nullptr){
                    z = 1;
                }else{
                    z = y->parent->left->size + 1;
                }
                r += z;
            }
            y = y->parent;
        }
        return r;
    }

public:
    AVL() : root(nullptr) {}

    Node* getRoot(){
        return root;
    }

	void insert(int key)
	{
        root = insert(root, key);
	}

    void printInorder()
    {
        inorder(root);
    }

    void printPreorder()
    {
        preorder(root);
    }

    void OS_SELECT(int i){
        Node* node = OS_SELECT(root, i);
        cout << "[K: " << node->key << ", H: " << node->height << ", B: " << balanceOfNode(node) << " , S: " << node->size << "] ";
    }

    int OS_KEY_RANK_class(Node* node, int k){
        Node* n = search(k, root);
        if(n == nullptr){
            return -1;
        }else{
            return OS_RANK(n);
        }
    }

    void ithSuccessor(int key, int i){
        Node* x = search(key, root);
        if(x == nullptr){
            return;
        }

        int r = OS_RANK(x);
        Node* y = OS_SELECT(root, i+r);

        if(y == nullptr){
            return;
        }

        cout << y->key << endl;
    }
};

int OS_KEY_RANK(AVL& T, int k) {
    return T.OS_KEY_RANK_class(T.getRoot(), k);
}

int main(){
    AVL avl;
    avl.insert(29);
    avl.insert(6);
    avl.insert(56);
    avl.insert(3);
    avl.insert(7);
    avl.insert(37);
    avl.insert(61);
    avl.insert(4);
    avl.insert(22);
    avl.insert(48);
    avl.insert(59);
    avl.insert(69);

    avl.printInorder();

    cout << endl << "-------------------------------------------------------------------------" << endl;
    
    avl.OS_SELECT(3);

    cout << endl << "-------------------------------------------------------------------------" << endl;

    cout << OS_KEY_RANK(avl, 22);

    cout << endl << "-------------------------------------------------------------------------" << endl;

    avl.ithSuccessor(29, 2); cout << endl;    
    return 0;
}
	