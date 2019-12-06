#pragma once

enum Color { RED, BLACK, DOUBLE_BLACK };

struct Node
{
	int value;
	int color;
	Node* left;
	Node* right;
	Node* parent;
	bool is_black;

	explicit Node(int val)
	{
		is_black = false;
		value = val;
		color = RED;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	}
};

class RBTree
{	
public:
	RBTree()
	{
		root = nullptr;
	}
	
	void insert(int val);
	void remove(int data);
	void inorder();
	void preorder();

private:
	Node* root;
	Node* nil;
	
	void left_rotate(Node*&);
	void right_rotate(Node*&);
	void fix_insert(Node*&);
	void fix_delete(Node*&);
	Node* successor(Node* root);
	Node* predecessor(Node* root);
	Node* iterative_search(int key, Node* root);
	Node* search(int key, Node* root);
	void inorder(Node*&);
	void preorder(Node*&);
	int get_color(Node*&);
	void set_color(Node*&, int);
	Node* min(Node * root);
	Node* max(Node * root);
	Node* insert(Node*&, Node*&);
	Node* remove(Node*&, int);
	void Transplant(Node* old_node, Node* new_node);
	Node* Least(Node* cursor) const;
	Node* Successor(Node* cursor) const;
	void deleteNodeHelper(Node* node, int key);
	void deleteNode(int data);
	int get_black_height(Node*);
};