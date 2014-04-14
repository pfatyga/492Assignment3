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
