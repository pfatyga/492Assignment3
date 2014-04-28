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

//append a File * to the end of this L_file linked list
void File::append(File *end) {
	File *temp = this;
	while(temp->next != NULL)
		temp = temp->next;
	temp->next = end;
}

//shorten L_file by a specified amount of blocks and free the disk space in L_disk
//returns true if this was also deleted in which case we must delete the reference to the File in File_node
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
	//assert(i <= blocks);
	return deletethis;
}

//returns the size of L_file linked list
unsigned int File::size() {
	unsigned int total = 1;
	File *temp = this;
	while ((temp = temp->next) != NULL)
		total++;
	return total;
}

//print L_file using cout
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
