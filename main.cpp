//============================================================================
// Name        : 492Assignment3.cpp
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
	Directory_node *G_root = new Directory_node("/");	//root directory is "/"
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
	cout << "dir_list: " << dir_list << ", file_list: " << file_list << ", disk_size: " << disk_size << ", block_size: " << block_size << '\n';

	number_of_blocks = disk_size / block_size;
	L_disk = new Disk_node(0, number_of_blocks-1);

	Tree_node::disk_nodes = L_disk;

	dir_list.close();
	file_list.close();

	return 0;
}
