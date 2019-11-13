#include "BinarySearchTree.h"
#include <algorithm>
#include <iostream>

int get_height(Node* node)
{
	return node == nullptr ? 0 : node->height;
}

// An utility function to right 
// rotate subtree rooted with y.  
Node* right_rotate(Node* y)
{
	Node* x = y->left;
	Node* T2 = x->right;

	// Perform rotation  
	x->right = y;
	y->left = T2;

	// Update heights  
	y->height = std::max(get_height(y->left),
		get_height(y->right)) + 1;
	x->height = std::max(get_height(x->left),
		get_height(x->right)) + 1;

	// Return new root  
	return x;
}

// An utility function to left  
// rotate subtree rooted with x.
Node* left_rotate(Node* x)
{
	Node* y = x->right;
	Node* T2 = y->left;

	// Perform rotation  
	y->left = x;
	x->right = T2;

	// Update heights  
	x->height = std::max(get_height(x->left),
		get_height(x->right)) + 1;
	y->height = std::max(get_height(y->left),
		get_height(y->right)) + 1;

	return y;
}

Node* BinarySearchTree::insert(Node* root, int val)
{
	if (root == nullptr)
		root = new Node(val);
	else if (val < root->val)
	{
		Node* lchild = insert(root->left, val);
		root->left = lchild;
		lchild->parent = root;
	}
	else
	{
		Node* rchild = insert(root->right, val);
		root->right = rchild;
		rchild->parent = root;
	}

	// Update height of this ancestor node.
	root->height = 1 + std::max(get_height(root->left),
		get_height(root->right));

	// Get the balance factor of this ancestor node
	// to check whether this node became unbalanced.
	const int balance_factor = root == nullptr ? 0 :
		get_height(root->left) - get_height(root->right);

	// If this node becomes unbalanced, then  
	// there are 4 cases:

	// Left Left Case. 
	if (balance_factor > 1 && val < root->left->val)
		return right_rotate(root);

	// Right Right Case. 
	if (balance_factor < -1 && val > root->right->val)
		return left_rotate(root);

	// Left Right Case.
	if (balance_factor > 1 && val > root->left->val)
	{
		root->left = left_rotate(root->left);
		return right_rotate(root);
	}

	// Right Left Case.
	if (balance_factor < -1 && val < root->right->val)
	{
		root->right = right_rotate(root->right);
		return left_rotate(root);
	}

	// If there is no need to rotate.
	return root;
}

Node* BinarySearchTree::search(int key, Node* root)
{
	if (root == nullptr || key == root->val)
		return root;

	if (key < root->val)
		search(key, root->left);
	else
		search(key, root->right);
}

Node* BinarySearchTree::iterative_search(int key, Node* root)
{
	while (root != nullptr && key != root->val)
	{
		if (key < root->val)
			root = root->left;
		else
			root = root->right;
	}
	return root;
}

Node* BinarySearchTree::successor(Node* root)
{
	if (root->right != nullptr)
		return min(root->right);

	Node* temp = root->parent;
	while (temp != nullptr && root == temp->right)
	{
		root = temp;
		temp = temp->parent;
	}
	return temp;
}

Node* BinarySearchTree::predecessor(Node* root)
{
	if (root->left != nullptr)
		return min(root->left);

	Node* temp = root->parent;
	while (temp != nullptr && root == temp->left)
	{
		root = temp;
		temp = temp->parent;
	}
	return temp;
}

Node* BinarySearchTree::max(Node* root)
{
	while (root->right != nullptr)
		root = root->right;
	return root;
}

Node* BinarySearchTree::min(Node* root)
{
	while (root->left != nullptr)
		root = root->left;
	return root;
}

void BinarySearchTree::inorder(Node* root)
{
	if (root == nullptr)
		return;

	inorder(root->left);
	std::cout << root->val << " ";
	inorder(root->right);
}

Node* BinarySearchTree::remove(int val, Node* root)
{
	Node* temp;

	if (root == nullptr)
		return nullptr;
	else if (val < root->val)
		root->left = remove(val, root->left);
	else if (val > root->val)
		root->right = remove(val, root->right);
	else if (root->left && root->right)
	{
		temp = min(root->right);
		root->val = temp->val;
		root->right = remove(root->val, root->right);
	}
	else
	{
		temp = root;
		if (root->left == nullptr)
			root = root->right;
		else if (root->right == nullptr)
			root = root->left;
		delete temp;
	}

	return root;
}

