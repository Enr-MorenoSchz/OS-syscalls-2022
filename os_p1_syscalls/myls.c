#include <stdio.h>		/* Header file for system call printf */
#include <unistd.h>		/* Header file for system call gtcwd */
#include <sys/types.h>		/* Header file for system calls opendir, readdir y closedir */
#include <dirent.h>
#include <string.h>


int main(int argc, char *argv[]){

	//If the number of arguments is more than two we print the error and return -1
    	if (argc > 2) {
        	perror("Error: More than 1 argument has been entered.\n");
        	return -1;
    	}
    	
    	//If the number of arguments less than two, then we know we have to take the current directory path
    	if (argc < 2) {
        	char current_path[PATH_MAX]; //Declare a char vector with the max size of the current path to store its entire name
        	DIR *current_dir; //Declare a pointer to a DIR data type to later store the address of the open directory
        	struct dirent *dir_item; //Declare a struct dirent to later use it for the different entries of the open directory
        	
        	/*Check if there is an error opending current directory. If not store the its address into current_dir (after 			using getcwd function to obtain the name of the and storing it into current_path)*/
        	if ((current_dir = opendir(getcwd(current_path, PATH_MAX))) == NULL){
        		printf("Error: Current directory could not be opened.\n");
        		return -1;
        	} 
        	
		//Check if current directory is empty. If so, print that it is empty and return 0 (it is not considered an error)
		if((dir_item = readdir(current_dir)) == NULL){
			printf("Current directory is empty.\n");
			return 0;
		}
		
		/*Reset the directory pointer so it points again to the first entry (since now it is known the directory is not 			empty)*/
		rewinddir(current_dir);
		
		//If current directory is not empty and there are still entries to be read, print the name of each entry
        	while ((dir_item = readdir(current_dir)) != NULL) {
        		printf("%s\n", dir_item -> d_name);
        	}
        	
        	if (closedir(current_dir) < 0){
        		//If current directory could not be closed, then print the error and return -1
        		printf("Error: Current directory could not be closed.\n");
        		return -1;
        	}
        	//Operation was successful
        	return 0;
	}
	
	//For this case, there was just one directory received as parameter (2 arguments in total)
	
    	DIR *given_dir; //Declare a pointer to a DIR data type to later store the address of the open directory
    	struct dirent *dir_item; //Declare a struct dirent to later use it for the different entries of the open directory
    	
    	//Check if given directory can be opened. If so, store its address in given_dir, else print an error and return -1
    	if ((given_dir = opendir(argv[1])) == NULL){
    		printf("Error: Given directory could not be opened.\n");
    		return -1;
    	};
	
	//Check if given directory is empty. If so, print that it is empty and return 0 (it is not considered an error)
	if((dir_item = readdir(given_dir)) == NULL){
		printf("Given directory is empty.\n");
		return 0;
	}
	
	//Reset the directory pointer so it points again to the first entry (since now it is known the directory is not empty)
	rewinddir(given_dir);
	
	//If given directory is not empty and there are still entries to be read, print the name of each entry	
    	while ((dir_item = readdir(given_dir)) != NULL) {
        	printf("%s\n", dir_item -> d_name);
    	}
    	
    	if (closedir(given_dir) < 0){
        	//If given directory could not be closed, then print the error and return -1
        	printf("Error: Given directory could not be closed.\n");
        	return -1;
        }
        //Operation was successfull
    	return 0;
}

