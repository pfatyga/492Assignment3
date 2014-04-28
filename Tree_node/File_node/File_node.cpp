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
	file = NULL;
	directory = false;
	update_timestamp();
}

File_node::~File_node() {
	File *temp = file;
	while(temp != NULL)
	{
		Tree_node::disk_nodes->free(temp->block_address / Disk_node::block_size);
		File *prev = temp;
		temp = temp->next;
		delete prev;
	}
}

File *File_node::get_file() {
	return file;
}

//gets free blocks for L_disk and sets them to used and creates L_file
File *File_node::allocate_disk_blocks(unsigned int number_blocks)
{
	if(number_blocks == 0)
		return NULL;
	Disk_node *available = Tree_node::disk_nodes->get_next_free_block();
	File *f = NULL;
	while(number_blocks > 0 && available != NULL)
	{
		available->split(number_blocks);
		available->in_use = true;
		for(unsigned int i = available->block_ID_start; i <= available->block_ID_end; i++)
		{
			if(f == NULL)
				f = new File(i * Disk_node::block_size);
			else
				f->append(new File(i * Disk_node::block_size));
		}
		available->merge();
		//assert(available->block_ID_size <= number_blocks);	//make sure number_blocks doesn't overflow
		number_blocks -= available->block_ID_size;
		available = Tree_node::disk_nodes->get_next_free_block();
	}
	if(number_blocks > 0)
	{
		std::cout << "Out of space.\n";
		//assert(Tree_node::disk_nodes->get_next_free_block() == NULL);
	}
	return f;
}

//append a file by a size (in bytes)
bool File_node::append(unsigned int size) {
	if(size == 0)
		return true;
	this->size += size;
	unsigned int number_blocks = ceil((double)(this->size) / Disk_node::block_size);
	unsigned int blocks_needed = number_blocks - (file != NULL ? file->size() : 0);
	File *f = allocate_disk_blocks(blocks_needed);
	if(file != NULL)
		file->append(f);
	else
		file = f;

	update_timestamp();

	if(file->size() == number_blocks)
		return true;
	else
	{
		this->size = file->size() * Disk_node::block_size;
		return false;
	}
}

//shortens a file by size (in bytes)
bool File_node::shorten(unsigned int size) {
	if(file == NULL)
		return true;
	if(size == 0)
		return true;
	if(size > this->size)
		this->size = 0;
	else
		this->size -= size;
	unsigned int blocks_to_remove = file->size() - ceil((double)(this->size) / Disk_node::block_size);
	if(file->shorten(blocks_to_remove))
		file = NULL;
	return true;
}

//calculates amount of blocks needed and allocates them in L_disk and L_file
bool File_node::allocate_disk_space() {
	if(size == 0)
		return true;
	unsigned int number_blocks = ceil((double)size / Disk_node::block_size);
	File *f = allocate_disk_blocks(number_blocks);
	this->file = f;
	if((this->file != NULL ? this->file->size() : 0) == ceil((double)size / Disk_node::block_size))
		return true;
	else
		return false;
}

//calculates the amount of fragmentation in the file
unsigned int File_node::fragmentation() {
	if(this->file != NULL)
	{
		return (this->file->size() * Disk_node::block_size) - this->size;
	}
	else
	{
		return 0;
	}
}

//print File_node using cout
std::ostream &operator<<(std::ostream &os, File_node const &node) {
	os << node.path << ": " << node.size << " bytes\t" << node.timestamp;
	if(node.file != NULL)
		os << *(node.file);
	else
		os << "No blocks allocated";
	return os;
}
