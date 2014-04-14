/*
 * File_node.h
 *
 *  Created on: Apr 13, 2014
 *      Author: Piotr Fatyga
 *      Login: 	pfatyga
 */

#ifndef FILE_NODE_H_
#define FILE_NODE_H_

#include "../../main.h"
#include "../Tree_node.h"
#include "File/File.h"

class File_node: public Tree_node {
	unsigned int size;
	std::string timestamp;
	File *file;
public:
	File_node(std::string file_name, std::string file_path, unsigned int file_size);
	virtual ~File_node();
	bool allocate_disk_space();
	File *get_file();
	void update_timestamp();
};

#endif /* FILE_NODE_H_ */
