/*
 * Directory_node.h
 *
 *  Created on: Apr 13, 2014
 *      Author: peter
 */

#ifndef DIRECTORY_NODE_H_
#define DIRECTORY_NODE_H_

#include "../../main.h"
#include "../Tree_node.h"
#include "../File_node/File_node.h"
#include <queue>

class Directory_node: public Tree_node {

public:
	Directory_node *parent_directory;
	std::map<std::string, Tree_node *> children;	//key: name of file/directory

	Directory_node(std::string directory_name);
	Directory_node(std::string directory_name, std::string directory_path, Directory_node *parent_directory);
	virtual ~Directory_node();
	Directory_node *get_directory(std::string name);
	File_node *get_file(std::string name);
	void create_directory(char *path);
	bool create_file(char *path, unsigned int size);
	bool create_file(std::string name, unsigned int size);
	bool create_subdirectory(std::string name);
	bool delete_child(std::string name);	//delete a file or directory
	static void dir_print(Directory_node *root);
	static void ls_print(Directory_node *root);
};

#endif /* DIRECTORY_NODE_H_ */
