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
	std::map<std::string, Tree_node *> children;	//key: name of file/directory
public:
	Directory_node(std::string directory_name);
	Directory_node(std::string directory_name, std::string directory_path);
	virtual ~Directory_node();
	void create_directory(char *path);
	void create_file(char *path, unsigned int size);
	bool create_subdirectory(std::string name);
	static void BFS_print(Tree_node *root);
};

#endif /* DIRECTORY_NODE_H_ */
