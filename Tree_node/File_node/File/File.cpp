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

unsigned int File::size() {
	unsigned int total = 1;
	File *temp = this;
	while ((temp = temp->next) != NULL)
		total++;
	return total;
}

std::ostream &operator<<(std::ostream &os, File const &node) {
	File *temp = node.next;
	os << &node << ":[" << node.block_address << "]";
	while (temp != NULL) {
		os << '\t' << temp << ":[" << temp->block_address << "]";
		temp = temp->next;
	};
	return os;
}
