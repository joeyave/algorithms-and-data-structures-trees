#pragma once
enum Color { RED, BLACK, DOUBLE_BLACK };

struct Node
{
	int val;
	int color;
	Node* left;
	Node* right;
	Node* parent;
	
	explicit Node(int _val)
	{
		val = _val;
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
	}
	
	void insert(int n);
	void remove(int data);
	void inorder();
	void preorder();

private:
	Node* root;

	void left_rotate(Node*&);
	void right_rotate(Node*&);
	void fix_insert(Node*&);
	void fix_delete(Node*&);
	void inorder(Node*&);
	void preorder(Node*&);
	int get_color(Node*&);
	void set_color(Node*&, int);
	Node* min(Node * root);
	Node* max(Node * root);
	Node* insert(Node*&, Node*&);
	Node* remove(Node*&, int);
	int get_black_height(Node*);
};