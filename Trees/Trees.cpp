#include "RB-tree.h"
#include <iostream>

int main()
{
	RBTree rbTree;

	rbTree.insert(15);

	rbTree.preorder();

	return 0;
}