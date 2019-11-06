#include <iostream>
#include "BinarySearchTree.h"

int main()
{
	
	BinarySearchTree bst;
	bst.insert(18);
	bst.insert(15);
	bst.insert(1);
	bst.insert(10);
	bst.insert(30);
	bst.insert(40);
	bst.insert(41);
	bst.insert(42);
	bst.insert(50);
	bst.insert(45);
	bst.insert(100);

	bst.display();
	std::cout << bst.search(10) << std::endl;
	std::cout << bst.search_preorder(10) << std::endl;
	std::cout << bst.search_postorder(10) << std::endl;
	bst.removeV2(10);
}