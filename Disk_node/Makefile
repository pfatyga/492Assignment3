# Author: Piotr Fatyga
# login: pfatyga
SRC = Disk_node.cpp Disk_node_test.cpp
TMN = disk_node_test
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
