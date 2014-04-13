# Author: Piotr Fatyga
# login: pfatyga
SRC = File/File.cpp File_node/File_node.cpp Disk_node/Disk_node.cpp Directory_node/Directory_node.cpp main.cpp
TMN = hwk3a
RM = rm -f

all:
	g++ -std=c++0x -Wall -g $(SRC) -o $(TMN)

clean:
	-$(RM) *.o
	-$(RM) *~
	-$(RM) \#*
	-$(RM) *.core

fclean: clean
	-$(RM) $(TMN)

re: fclean all
