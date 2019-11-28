#pragma once

enum Color { RED, BLACK, DOUBLE_BLACK };

struct Node
{
	int data;
	int color;
	Node* left;
	Node* right;
	Node* parent;
	
	explicit Node(int data)
	{
		this->data = data;
		color = RED;
		left = right = parent = nullptr;
	}
};

class RBTree
{
private:
	Node* root;
protected:
	void rotateLeft(Node*&);
	void rotateRight(Node*&);
	void fixInsert(Node*&);
	void fixDelete(Node*&);
	void inorder(Node*&);
	void preorder(Node*&);
	int getColor(Node*&);
	void setColor(Node*&, int);
	Node* min(Node*&);
	Node* max(Node*&);
	Node* insert(Node*&, Node*&);
	Node* remove(Node*&, int);
	int getBlackHeight(Node*);
	
public:
	RBTree();
	void insert(int);
	void remove(int);
	void inorder();
	void preorder();
};