#include <utility>

struct Node
{
	int key;
	int priority;

	Node* left;
	Node* right;

	explicit Node(const int k)
	{
		key = k;
		priority = rand();
		left = right = nullptr;
	}

	explicit Node(const int k, const int prior)
	{
		key = k;
		priority = prior;
		left = right = nullptr;
	}
};

class Treap
{
public:
	typedef std::pair<Node*, Node*> node_pair;

	node_pair split(Node* root, const int key) const
	{
		if (root == nullptr)
			return node_pair(nullptr, nullptr);

		if (root->key < key)
		{
			node_pair splited_node = split(root->right, key);
			root->right = splited_node.first;
			return node_pair(root, splited_node.second);
		}
		node_pair splited_node = split(root->left, key);
		root->left = splited_node.second;
		return node_pair(splited_node.first, root);
	}

	node_pair split(const int key) const
	{
		return split(root, key);
	}

	Node* insert(Node* root, Node* node) const
	{
		if (root == nullptr)
			return node;

		if (root->priority < node->priority)
		{
			const node_pair splited_node = split(root, node->key);
			node->left = splited_node.first;
			node->right = splited_node.second;
			return node;
		}

		if (root->key < node->key)
		{
			root->right = insert(root->right, node);
		}
		else
		{
			root->left = insert(root->left, node);
		}
		return root;
	}

	void insert(const int value)
	{
		root = insert(root, new Node(value));
	}

	void insert(const int value, const int priority)
	{
		root = insert(root, new Node(value, priority));
	}
	
	Node* merge(Node* a, Node* b)
	{
		if (a == nullptr) return b;
		if (b == nullptr) return a;

		if (a->priority > b->priority)
		{
			a->right = merge(a->right, b);
			return a;
		}
		b->left = merge(a, b->left);
		return b;
	}

	Node* remove(Node* root, const int key)
	{
		if (root == nullptr) return nullptr;

		if (root->key == key)
		{
			Node* node = merge(root->left, root->right);
			delete root;
			return node;
		}

		if (root->key < key)
		{
			root->right = remove(root->right, key);
		}
		else
		{
			root->left = remove(root->left, key);
		}
		return root;
	}

	void remove(const int key)
	{
		remove(root, key);
	}

private:
	Node* root = nullptr;
};

int main()
{
	Treap treap;
	treap.insert(7, 10);
	treap.insert(4, 6);
	treap.insert(13, 8);
	treap.insert(2, 4);
	treap.insert(5, 11);
}