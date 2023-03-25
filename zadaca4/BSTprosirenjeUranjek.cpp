#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

struct Node
{
	int key;
	Node *left, *right, *parent;
};

class BST
{
	Node *root;
	
	Node* insert(int key, Node *node)
	{
		if (node == NULL) 
		{
			node = new Node;
			node->key = key;
			node->left = node->right = node->parent = NULL;
		} else if (key > node->key) 
		{
			node->right = insert(key, node->right);
			node->right->parent = node;
		} else 
		{
			node->left = insert(key, node->left);
			node->left->parent = node;
		}
		return node;
			
	}

	void inorder(Node *node)
	{
		if (node == NULL)
			return;
		inorder(node->left);
		cout << node->key << ' ';
		inorder(node->right);
	}

	void listOfNodes(Node* node, vector<int>& nodes){
		if(node == nullptr){
			return;
		}
		listOfNodes(node->left, nodes);
		nodes.push_back(node->key);
		listOfNodes(node->right, nodes);
	}

	Node* search(int key, Node *node)
	{
		if (node == NULL || key == node->key)
			return node;
		if (key > node->key)
			return search(key, node->right);
		return search(key, node->left);
	}

	Node* find_min(Node *node)
	{
		if (node == NULL)
			return NULL;
		if (node->left == NULL)
			return node;
		return find_min(node->left);
	}

	Node* find_max(Node *node)
	{
		if (node == NULL)
			return NULL;
		if (node->right == NULL)
			return node;
		return find_min(node->right);
	}

	Node* successor(Node *node)
	{
		if (node->right != NULL)
			return find_min(node->right);

		Node *parent = node->parent;
		while (parent != NULL && node == parent->right) {
			node = parent;
			parent = node->parent;
		}

		return parent;
	}

	Node* predecessor(Node *node)
	{
		if (node->left != NULL)
			return find_max(node->left);

		Node *parent = node->parent;
		while (parent != NULL && node == parent->left) {
			node = parent;
			parent = node->parent;
		}

		return parent;
	}

	bool nodesEqual(Node* node1, Node* node2){
        if(node1 == nullptr && node2 == nullptr){
            return true;
        }

        if(node1 != nullptr && node2 != nullptr){
            return(nodesEqual(node1->left, node2->left) && nodesEqual(node1->right, node2->right));
        }

        return false;
    }

	Node* nthPower(Node* node, int n){
		if(node != nullptr){
			Node* add = new Node;
			add->key = pow(node->key, n);
			add->left = nthPower(node->left, n);
			add->right = nthPower(node->right, n);
			return add;
		}else{
			return nullptr;
		}
	}

	Node* NodeAdd(Node* node1, Node* node2){
		if(node1 == nullptr && node2 == nullptr){
			return nullptr;
		}else if(node1==nullptr){
			Node* add = new Node;
			add->key = node2->key;
			return add;	
		} else if(node2 == nullptr){
			Node* add = new Node;
			add->key = node1->key;
			return add;
		}else{
			int sum = node1->key + node2->key;
        	Node* newNode = new Node;
			newNode->key = sum;
        	newNode->left = NodeAdd(node1->left, node2->left);
        	newNode->right = NodeAdd(node1->right, node2->right);
        	return newNode;
		}

		/*
		if(node1 != nullptr && node2 != nullptr){
			NodeAdd(node1->left,node2->left);
			node1-> key = node1->key + node2->key;
			NodeAdd(node1->right,node2->right);
		}
		*/
	}

	Node* buildTree(vector<int>& nodes, int start, int end, Node* parent){
		if(start > end){
			return nullptr;
		}

		int mid = (start + end) / 2;
		Node* add = new Node;
		add->key = nodes[mid];
		add->parent = parent;
		add->left = buildTree(nodes, start, mid-1, add);
		add->right = buildTree(nodes, mid+1, end, add);
		return add;
	}

public:
	BST() : root(NULL) {}
	
	void print()
	{
		inorder(root);
	}

	void insert(int key)
	{
		root = insert(key, root);
	}

	bool search(int key)
	{
		return search(key, root);
	}

	int find_min()
	{
		Node *node = find_min(root);
		if (node != NULL)
			return node->key;
		return -1;
	}

	int find_max()
	{
		Node *node = find_max(root);
		if (node != NULL)
			return node->key;
		return -1;
	}

	int successor(int key)
	{
		Node *node = search(key, root);
		if (node == NULL)
			return -1;
		node = successor(node);
		if (node == NULL)
			return -1;
		return node->key;
	}

	int predecessor(int key)
	{
		Node *node = search(key, root);
		if (node == NULL)
			return -1;
		node = predecessor(node);
		if (node == NULL)
			return -1;
		return node->key;
	}

	bool structurallyEqual(BST T1, BST T2){
        return nodesEqual(T1.root, T2.root);
    }

	BST nthPowerBST(BST T, int n){
		BST ret;
		ret.root = T.nthPower(T.root, n);
		return ret;
	}

	BST BSTbuilder(vector<int> nodes){
		BST ret;
		ret.root = buildTree(nodes, 0, nodes.size() - 1, nullptr);
	}

	BST BSTadd(BST T1, BST T2){
		if(T1.structurallyEqual(T1,T2)){
			BST ret;
			ret.root = T1.NodeAdd(T1.root, T2.root);
			return ret;
		}

		vector<int> nodes;
		T1.listOfNodes(T1.root, nodes);
		T2.listOfNodes(T2.root, nodes);

		sort(nodes.begin(), nodes.end());
		nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());

		//random_shuffle(nodes.begin(), nodes.end()); // nisam znao sta znaci što više binarno
		return BSTbuilder(nodes);
	}
};

int main()
{
BST T1, T2, T3, T4, T5, T6, T7, T8, T9;
    T1.insert(50);
    T1.insert(25);
    T1.insert(75);
    T1.insert(10);
    T1.insert(30);
    T1.insert(100);

    T2.insert(6);
    T2.insert(3);
    T2.insert(8);
    T2.insert(1);
    T2.insert(4);
    T2.insert(10);

    T3.insert(50);
    T3.insert(25);
    T3.insert(75);
    T3.insert(20);
    T3.insert(100);

    T4.insert(6);
    T4.insert(3);
    T4.insert(1);
    T4.insert(8);

	T5.insert(5);
	T5.insert(3);
	T5.insert(7);
	T5.insert(1);
	T5.insert(4);
	T5.insert(9);

	T6.insert(10);
	T6.insert(5);
	T6.insert(14);
	T6.insert(2);
	T6.insert(8);
	T6.insert(16);


    cout << T1.structurallyEqual(T1, T2) << endl;
    cout << T3.structurallyEqual(T3, T4) << endl;

	cout << "-----------------------------------------------------------------------------" << endl;

	T5.print();
	cout << endl;
	T8 = T5.nthPowerBST(T5,2);
	T8.print();
	cout << endl;
	T5.print();
	cout << endl;

	cout << "-----------------------------------------------------------------------------" << endl;

	T2.print();
	cout << endl;
	T7 = T2.BSTadd(T2, T6);
	T7.print();

	cout << endl;

	T9 = T4.BSTadd(T4, T1);
	T9.print();

}