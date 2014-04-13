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

