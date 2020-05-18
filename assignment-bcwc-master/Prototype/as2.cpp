#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

class Executer{
	public:
		bool executeCommand(char** argv){
			
    if (strcmp(argv[0], "exit") == 0)
    {
        exit(0);
    }

    if (strcmp(argv[0], "cd") == 0)
    {
        if (chdir(argv[1]) < 0)
        {
            perror(argv[1]);
	    return false;
        }
        return true;
    }

    pid_t child_pid = fork();

    if (child_pid < 0)
    {
        perror("fork failed");
        exit(1);
    }

    if (child_pid == 0)
    {
	    auto success = execvp(argv[0], argv);
        
	    if (success < 0)
        {
            perror(argv[0]);
        return false;   
        }
	
    }
    else
    {
        int stat_loc;
        auto poop = waitpid(child_pid, &stat_loc, WUNTRACED);
	cout << poop << '\n';
	return true;
    }
		}
};
class Rshell{
	public:
void get_input(char **argv)
{
    char *cstr;
    string arg;
    int argc = 0;

    // Read in arguments till the user hits enter
    while (cin >> arg)
    {

        // Convert that std::string into a C string.
        cstr = new char[arg.size() + 1];
        strcpy(cstr, arg.c_str());
        argv[argc] = cstr;

        // Increment our counter of where we're at in the array of arguments.
        argc++;

        // If the user hit enter, stop reading input.
        if (cin.get() == '\n')
            break;
    }

    // Have to have the last argument be NULL so that execvp works.
    argv[argc] = NULL;

    return;
}

};


int main()
{
Executer *e = new Executer();
Rshell *r = new Rshell();

while (1)
    {
        std::cout << '$';

        char *command[200];

       r->get_input(command);

        //cout << (bool) e->executeCommand(command);
	e->executeCommand(command);
    }
    return 0;
}
