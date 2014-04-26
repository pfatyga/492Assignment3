#include "Disk_node.h"
#include <cassert>

int main()
{
	Disk_node *root = new Disk_node(0, 129);
	root->in_use = true;
	root->next = new Disk_node(130, 31249);
	root->next->split(4131);
	root->next->in_use = true;
	root->next->merge();
	std::cout << *root << '\n';
	delete root;

	root = new Disk_node(0, 6);
	root->split(4);
	std::cout << *root << '\n';
	root->next->split(1);
	assert(root->next->block_ID_size == 1);
	std::cout << *root << '\n';
	root->in_use = true;
	root->next->in_use = true;
	root->next->next->in_use = true;
	root->next->merge();
	std::cout << *root << '\n';
	delete root;

	root = new Disk_node(0, 511);
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

	root = new Disk_node(0, 511);
	root->split(100);
	std::cout << *root << '\n';
	root->split(50);
	std::cout << *root << '\n';
	root->split(40);
	std::cout << *root << '\n';
	root->split(30);
	std::cout << *root << '\n';
	root->next->in_use = true;
	root->next->next->next->in_use = true;
	root->merge();
	std::cout << *root << '\n';
	root->next->merge();
	std::cout << *root << '\n';
	root->next->next->merge();
	std::cout << *root << '\n';
	root->next->next->next->merge();
	std::cout << *root << '\n';
	root->next->next->next->next->merge();
	std::cout << *root << '\n';
	root->next->next->next->next->in_use = true;
	root->next->next->next->merge();
	std::cout << *root << '\n';
	root->get_next_free_block()->in_use = true;
	std::cout << *(root->get_next_free_block()) << '\n';
	root->get_next_free_block()->in_use = true;
	//std::cout << *root << '\n';
	std::cout << root->get_next_free_block() << '\n';
	delete root;

	return 0;
}