void BinarySearchTree::transplant(Node* root, Node* subtree1, Node* subtree2)
{
	// When subtree1 is the root.
	// Otherwise, u is either a left child
	// or a right child of its parent.
	if (subtree1->parent == nullptr)
		root = subtree2;
	else if (subtree1 == subtree1->parent->left)
		subtree1->parent->left = subtree2;
	else
		subtree1->parent->right = subtree2;

	if (subtree2 != nullptr)
		subtree2->parent = subtree1->parent;
}

void BinarySearchTree::remove(Node* root, Node* todelete)
{
	Node* suc;

	// If node todelete has no left child.
	if (todelete->left == nullptr)
		transplant(root, todelete, todelete->right);

		// If node todelete has a left child but no right child.
	else if (todelete->right == nullptr)
		transplant(root, todelete, todelete->left);

		// If node todelete has two children.
	else
	{
		// Finds the successor of todelete.
		suc = min(todelete->right);

		// If suc is not todelete's right child then
		// replace suc as a child of its parent by suc’s right child 
		// and turn todelete’s right child into suc’s right child, 
		// and then lines 10–12 replace todelete as a child of its
		// parent by suc and replace suc’s left child by todelete’s left child.
		if (suc->parent != todelete)
		{
			transplant(root, suc, suc->right);
			suc->right = todelete->right;
			suc->right->parent = suc;
		}

		// If successor is todelete's right child
		// then replace todelete as a child of its parent by suc
		// and replace suc's left child by todelete's left child.
		transplant(root, todelete, suc);
		suc->left = todelete->left;
		suc->left->parent = suc;
	}
}

void BinarySearchTree::destroy(Node* root)
{
	if (root == nullptr)
		return;

	destroy(root->left);
	destroy(root->right);
	delete root;
}

int BinarySearchTree::find_distance_preorder(Node* root, int key)
{
	// Base case.
	if (root == NULL)
		return -1;

	// Initialize distance.
	int dist = -1;

	if ((root->val == key) ||
		(dist = find_distance_preorder(root->left, key)) >= 0 ||
		(dist = find_distance_preorder(root->right, key)) >= 0)
		return dist + 1;

	return dist;
}

int BinarySearchTree::find_distance_postorder(Node* root, int key)
{
	// Base case.
	if (root == nullptr)
		return -1;

	// Initialize distance.
	int dist = -1;

	if ((dist = find_distance_postorder(root->left, key)) >= 0 ||
		(dist = find_distance_postorder(root->right, key)) >= 0 ||
		(root->val == key))
		return dist + 1;

	return dist;
}

void BinarySearchTree::search_preorder(Node* root, int key)
{
	// Base case.
	if (root == NULL)
		return;

	if (root->val == key)
	{
		temp = root;
		return;
	}

	search_preorder(root->left, key);
	search_preorder(root->right, key);
}

void BinarySearchTree::search_postorder(Node* root, int key)
{
	// Base case.
	if (root == NULL)
		return;

	search_preorder(root->left, key);
	search_preorder(root->right, key);

	if (root->val == key)
	{
		temp = root;
		return;
	}
}

BinarySearchTree::BinarySearchTree()
{
	root = nullptr;
	temp = nullptr;
}

BinarySearchTree::~BinarySearchTree()
{
	destroy(root);
	root = nullptr;
}

void BinarySearchTree::insert(int val)
{
	root = insert(root, val);
}

void BinarySearchTree::display()
{
	inorder(root);
	std::cout << std::endl;
}

Node* BinarySearchTree::search(int key)
{
	return search(key, root);
}

void BinarySearchTree::iterative_search(int key)
{
	iterative_search(key, root);
}

int BinarySearchTree::max()
{
	return max(root)->val;
}

int BinarySearchTree::min()
{
	return min(root)->val;
}

void BinarySearchTree::remove(int key)
{
	remove(key, root);
}

void BinarySearchTree::removeV2(int key)
{
	remove(root, search(key, root));
}

void BinarySearchTree::destroy()
{
	destroy(root);
	root = nullptr;
}

int BinarySearchTree::find_distance_preorder(int key)
{
	return find_distance_preorder(root, key);
}

int BinarySearchTree::find_distance_postorder(int key)
{
	return find_distance_postorder(root, key);
}

Node* BinarySearchTree::search_preorder(int key)
{
	search_preorder(root, key);
	Node* node = temp;
	temp = nullptr;
	return node;
}

Node* BinarySearchTree::search_postorder(int key)
{
	search_postorder(root, key);
	Node* node = temp;
	temp = nullptr;
	return node;
}
