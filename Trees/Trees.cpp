#include "RB-tree.h"
#include <iostream>

int main()
{
	RBTree rbTree;

	rbTree.insertValue(15);

	rbTree.preorder();

	return 0;
}