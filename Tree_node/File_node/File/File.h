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

#include "main.h"

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
	unsigned int block_address;

	File *next;	//linked list
public:
	File(unsigned int block_address);
	virtual ~File();
};

#endif /* FILE_H_ */
