#include "RB-tree.h"
#include <iomanip>
#include <iostream>

int RBTree::get_color(Node*& node)
{
	if (node == nullptr)
		return BLACK;

	return node->color;
}

void RBTree::set_color(Node*& node, int color)
{
	if (node == nullptr)
		return;

	node->color = color;
}

Node* RBTree::insert(Node*& root, Node*& ptr)
{
	if (root == nullptr)
		return ptr;

	if (ptr->val < root->val) 
	{
		root->left = insert(root->left, ptr);
		root->left->parent = root;
	}
	else if (ptr->val > root->val) 
	{
		root->right = insert(root->right, ptr);
		root->right->parent = root;
	}

	return root;
}

void RBTree::insert(int n)
{
	Node* node = new Node(n);
	root = insert(root, node);
	fix_insert(node);
}

void RBTree::left_rotate(Node*& ptr)
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

void RBTree::right_rotate(Node*& ptr)
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

void RBTree::fix_insert(Node*& ptr)
{
	/// 4 scenarious:
	/// 1. ptr = root -> color black.
	/// 2. ptr.uncle = red -> recolor.
	/// 3. ptr.uncle = black (triangle) -> rotate ptr.parent.
	/// 4. ptr.uncle = black (line) -> rotate ptr.grandparent.
	
	Node* parent = nullptr;
	Node* grandparent = nullptr;

	// Scenarious 2, 3, 4.
	while (ptr != root && get_color(ptr) == RED && get_color(ptr->parent) == RED) 
	{
		parent = ptr->parent;
		grandparent = parent->parent;
		
		if (parent == grandparent->left) 
		{
			Node* uncle = grandparent->right;

			// Scenario 2. Recolor.
			if (get_color(uncle) == RED)
			{
				set_color(uncle, BLACK);
				set_color(parent, BLACK);
				set_color(grandparent, RED);
				ptr = grandparent;
			}
			else
			{
				// If ptr is right child.
				// Scenario 3.
				if (ptr == parent->right)
				{
					left_rotate(parent);
					ptr = parent;
					parent = ptr->parent;
				}

				// If ptr is left child.
				// Scenario 4.
				right_rotate(grandparent);
				std::swap(parent->color, grandparent->color);
				ptr = parent;
			}
		}

		// Everything is the same. Just symmetrically.
		else 
		{
			Node* uncle = grandparent->left;
			if (get_color(uncle) == RED) 
			{
				set_color(uncle, BLACK);
				set_color(parent, BLACK);
				set_color(grandparent, RED);
				ptr = grandparent;
			}
			else
			{
				if (ptr == parent->left) 
				{
					right_rotate(parent);
					ptr = parent;
					parent = ptr->parent;
				}
				left_rotate(grandparent);
				std::swap(parent->color, grandparent->color);
				ptr = parent;
			}
		}
	}

	// Scenario 1.
	set_color(root, BLACK);
}

void RBTree::fix_delete(Node*& node)
{
	if (node == nullptr)
		return;

	if (node == root)
	{
		root = nullptr;
		return;
	}

	if (get_color(node) == RED || get_color(node->left) == RED || get_color(node->right) == RED)
	{
		Node* child = node->left != nullptr ? node->left : node->right;

		if (node == node->parent->left) 
		{
			node->parent->left = child;
			if (child != nullptr)
				child->parent = node->parent;
			set_color(child, BLACK);
			delete (node);
		}
		else 
		{
			node->parent->right = child;
			if (child != nullptr)
				child->parent = node->parent;
			set_color(child, BLACK);
			delete (node);
		}
	}
	else 
	{
		Node* sibling = nullptr;
		Node* parent = nullptr;
		Node* ptr = node;
		set_color(ptr, DOUBLE_BLACK);
		while (ptr != root && get_color(ptr) == DOUBLE_BLACK) 
		{
			parent = ptr->parent;
			if (ptr == parent->left) 
			{
				sibling = parent->right;

				// Lecture scenario 1.
				if (get_color(sibling) == RED) 
				{
					set_color(sibling, BLACK);
					set_color(parent, RED);
					left_rotate(parent);
				}

				// Lecture scenario 2. There are thee cases.
				else 
				{
					// Case A.
					if (get_color(sibling->left) == BLACK && get_color(sibling->right) == BLACK) 
					{
						set_color(sibling, RED);
						if (get_color(parent) == RED)
							set_color(parent, BLACK);
						else
							set_color(parent, DOUBLE_BLACK);
						ptr = parent;
					}
					else 
					{
						// Case B.
						if (get_color(sibling->right) == BLACK) 
						{
							set_color(sibling->left, BLACK);
							set_color(sibling, RED);
							right_rotate(sibling);
							sibling = parent->right;
						}

						// Case C.
						set_color(sibling, parent->color);
						set_color(parent, BLACK);
						set_color(sibling->right, BLACK);
						left_rotate(parent);
						break;
					}
				}
			}
			else
			{
				sibling = parent->left;
				if (get_color(sibling) == RED) 
				{
					set_color(sibling, BLACK);
					set_color(parent, RED);
					right_rotate(parent);
				}
				else 
				{
					if (get_color(sibling->left) == BLACK && get_color(sibling->right) == BLACK) 
					{
						set_color(sibling, RED);
						if (get_color(parent) == RED)
							set_color(parent, BLACK);
						else
							set_color(parent, DOUBLE_BLACK);
						ptr = parent;
					}
					else 
					{
						if (get_color(sibling->left) == BLACK)
						{
							set_color(sibling->right, BLACK);
							set_color(sibling, RED);
							left_rotate(sibling);
							sibling = parent->left;
						}
						set_color(sibling, parent->color);
						set_color(parent, BLACK);
						set_color(sibling->left, BLACK);
						right_rotate(parent);
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
		set_color(root, BLACK);
	}
}

Node* RBTree::remove(Node*& root, int data)
{
	if (root == nullptr)
		return root;

	if (data < root->val)
		return remove(root->left, data);

	if (data > root->val)
		return remove(root->right, data);

	if (root->left == nullptr || root->right == nullptr)
		return root;

	Node* temp = min(root->right);
	root->val = temp->val;
	return remove(root->right, temp->val);
}

void RBTree::remove(int data)
{
	Node* node = remove(root, data);
	fix_delete(node);
}

void RBTree::inorder(Node*& ptr)
{
	if (ptr == nullptr)
		return;

	inorder(ptr->left);
	std::cout << ptr->val << " " << ptr->color << std::endl;
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

	std::cout << ptr->val << " " << ptr->color << std::endl;
	preorder(ptr->left);
	preorder(ptr->right);
}

void RBTree::preorder()
{
	preorder(root);
}

Node* RBTree::min(Node * root)
{
	while (root->left != nullptr)
		root = root->left;
	return root;
}

Node* RBTree::max(Node * root)
{
	while (root->right != nullptr)
		root = root->right;
	return root;
}

int RBTree::get_black_height(Node* node)
{
	int blackheight = 0;
	while (node != nullptr) 
	{
		if (get_color(node) == BLACK)
			blackheight++;
		node = node->left;
	}
	return blackheight;
}