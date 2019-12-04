#include "RB-tree.h"
#include <iostream>

int main()
{
	RBTree rb_tree;

	rb_tree.insert(15);
	rb_tree.insert(11);
	rb_tree.insert(154);
	rb_tree.insert(1512);
	rb_tree.insert(152);
	rb_tree.insert(1562);
	rb_tree.insert(1521);
	rb_tree.preorder();

	
	rb_tree.remove(15);
	rb_tree.remove(1562);
	rb_tree.remove(1521);

	
	rb_tree.preorder();

	return 0;
}