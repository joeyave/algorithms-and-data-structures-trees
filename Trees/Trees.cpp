#include <iostream>

struct TreapNode
{
	TreapNode(const int k, const int p)
	{
		key = k;
		priority = p;
		left = right = nullptr;
	}

	int key, priority;
	TreapNode* left;
	TreapNode* right;
};

class Treap
{
public:
	Treap()
	{
		root_ = nullptr;
	}

	TreapNode* right_rotate(TreapNode* y)
	{
		TreapNode* x = y->left;
		TreapNode* T2 = x->right;
		x->right = y;
		y->left = T2;
		return x;
	}

	TreapNode* left_rotate(TreapNode* x)
	{
		TreapNode* y = x->right;
		TreapNode* T2 = y->left;
		y->left = x;
		x->right = T2;
		return y;
	}

	TreapNode* insert(TreapNode* root, const int key, const int prior)
	{
		if (!root)
		{
			return new TreapNode(key, prior);
		}

		if (key <= root->key)
		{
			root->left = insert(root->left, key, prior);
			if (root->left->priority > root->priority)
			{
				root = right_rotate(root);
			}
		}
		else
		{
			root->right = insert(root->right, key, prior);
			if (root->right->priority > root->priority)
			{
				root = left_rotate(root);
			}
		}
		return root;
	}

	void insert(const int key, const int prior)
	{
		root_ = insert(root_, key, prior);
	}

	TreapNode* remove(TreapNode* root, const int key)
	{
		if (root == nullptr)
			return root;
		if (key < root->key)
		{
			root->left = remove(root->left, key);
		}
		else if (key > root->key)
		{
			root->right = remove(root->right, key);
		}
		else if (root->left == nullptr)
		{
			TreapNode* temp = root->right;
			delete(root);
			root = temp;
		}
		else if (root->right == nullptr)
		{
			TreapNode* temp = root->left;
			delete(root);
			root = temp;
		}
		else if (root->left->priority < root->right->priority)
		{
			root = left_rotate(root);
			root->left = remove(root->left, key);
		}
		else
		{
			root = right_rotate(root);
			root->right = remove(root->right, key);
		}
		return root;
	}

	void remove(const int key)
	{
		remove(root_, key);
	}

	void display(TreapNode* root, const int level)
	{
		if (root)
		{
			display(root->left, level + 2);
			for (int i = 0; i < level; i++)
			{
				std::cout << "  ";
			}
			std::cout << root->key << " - " << root->priority;
			display(root->right, level + 2);
		}
	}

	void display(const int level)
	{
		display(root_, level);
	}
private:
	TreapNode* root_;
};


int main()
{
	Treap treap;
	treap.insert(15, 1);
	treap.insert(40, 4);
	treap.insert(30, 5);
	treap.insert(20, 6);
	treap.insert(50, 7);
	treap.insert(70, 2);
	treap.display(0);

	return 0;
}