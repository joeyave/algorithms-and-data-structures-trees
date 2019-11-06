#pragma once
#include <iostream>
#include <iomanip>

struct Node
{
	int val;
	Node* left;
	Node* right;
	Node* parent;

	Node(int _val)
	{
		val = _val;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	}
};

class BinarySearchTree
{
private:
	Node* root;
	size_t pathlength;

	Node* insert(Node* root, int val)
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

		return root;
	}

	// Time complexity is O(h).
	Node* search(int key, Node* root)
	{
		if (root == nullptr || key == root->val)
			return root;

		if (key < root->val)
			search(key, root->left);
		else
			search(key, root->right);
	}

	// Time complexity is O(h).
	Node* iterative_search(int key, Node* root)
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

	// Time complexity is O(h).
	Node* successor(Node* root)
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

	// Time complexity is O(h).
	Node* predecessor(Node* root)
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

	// Time complexity is O(h).
	Node* max(Node* root)
	{
		while (root->right != nullptr)
			root = root->right;
		return root;
	}

	// Time complexity is O(h).
	Node* min(Node* root)
	{
		while (root->left != nullptr)
			root = root->left;
		return root;
	}

	// Tree traversals.
	//Inorder traversal (left -> root -> right).
	void inorder(Node* root)
	{
		if (root == nullptr)
			return;

		inorder(root->left);
		std::cout << root->val << " ";
		inorder(root->right);
	}

	Node* remove(int val, Node* root) {
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

	// UTILITY FUNCTIONS.
	void transplant(Node* root, Node* subtree1, Node* subtree2)
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

	// Runs in O(h) time.
	void remove(Node* root, Node* todelete)
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

	void destroy(Node* root)
	{
		if (root == nullptr)
			return;
		else
		{
			destroy(root->left);
			destroy(root->right);
			delete root;
		}
		return;
	}

	void preorder(Node* root, Node* node, size_t pathlen = 0)
	{
		if (root == nullptr)
			return;

		pathlen++;
		if (root == node)
		{
			pathlength = pathlen;
			return;
		}

		preorder(root->left, node, pathlen);
		preorder(root->right, node, pathlen);
	}

	void postorder(Node* root, Node* node)
	{
		// TODO
	}

public:
	BinarySearchTree()
	{
		root = nullptr;
		pathlength = 0;
	}

	~BinarySearchTree()
	{
		destroy(root);
		root = nullptr;
	}

	void insert(int val)
	{
		root = insert(root, val);
	}

	void display()
	{
		inorder(root);
		std::cout << std::endl;
	}

	void search(int key)
	{
		search(key, root);
	}

	// Search using while loop. On most computers works faster.
	void iterative_search(int key)
	{
		iterative_search(key, root);
	}

	size_t GetPathLength(int key)
	{
		preorder(root, search(key, root));
		size_t temp = pathlength;
		pathlength = 0;
		return temp;
	}

	size_t GetPostorderPathLength(int key)
	{
		// TODO
	}

int max()
{
	return max(root)->val;
}

int min()
{
	return min(root)->val;
}

void remove(int key)
{
	remove(key, root);
	std::cout << "Removed successfully!\n";
}

void removeV2(int key)
{
	Node* todel = search(key, root);
	remove(root, todel);
}
	};

