/*
 * File.h
 *
 *  Created on: Apr 13, 2014
 *      Author: peter
 */

#ifndef FILE_H_
#define FILE_H_

#include <string>

class File {
	std::string name;
	unsigned int size;
	std::string timestamp;
public:
	File(std::string file_name, unsigned int file_size);
	virtual ~File();
	void update_timestamp();
};

#endif /* FILE_H_ */
