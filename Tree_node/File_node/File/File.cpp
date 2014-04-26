/*
 * File.cpp
 *
 *  Created on: Apr 13, 2014
 *      Author: peter
 */

#include "File.h"

File::File(unsigned int block_address) {
	this->block_address = block_address;
	next = NULL;
}

File::~File() {
	// TODO Auto-generated destructor stub
}

void File::append(File *end) {
	File *temp = this;
	while(temp->next != NULL)
		temp = temp->next;
	temp->next = end;
}

bool File::shorten(unsigned int blocks) {
	if(blocks == 0)
		return false;
	bool deletethis = false;
	File *before_begin = this;
	File *begin = this;
	File *end = this;
	//get the blocks-last item in the list (i.e. blocks = 5, get the 5th last item in the list)
	for(unsigned int i = 1; end->next != NULL; i++)
	{
		end = end->next;
		if(i >= blocks)
		{
			before_begin = begin;
			begin = begin->next;
		}
	}
	if(before_begin != begin)
		before_begin->next = NULL;
	unsigned int i = 0;
	while(begin != NULL)
	{
		if(begin == this)
			deletethis = true;
		File *temp = begin;
		begin = begin->next;
		Tree_node::disk_nodes->free(temp->block_address / Disk_node::block_size);
		delete temp;
		i++;
	}
	//std::cout << "Removed " << i << " blocks\n";
	//assert(i <= blocks);
	return deletethis;
}

unsigned int File::size() {
	unsigned int total = 1;
	File *temp = this;
	while ((temp = temp->next) != NULL)
		total++;
	return total;
}

std::ostream &operator<<(std::ostream &os, File const &node) {
	File *temp = node.next;
	os << "[" << node.block_address;
	while (temp != NULL) {
		os << ", " << temp->block_address;
		temp = temp->next;
	};
	os << "]";
	return os;
}

/*std::ostream &operator<<(std::ostream &os, File const &node) {
	File *temp = node.next;
	os << &node << ":[" << node.block_address << "]" << "->" << node.next;
	while (temp != NULL) {
		os << '\t' << temp << ":[" << temp->block_address << "]" << "->" << temp->next;
		temp = temp->next;
	};
	return os;
}*/
