#include "Disk_node.h"

int main()
{
	Disk_node *root = new Disk_node(0, 511);
	root->split(10);
	std::cout << *root << '\n';
	root->split(5);
	std::cout << *root << '\n';
	root->next->merge();
	std::cout << *root << '\n';
	delete root;

	root = new Disk_node(0, 511);
	root->split(10);
	std::cout << *root << '\n';
	root->split(5);
	std::cout << *root << '\n';
	root->in_use = true;
	root->next->merge();
	std::cout << *root << '\n';
	delete root;

	root = new Disk_node(0, 511);
	root->split(10);
	std::cout << *root << '\n';
	root->split(5);
	std::cout << *root << '\n';
	root->next->next->in_use = true;
	root->next->merge();
	std::cout << *root << '\n';
	delete root;

	root = new Disk_node(0, 511);
	root->split(100);
	std::cout << *root << '\n';
	root->split(50);
	std::cout << *root << '\n';
	root->split(40);
	std::cout << *root << '\n';
	root->split(30);
	std::cout << *root << '\n';
	root->merge();
	std::cout << *root << '\n';
	delete root;

	return 0;
}
