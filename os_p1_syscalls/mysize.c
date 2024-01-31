#include <stdio.h>	/*Header file for system call printf*/
#include <sys/types.h>	/*Header file for system call fstat*/
#include <sys/stat.h>
#include <fcntl.h>	/*Header file for system call fcntl*/
#include <dirent.h> 	/*Header file for system call opendir, closedir,readdir...*/
#include <unistd.h>

int main(int argc, char *argv[]){

	//If there are 1 or more given arguments, then print error and return -1
	if (argc > 1) {
		perror("Error: Too many arguments.\n");
		return -1;
	}
	
	DIR *current_dir; //Declare a DIR data type to store the address of the curret path
	struct dirent *dir_item; //Declare a struct dirent for the different entries of the current directory
    	char current_path[PATH_MAX]; //Declare a char vector to store the path of the current directory
    	
        // If the directory cannot be opened an error is raised
        if ((current_dir = opendir(getcwd(current_path, PATH_MAX))) == NULL){
        	perror("Error: Current directory could not be opened.\n");
            	return -1;
        }
        int fd, file_size; //Declare the file descriptor and the file size
        
        if ((dir_item = readdir(current_dir)) == NULL){
        	//If current directory is empty, then print that information and return 0 (being empty is not considered an error)
        	printf("Current directory is empty.\n");
        	return 0;
        }
        
        //Reset the directory pointer so it points again to the first entry (since now it is known the directory is not empty)
        rewinddir(current_dir);
        
        /*While current directory is not empty and there are still entries to read, take those entries and store them into    
        dir_item, one per loop*/
        while ((dir_item = readdir(current_dir)) != NULL){
        	//Check if the entry is a regular file
        	if ((dir_item -> d_type) == DT_REG){
			// If the file cannot be opened an error is raised
			if((fd = open((dir_item -> d_name), O_RDONLY)) < 0){
				perror("Error: File could not be opened.\n");
                       	return -1;
                    	}
                       //If the size of the open file is smaller than 0, then there was a problem. So print the error and return -1
                	if ((file_size = lseek(fd, 0, SEEK_END))<0){
                        	perror("Error: The size of the file could not be obtained.\n");
                        	return -1;
			}
			//Check if open file can be closed. If so, close it; else, print the error and return -1
                	if (close(fd) < 0){
                		perror("Error: The open file could not be closed.\n");
                		return -1;
                	}
                	//Print the regular file name and its size in bytes
                	printf("%s    %d\n", (dir_item -> d_name), file_size);
		}
        }
        
     	//Once all regular files from the current directory are read, close the directory
        if (closedir(current_dir) < 0){
        	//If current directory could not be closed, then report the error and return -1
        	perror("Error: Current directory could not be closed.\n");
        	return -1;
        };
        //Operation successful
        return 0;
}   
