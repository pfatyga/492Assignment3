# Author: Piotr Fatyga
# login: pfatyga
SRC = File.cpp File_node.cpp main.cpp
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
