author: Piotr Fatyga
login:  pfatyga
-==================================README==================================-

First run make to create the executable ./hwk3a
To run the executable you must specify the following command-line parameters in any order:

	-f [dir_list.txt] [file_list.txt]
	-s [disk size]
	-b [block size]

	* be sure to specify dir_list first and file_list second for the -f parameter 
	* make sure you make the disk_size (-s) AT LEAST 500000.

Example Usage:
./hwk3a -f "dir_list.txt" "file_list.txt" -s 500000 -b 4096
