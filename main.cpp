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
using namespace std;

int main(int argc, char **argv) {
	unsigned int disk_size = 0;
	unsigned int block_size = 0;
	ifstream input_file;

	/* Your program must accept the following parameters at the command prompt:

		-f [input files storing information on directories and files]
		-s [disk size]
		-b [block size]
	 */
	if(argc != 7)
	{
		cout << "Usage: ";
		cout << argv[0];	//name of program is printed
		cout << " -f [F] -s [S] -b [B]\n";
		cout << "F: input files storing information on directories and files\n";
		cout << "S: disk size\n";
		cout << "B: block size\n";
		return 0;
	}

	//argv[1], argv[3], argv[5]
	for(int i = 1; i <= 5; i += 2)
	{
		if(strcmp(argv[i], "-f") == 0)
		{
			input_file.open(argv[i+1], std::ifstream::in);
			if(!input_file.is_open())
			{
				cout << "Input file could not be opened.\n";
				return 0;
			}
		}
		else if(strcmp(argv[i], "-s") == 0)
		{
			if(atoi(argv[i+1]) <= 0)
			{
				cout << "Disk size must be positive.\n";
				return 0;
			}
			disk_size = atoi(argv[i+1]);
		}
		else if(strcmp(argv[i], "-b") == 0)
		{
			if(atoi(argv[i+1]) <= 0)
			{
				cout << "Block size must be positive.\n";
				return 0;
			}
			block_size = atoi(argv[i+1]);
		}
		else
		{
			cout << "Bad input flag.\n";
			return 0;
		}
	}


	//check if all input was received
	if(input_file == "" || disk_size == 0 || block_size == 0)
	{
		cout << "Please provide all input.\n";
		return 0;
	}

	//DEBUGGING
	cout << "input_file: " << input_file << ", disk_size: " << disk_size << ", block_size: " << block_size << '\n';



	input_file.close();

	return 0;
}
