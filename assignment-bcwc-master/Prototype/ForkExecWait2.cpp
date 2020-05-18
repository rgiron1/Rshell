#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <vector>
#include <cstring>

const char **get_input(std::string input){

    std::vector<const char *> result;

    char *pch = strtok(&input[0], " ");

    while (pch != NULL){
        result.push_back(pch);
        pch = strtok(NULL, " ");
    }

    return result.data();
}

int main(){
    int stat_loc;
    pid_t child_pid;
    std::string input;
    int j = 0;
    while (1){
        std::cout << '$';

        std::getline(std::cin, input);

        std::vector<const char *> result;

        for (int i = 0; i < j; i++){
            result.push_back(NULL);
        }
        result.clear();

        char *pch = strtok(&input[0], " ");

        while (pch != NULL){
            result.push_back(pch);
            pch = strtok(NULL, " ");
        }

        char **command = const_cast<char **>(result.data());

        for (j = 0; j < result.size(); j++){
        }

        //std::cout <<result[1];// command[1];

        if (strcmp(command[0], "exit") == 0){
            return 0;
        }

        if (strcmp(command[0], "cd") == 0){
            if (chdir(command[1]) < 0){
                perror(command[1]);
            }
            continue;
        }

        child_pid = fork();

        if (child_pid < 0){
            perror("fork failed");
            exit(1);
        }

        if (child_pid == 0){
            if (execvp(command[0], command) < 0){
                perror(command[0]);
                exit(1);
            }
        }
        else{
            waitpid(child_pid, &stat_loc, WUNTRACED);
        }
    }
    return 0;
}
