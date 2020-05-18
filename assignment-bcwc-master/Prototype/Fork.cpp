#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>

int
main() {
	std::string UserInput;
	int stat_loc;
	
	std::cout << "Please input a string: " << UserInput;
	std::cin >> UserInput;
	pid_t wait_result;
	pid_t child_pid = fork();

	if( child_pid == 0) {
		std::cout << "### Child ###\nCurrent PID: " << getpid() << " and Child PID: " << child_pid << std::endl;
		std::cout << "The parent funtion's input is: " << UserInput << std::endl;
	} else {
		wait_result = waitpid(child_pid, &stat_loc, WUNTRACED);
		std::cout << "### Parent  ###\nCurrent PID: " << getpid() << " and Child PID: " << child_pid << std::endl;
	}
	return 0;
}

