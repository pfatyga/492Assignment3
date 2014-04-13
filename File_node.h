/*
 * File_node.h
 *
 *  Created on: Apr 13, 2014
 *      Author: Piotr Fatyga
 *      Login: 	pfatyga
 */

#ifndef FILE_NODE_H_
#define FILE_NODE_H_

#include <string>
#include "Tree_node.h"
#include "File.h"

class File_node: public Tree_node {
	File *file;
public:
	File_node(std::string file_name, unsigned int file_size);
	virtual ~File_node();
	File *get_file();
};

#endif /* FILE_NODE_H_ */
