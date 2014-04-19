/*
 * Disk_node.h
 *
 *  Created on: Apr 13, 2014
 *      Author: Piotr Fatyga
 *      Login:	pfatyga
 *      Description: Disk Node object used in linked list for Disk blocks.
 *       			 Each node in Ldisk consists of:
 *       			 	(1) the set of block IDs (not the physical address of the blocks),
 *       				(2) the status ("free" or "used") of this set of blocks, and
 *       				(3) the pointer to the next node in Ldisk.
 */

#ifndef DISK_NODE_H_
#define DISK_NODE_H_

#include "../main.h"

class Disk_node {

public:

	unsigned int block_ID_start;
	unsigned int block_ID_end;
	unsigned int block_ID_size;
	bool in_use;
	Disk_node *next;
	Disk_node *prev;

	Disk_node(unsigned int block_ID_start, unsigned int block_ID_end);
	Disk_node(unsigned int block_ID_start, unsigned int block_ID_end, bool in_use, Disk_node *prev, Disk_node *next);
	virtual ~Disk_node();
	void update_size();
	Disk_node *split(unsigned int next_block_ID_start);	//splits this Disk_node into 2 nodes with the second one starting at next_block_id_start and this one ending at next_block_id_start-1
	void free(unsigned int block_ID);
	void merge();
	Disk_node *get_next_free_block();
	unsigned int size();

	static unsigned int block_size;
	static unsigned int disk_size;
	static unsigned int total_blocks;

	friend std::ostream &operator<<(std::ostream &os, Disk_node const &node);
};

#endif /* DISK_NODE_H_ */
