#include "RB-tree.h"
 
int main()
{
	RBTree rb_tree;

	rb_tree.insert(10);
	rb_tree.insert(30);
	rb_tree.insert(20);
	rb_tree.insert(5);
	rb_tree.insert(7);
	rb_tree.remove(20);
	
	rb_tree.preorder();

	
	rb_tree.remove(15);
	rb_tree.remove(1562);
	rb_tree.remove(1521);

	
	rb_tree.preorder();

	return 0;
}