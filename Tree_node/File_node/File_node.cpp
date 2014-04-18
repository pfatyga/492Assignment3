/*
 * File_node.cpp
 *
 *  Created on: Apr 13, 2014
 *      Author: Piotr Fatyga
 *      Login:	pfatyga
 */

#include "File_node.h"

File_node::File_node(std::string file_name, std::string file_path, unsigned int file_size) {
	name = file_name;
	path = file_path;
	size = file_size;
	directory = false;
	update_timestamp();
}

File_node::~File_node() {
	//TODO: Remove from Linked list
	delete file;
}

File *File_node::get_file() {
	return file;
}

bool File_node::allocate_disk_space() {
	Disk_node *available = Tree_node::disk_nodes->get_next_free_block();
	//std::cout << "size: " << size << "block_size: " << Disk_node::block_size << '\n';
	unsigned int number_blocks = (size / Disk_node::block_size) + 1;	//integer division: 5 / 2 = 2 but we need 3 blocks
	//std::cout << "Allocating " << number_blocks << " for " << path << '\n';
	//std::cout << number_blocks << '\n';
	File *f = NULL;
	while(number_blocks > 0 && available != NULL)
	{
		//std::cout << *available << '\n';
		//std::cout << number_blocks << '\n';
		available->split(number_blocks);
		available->in_use = true;
		//std::cout << *(Tree_node::disk_nodes) << '\n';
		for(unsigned int i = available->block_ID_start; i <= available->block_ID_end; i++)
		{
			if(f == NULL)
				f = new File(i * Disk_node::block_size);
			else
				f->append(new File(i * Disk_node::block_size));
		}
		available->merge();
		//std::cout << *(Tree_node::disk_nodes) << '\n';
		//std::cout << number_blocks << " " << available->block_ID_size << '\n';
		assert(available->block_ID_size <= number_blocks);
		number_blocks -= available->block_ID_size;
		available = Tree_node::disk_nodes->get_next_free_block();
	}
	if(number_blocks > 0)	//not enough space
		return false;
	this->file = f;
	return true;
}

void File_node::update_timestamp() {

}

