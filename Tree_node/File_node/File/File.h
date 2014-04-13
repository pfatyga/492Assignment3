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

#include <string>

class File {
	unsigned int block_address;

	File *next;	//linked list
public:
	File(unsigned int block_address);
	virtual ~File();
};

#endif /* FILE_H_ */
