//============================================================================
// Name        : main.cpp
// Author      : Piotr Fatyga
// Login	   : pfatyga
// Version     :
// Copyright   : 
// Description : CS 492 Assignment 3
//============================================================================

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include "main.h"
#include "Tree_node/Directory_node/Directory_node.h"
#include "Tree_node/Tree_node.h"
using namespace std;

int main(int argc, char **argv) {
	unsigned int disk_size = 0;
	unsigned int block_size = 0;
	unsigned int number_of_blocks = 0;
	string command;
	Directory_node *G_root = new Directory_node(".");	//root directory is "/"
	Directory_node *current_directory = G_root;
	Disk_node *L_disk;
	ifstream dir_list;
	ifstream file_list;

	/* Your program must accept the following parameters at the command prompt:

		-f [input files storing information on directories and files]
		-s [disk size]
		-b [block size]
	 */
	if(argc != 8)
	{
		cout << "Usage: ";
		cout << argv[0];	//name of program is printed
		cout << " -f [F1] [F2] -s [S] -b [B]\n";
		cout << "F1: Directory list input\n";
		cout << "F2: File list input\n";
		cout << "S: disk size\n";
		cout << "B: block size\n";
		return 0;
	}

	for(int i = 1; i < 8;)
	{
		if(strcmp(argv[i], "-f") == 0)
		{
			dir_list.open(argv[i+1], std::ifstream::in);
			if(!dir_list.is_open())
			{
				cout << "Dir list input [F1] could not be opened.\n";
				return 0;
			}
			file_list.open(argv[i+2], std::ifstream::in);
			if(!file_list.is_open())
			{
				cout << "File list input [F2] could not be opened.\n";
				return 0;
			}
			i+=3;	//2 parameters
		}
		else if(strcmp(argv[i], "-s") == 0)
		{
			if(atoi(argv[i+1]) <= 0)
			{
				cout << "Disk size must be positive.\n";
				return 0;
			}
			disk_size = atoi(argv[i+1]);
			i += 2; //1 parameter
		}
		else if(strcmp(argv[i], "-b") == 0)
		{
			if(atoi(argv[i+1]) <= 0)
			{
				cout << "Block size must be positive.\n";
				return 0;
			}
			block_size = atoi(argv[i+1]);
			i += 2;	//1 parameter
		}
		else
		{
			cout << "Bad input flag.\n";
			return 0;
		}
	}


	//check if all input was received
	if(!dir_list.is_open() || !file_list.is_open() || disk_size == 0 || block_size == 0)
	{
		cout << "Please provide all input.\n";
		return 0;
	}

	//DEBUGGING
	//cout << "dir_list: " << dir_list << ", file_list: " << file_list << ", disk_size: " << disk_size << ", block_size: " << block_size << '\n';

	number_of_blocks = disk_size / block_size;

	Disk_node::total_blocks = number_of_blocks;
	Disk_node::disk_size = disk_size;
	Disk_node::block_size = block_size;

	L_disk = new Disk_node(0, number_of_blocks-1);

	Tree_node::disk_nodes = L_disk;

	while(!dir_list.eof() && !dir_list.fail())
	{
		char path[1000];
		dir_list >> path;
		G_root->create_directory(path);
	}

	dir_list.close();

	while(!file_list.eof() && !file_list.fail())
	{
		string ignore;
		unsigned int size;
		string month;
		string day;
		string time;
		char path[1000];
		file_list >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore;
		file_list >> size >> month >> day >> time;
		//cout << size << '\n';
		file_list >> path;
		//cout << path << '\n';
		if(strcmp(path, ".") == 0)	//weird issue where it reads . as the path even though it's not in there
			continue;
		if(!G_root->create_file(path, size))
		{
			cout << "Failed to allocate disk space.\n";
			file_list.close();	//TODO: just continue, also create_file should print
			return 0;
		}
	}

	file_list.close();

	//Directory_node::BFS_print(G_root);
	cout << *L_disk << '\n';
	cout << current_directory->get_path() << "> ";
	cin >> command;
	while(command != "exit")
	{
		if(command == "cd")
		{
			string directory;
			cin >> directory;
			Directory_node *temp = current_directory->get_directory(directory);
			if(temp != NULL)
				current_directory = temp;
		}
		else if(command == "ls")
		{
			Directory_node::ls_print(current_directory);
		}
		else if(command == "mkdir")
		{
			string directory;
			cin >> directory;
			if(!(current_directory->create_subdirectory(directory)))	//return false if directory/file already exists
			{
				std::cout << "Cannot create directory \'" << directory << "\': File exists\n";
			}
		}
		else if(command == "create")
		{
			string file_name;
			cin >> file_name;
			if(!current_directory->create_file(file_name, 0))
			{
				std::cout << "Cannot create file \'" << file_name << "\': File exists\n";
			}
		}
		else if(command == "append")
		{
			string file_name;
			unsigned int bytes_to_append;
			cin >> file_name;
			cin >> bytes_to_append;
			File_node *file = current_directory->get_file(file_name);
			if(file != NULL)
			{
				file->append(bytes_to_append);
			}
			cout << *(file->get_file()) << '\n';
		}
		else if(command == "remove")
		{

		}
		else if(command == "delete")
		{
			string name;
			cin >> name;
			current_directory->delete_child(name);
			cout << *L_disk << '\n';
		}
		else if(command == "dir")
		{
			Directory_node::dir_print(current_directory);
		}
		else if(command == "prfiles")
		{

		}
		else if(command == "prdisk")
		{

		}
		cout << current_directory->get_path() << "> ";
		cin >> command;
	}

	return 0;
}
