#include <stdio.h>		/* Header file for printf */
#include <sys/types.h>         /* Header file for system call  open */
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>		/* Header file for system calls read, write y close */

#define BUFFER_SIZE 1024  	/*We define the buffer size*/


int main(int argc, char *argv[]){

    	/*If the number of arguments is different from two (argv[0] -> program, argv[1] -> file to be shown) we print an error and 	return -1*/
	if(argc != 2){
		// If argc < 2, then the problem was not having enough arguments, printing this as the error
		if (argc < 2) printf("Error: Not enough arguments.\n");
		// If not, then the problem was having more than 2 arguments, printing this as the error
        	else printf("Error: Too many arguments.\n");
        	return -1;
    	}
    	
    	int fd_input, bytes_read, bytes_written; //Declare input file descriptor and 2 var. to store bytes read and written
    	char buffer[BUFFER_SIZE]; //Declare the buffer with a size of 1024 bytes
    	
	//If open() returns -1, then the file does not exist, printing an error and returning -1
    	if ((fd_input = open(argv[1], O_RDONLY, 0444)) <0){
        	perror("Error: File does not exit.\n");
        	return -1;
    	}
    	
	//Check that the number of bytes read from the input file is greater than 0 (something was read) 
    	while ((bytes_read=read(fd_input, buffer, BUFFER_SIZE)) > 0){
		/*Check if the number of bytes written (printed on screen) is less than the number of bytes read. If so, print 			error, close the open file and return -1*/
        	if ((bytes_written=write(STDOUT_FILENO, buffer, bytes_read)) < bytes_read){
        		perror("Error: Writing operation was not perfomed correctly.\n");
            		if (close(fd_input) < 0){
            			//If close operation returns -1, then an error when closing open file occured, printing an error
            			perror("Error: Open file could not be closed.\n");
            		}
            		return -1;
        	}
    	}
    		
	/*If the bytes read are -1, it implies that an error ocurred while reading the input file, therefore we return -1 and 		report the error after closing the open file*/
    	if (bytes_read<0){
        	perror("Error: Reading operation was not performed correctly.\n");
        	if (close(fd_input) < 0){
        		//If close operation returns -1, then an error when closing open file occured, printing an error
            		perror("Error: Open file could not be closed.\n");
            	}
        	return -1;
    	}
    	
	//No error ocurred, we close the open input file and return 0
	if (close(fd_input)  < 0){	
		//If close operation returns -1, then an error when closing open file occured, printing an error and returning -1
		perror("Error: Open file could not be closed.\n");
		return -1;
	}
	return 0;
}

