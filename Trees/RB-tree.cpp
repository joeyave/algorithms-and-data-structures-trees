#include "RB-tree.h"
#include <iomanip>
#include <iostream>

int RBTree::getColor(Node*& node)
{
	if (node == nullptr)
		return BLACK;

	return node->color;
}

void RBTree::setColor(Node*& node, int color) {
	if (node == nullptr)
		return;

	node->color = color;
}

Node* RBTree::insert(Node*& root, Node*& ptr) {
	if (root == nullptr)
		return ptr;

	if (ptr->data < root->data) {
		root->left = insert(root->left, ptr);
		root->left->parent = root;
	}
	else if (ptr->data > root->data) {
		root->right = insert(root->right, ptr);
		root->right->parent = root;
	}

	return root;
}

void RBTree::insert(int n) {
	Node* node = new Node(n);
	root = insert(root, node);
	fixInsert(node);
}

void RBTree::rotateLeft(Node*& ptr)
{
	Node* right_child = ptr->right;
	ptr->right = right_child->left;

	if (ptr->right != nullptr)
		ptr->right->parent = ptr;

	right_child->parent = ptr->parent;

	if (ptr->parent == nullptr)
		root = right_child;
	else if (ptr == ptr->parent->left)
		ptr->parent->left = right_child;
	else
		ptr->parent->right = right_child;

	right_child->left = ptr;
	ptr->parent = right_child;
}

void RBTree::rotateRight(Node*& ptr)
{
	Node* left_child = ptr->left;
	ptr->left = left_child->right;

	if (ptr->left != nullptr)
		ptr->left->parent = ptr;

	left_child->parent = ptr->parent;

	if (ptr->parent == nullptr)
		root = left_child;
	else if (ptr == ptr->parent->left)
		ptr->parent->left = left_child;
	else
		ptr->parent->right = left_child;

	left_child->right = ptr;
	ptr->parent = left_child;
}

void RBTree::fixInsert(Node*& ptr) {
	Node* parent = nullptr;
	Node* grandparent = nullptr;
	while (ptr != root && getColor(ptr) == RED && getColor(ptr->parent) == RED) {
		parent = ptr->parent;
		grandparent = parent->parent;
		if (parent == grandparent->left) {
			Node* uncle = grandparent->right;
			if (getColor(uncle) == RED) {
				setColor(uncle, BLACK);
				setColor(parent, BLACK);
				setColor(grandparent, RED);
				ptr = grandparent;
			}
			else {
				if (ptr == parent->right) {
					rotateLeft(parent);
					ptr = parent;
					parent = ptr->parent;
				}
				rotateRight(grandparent);
				std::swap(parent->color, grandparent->color);
				ptr = parent;
			}
		}
		else {
			Node* uncle = grandparent->left;
			if (getColor(uncle) == RED) {
				setColor(uncle, BLACK);
				setColor(parent, BLACK);
				setColor(grandparent, RED);
				ptr = grandparent;
			}
			else {
				if (ptr == parent->left) {
					rotateRight(parent);
					ptr = parent;
					parent = ptr->parent;
				}
				rotateLeft(grandparent);
				std::swap(parent->color, grandparent->color);
				ptr = parent;
			}
		}
	}
	setColor(root, BLACK);
}

void RBTree::fixDelete(Node*& node) {
	if (node == nullptr)
		return;

	if (node == root) {
		root = nullptr;
		return;
	}

	if (getColor(node) == RED || getColor(node->left) == RED || getColor(node->right) == RED) {
		Node* child = node->left != nullptr ? node->left : node->right;

		if (node == node->parent->left) {
			node->parent->left = child;
			if (child != nullptr)
				child->parent = node->parent;
			setColor(child, BLACK);
			delete (node);
		}
		else {
			node->parent->right = child;
			if (child != nullptr)
				child->parent = node->parent;
			setColor(child, BLACK);
			delete (node);
		}
	}
	else {
		Node* sibling = nullptr;
		Node* parent = nullptr;
		Node* ptr = node;
		setColor(ptr, DOUBLE_BLACK);
		while (ptr != root && getColor(ptr) == DOUBLE_BLACK) {
			parent = ptr->parent;
			if (ptr == parent->left) {
				sibling = parent->right;
				if (getColor(sibling) == RED) {
					setColor(sibling, BLACK);
					setColor(parent, RED);
					rotateLeft(parent);
				}
				else {
					if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
						setColor(sibling, RED);
						if (getColor(parent) == RED)
							setColor(parent, BLACK);
						else
							setColor(parent, DOUBLE_BLACK);
						ptr = parent;
					}
					else {
						if (getColor(sibling->right) == BLACK) {
							setColor(sibling->left, BLACK);
							setColor(sibling, RED);
							rotateRight(sibling);
							sibling = parent->right;
						}
						setColor(sibling, parent->color);
						setColor(parent, BLACK);
						setColor(sibling->right, BLACK);
						rotateLeft(parent);
						break;
					}
				}
			}
			else {
				sibling = parent->left;
				if (getColor(sibling) == RED) {
					setColor(sibling, BLACK);
					setColor(parent, RED);
					rotateRight(parent);
				}
				else {
					if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
						setColor(sibling, RED);
						if (getColor(parent) == RED)
							setColor(parent, BLACK);
						else
							setColor(parent, DOUBLE_BLACK);
						ptr = parent;
					}
					else {
						if (getColor(sibling->left) == BLACK) {
							setColor(sibling->right, BLACK);
							setColor(sibling, RED);
							rotateLeft(sibling);
							sibling = parent->left;
						}
						setColor(sibling, parent->color);
						setColor(parent, BLACK);
						setColor(sibling->left, BLACK);
						rotateRight(parent);
						break;
					}
				}
			}
		}
		if (node == node->parent->left)
			node->parent->left = nullptr;
		else
			node->parent->right = nullptr;
		delete(node);
		setColor(root, BLACK);
	}
}

Node* RBTree::remove(Node*& root, int data) {
	if (root == nullptr)
		return root;

	if (data < root->data)
		return remove(root->left, data);

	if (data > root->data)
		return remove(root->right, data);

	if (root->left == nullptr || root->right == nullptr)
		return root;

	Node* temp = min(root->right);
	root->data = temp->data;
	return remove(root->right, temp->data);
}

void RBTree::remove(int data) {
	Node* node = remove(root, data);
	fixDelete(node);
}

void RBTree::inorder(Node*& ptr) {
	if (ptr == nullptr)
		return;

	inorder(ptr->left);
	std::cout << ptr->data << " " << ptr->color << std::endl;
	inorder(ptr->right);
}

void RBTree::inorder()
{
	inorder(root);
}

void RBTree::preorder(Node*& ptr)
{
	if (ptr == nullptr)
		return;

	std::cout << ptr->data << " " << ptr->color << std::endl;
	preorder(ptr->left);
	preorder(ptr->right);
}

void RBTree::preorder() {
	preorder(root);
}

Node* RBTree::min(Node*& node)
{

	Node* ptr = node;

	while (ptr->left != nullptr)
		ptr = ptr->left;

	return ptr;
}

Node* RBTree::max(Node*& node)
{
	Node* ptr = node;

	while (ptr->right != nullptr)
		ptr = ptr->right;

	return ptr;
}

int RBTree::getBlackHeight(Node* node)
{
	int blackheight = 0;
	while (node != nullptr) 
	{
		if (getColor(node) == BLACK)
			blackheight++;
		node = node->left;
	}
	return blackheight;
}