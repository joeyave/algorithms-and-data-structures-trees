#include <utility>

typedef int KeyType;

struct Node
{
	int priority;
	KeyType key;

	Node* left;
	Node* right;

	explicit Node(const KeyType k)
	{
		priority = rand();
		key = k;
		left = right = nullptr;
	}
};

class Treap
{
public:
	typedef std::pair<Node*, Node*> NodePair;

	NodePair split(Node* root, const KeyType key)
	{
		if (root == nullptr)
			return NodePair(nullptr, nullptr);

		if (root->key < key)
		{
			NodePair splited_node = split(root->right, key);
			root->right = splited_node.first;
			return NodePair(root, splited_node.second);
		}
		NodePair splited_node = split(root->left, key);
		root->left = splited_node.second;
		return NodePair(splited_node.first, root);
	}

	Node* insert(Node* root, Node* node)
	{
		if (root == nullptr)
			return node;

		if (root->priority < node->priority)
		{
			const NodePair splited_node = split(root, node->key);
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

	void insert(const KeyType value)
	{
		root = insert(root, new Node(value));
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

	Node* remove(Node* root, const KeyType key)
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

	void remove(const KeyType key)
	{
		remove(root, key);
	}

private:
	Node* root = nullptr;
};

int main()
{
	Treap treap;
	treap.insert(15);
	treap.insert(1);
	treap.insert(11);
	treap.insert(16);
}
