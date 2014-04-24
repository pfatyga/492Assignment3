# Author: Piotr Fatyga
# login: pfatyga
SRC = Tree_node/Tree_node.cpp Tree_node/File_node/File/File.cpp Tree_node/File_node/File_node.cpp Disk_node/Disk_node.cpp Tree_node/Directory_node/Directory_node.cpp main.cpp
TMN = hwk3a
RM = rm -f

all:
	g++ -std=c++0x -Wall -pg -g $(SRC) -o $(TMN)

clean:
	-$(RM) *.o
	-$(RM) *~
	-$(RM) \#*
	-$(RM) *.core

fclean: clean
	-$(RM) $(TMN)

re: fclean all
