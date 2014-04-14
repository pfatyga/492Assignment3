/*
 * Tree_node.cpp
 *
 *  Created on: Apr 13, 2014
 *      Author: peter
 */

#include "Tree_node.h"

Disk_node *Tree_node::disk_nodes;

std::string Tree_node::get_name() {
	return name;
}

std::string Tree_node::get_path() {
	return path;
}

bool Tree_node::is_directory() {
	return directory;
}

/*void Tree_node::BFS_print(Tree_node *root) {
	std::cout << root->get_path() << '\n';
	if(!root->is_directory())
		return;
	Directory_node *temp = dynamic_cast<Directory_node *>(root);
	for(auto it = temp->children.begin(); it != temp->children.end(); it++)
	{
		BFS_print(dynamic_cast<Directory_node *>((*it).second));
	}
}*/
