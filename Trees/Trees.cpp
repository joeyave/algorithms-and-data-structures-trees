#include <iostream>
#include "BinarySearchTree.h"

int main()
{
	BinarySearchTree bst;
	bst.insert(18);
	bst.insert(3);
	bst.insert(20);
	bst.insert(1);
	bst.insert(5);
	bst.insert(4);
	bst.insert(7);
	bst.insert(24);
	bst.insert(21);

	bst.display();

	// Lab 8.
	std::cout << "Search: " << bst.search(24) << std::endl;
	std::cout << "Search using preorder traversal: " << bst.search_preorder(24) << std::endl;
	std::cout << "Search using postorder traversal: " << bst.search_postorder(24) << std::endl;
	std::cout << "Preorder distance: " << bst.find_distance_preorder(24) << std::endl;
	std::cout << "Postorder distance: " << bst.find_distance_postorder(24) << std::endl;

	// Lab 9 - 10.
	std::cout << "Search: " << bst.search(24) << std::endl;
	bst.removeV2(24);
	std::cout << "Search: " << bst.search(24) << std::endl;
	bst.remove(3);
}