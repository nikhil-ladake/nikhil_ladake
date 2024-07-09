#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PATH_MAX 4096

int main(int argc, char *argv[]) {
    char cwd[PATH_MAX];
    static char prev_cwd[PATH_MAX] = "";

    // Initialize the prev_cwd to the current directory at the start
    if (getcwd(prev_cwd, sizeof(prev_cwd)) == NULL) {     //returns an absolute file name of current working dirrectory
        perror("getcwd() error");    // print error
        return 1;
    }

    // Check if the command entered is correct or not 
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);  //print content from file
        //printf("Usage: %s <directory_name>\n", argv[0]);
        return 1;
    }
    
    
    char *path = argv[1]; // pointer to directory entered 

    // Handle "cd -"
    if (strcmp(path, "-") == 0) {
        //checking for previous directory
        if (strlen(prev_cwd) ==   0) {  
            printf("Error: OLDPWD not set\n");
            return 1;
        }
        path = prev_cwd;
    }

    // Get the current working directory before changing it
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd() error");
        return 1;
    }

    // Change the directory
    if (chdir(path) != 0) {
        perror("chdir() error");
        return 1;
    }

    // Update prev_cwd to the previous directory
    strncpy(prev_cwd, cwd, sizeof(prev_cwd));

    // Get and print the new current working directory
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd() error");
        return 1;
    }

    printf("Changed directory to: %s\n", cwd);

    return 0;
}

