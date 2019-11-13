#pragma once

struct Node
{
	int val;
	Node* left;
	Node* right;
	Node* parent;
	int height;
	
	Node(int _val)
	{
		val = _val;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
		height = 0;
	}
};

class BinarySearchTree
{
private:
	Node* root;

	Node* insert(Node* root, int val);
	// Time complexity is O(h).
	Node* search(int key, Node* root);
	// Time complexity is O(h).
	Node* iterative_search(int key, Node* root);
	// Time complexity is O(h).
	Node* successor(Node* root);
	// Time complexity is O(h).
	Node* predecessor(Node* root);
	// Time complexity is O(h).
	Node* max(Node* root);
	// Time complexity is O(h).
	Node* min(Node* root);
	// Tree traversals.
	//Inorder traversal (left -> root -> right).
	void inorder(Node* root);
	Node* remove(int val, Node* root);
	// UTILITY FUNCTIONS.
	void transplant(Node* root, Node* subtree1, Node* subtree2);
	// Runs in O(h) time.
	void remove(Node* root, Node* todelete);
	void destroy(Node* root);
	int find_distance_preorder(Node* root, int key);
	int find_distance_postorder(Node* root, int key);
	Node* temp;
	void search_preorder(Node* root, int key);
	void search_postorder(Node* root, int key);

public:
	BinarySearchTree();
	~BinarySearchTree();
	void insert(int val);
	void display();
	Node* search(int key);
	// Search using while loop. On most computers works faster.
	void iterative_search(int key);
	int max();
	int min();
	void remove(int key);
	void removeV2(int key);
	void destroy();
	int find_distance_preorder(int key);
	int find_distance_postorder(int key);
	Node* search_preorder(int key);
	Node* search_postorder(int key);
};