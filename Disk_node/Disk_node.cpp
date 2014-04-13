/*
 * Disk_node.cpp
 *
 *  Created on: Apr 13, 2014
 *      Author: peter
 */

#include "Disk_node.h"

Disk_node::Disk_node(unsigned int block_ID_start, unsigned int block_ID_end) {
	this->block_ID_start = block_ID_start;
	this->block_ID_end = block_ID_end;
	update_size();
}

Disk_node::~Disk_node() {
	// TODO Auto-generated destructor stub
}

void Disk_node::split(unsigned int next_block_ID_start) {
	next = new Disk_node(next_block_ID_start, this->block_ID_end);
	block_ID_end = next_block_ID_start-1;
	update_size();
	assert(block_ID_start <= block_ID_end);
}

void Disk_node::update_size() {
	block_ID_size = block_ID_end - block_ID_start + 1;	//block 3 - 5 is 3 blocks: 3, 4, 5 but 5 - 3 = 2
}
