#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <vector>
#include <cstring>

int main()
{
    std::cout << '$';
    std::string s;
    std::getline(std::cin, s);

    char *pch;
    pch = strtok(&s[0], " ");

    std::vector<const char *> result;

    while (pch != NULL)
    {
        result.push_back(pch);
        pch = strtok(NULL, " ");
    }

    char **argv = const_cast<char **>(result.data());

    int stat_loc;
    pid_t wait_result;
    pid_t child_pid = fork();

    if (child_pid == 0)
    {
        execvp(argv[0], argv);
    }
    else
    {
        wait_result = waitpid(child_pid, &stat_loc, WUNTRACED);
        std::cout << "Command Completed! \n";
    }
    return 0;
}
