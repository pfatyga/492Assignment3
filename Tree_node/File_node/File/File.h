/*
 * File.h
 *
 *  Created on: Apr 13, 2014
 *      Author: Piotr Fatyga
 *      Login:	pfatyga
 *      Description: File class which is also used as linked list
 */

#ifndef FILE_H_
#define FILE_H_

#include "../../../main.h"
#include "../../../Disk_node/Disk_node.h"

/*
 * Each node in Lfile represents a file block.
 * It contains:
 * 	(1) the starting physical address  of the block (not the block ID), and
 * 	(2)  a pointer to the next file block.
 * 	The starting physical address of the block of ID k can be calculated as
 * 	k * block_size,
 * 	where block_size is specified by the parameter -b.
 */

class File {

public:
	unsigned int block_address;
	File *next;	//linked list
	File(unsigned int block_address);
	virtual ~File();
	void append(File *end);
	unsigned int size();

	friend std::ostream &operator<<(std::ostream &os, File const &node);
};

#endif /* FILE_H_ */
