#ifndef __COMMAND_HPP__
#define __COMMAND_HPP__
#include <vector>
//#include <string>
#include <string.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <unistd.h>

#include "Component.hpp"
#include "Token.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#include <iostream>

//include more
using namespace std;

class Command : public Component
{
public:
    Command(vector<Token> vectok)
    {
        command = vectok;
    }

    virtual bool is_command()
    {
        return true;
    }

    bool test_command(int argc, char **argv)
    {
        struct stat sb;

        if (argc < 3)
        {
            return false;
        }

        if (argv[1][0] == '-')
        {
            if (stat(argv[2], &sb) == -1)
            {
                perror("stat");
                return false;
            }
        }
        else
        {
            if (stat(argv[1], &sb) == -1)
            {
                perror("stat");
                return false;
            }
        }

        if (argv[1][0] == '-')
        {
            if (strcmp(argv[1], "-e") == 0)
            {
                return is_dir(sb) || is_file(sb);
            }

            if (strcmp(argv[1], "-d") == 0)
            {
                return is_dir(sb);
            }

            if (strcmp(argv[1], "-f") == 0)
            {
                return is_file(sb);
            }
        }
        else
        {
            return is_dir(sb) || is_file(sb);
        }
        return false;
    }
    //file_exists
    bool is_file(struct stat sb)
    {
        return S_ISREG(sb.st_mode); //
    }

    //dir_exists
    bool is_dir(struct stat sb)
    {
        return S_ISDIR(sb.st_mode);
    }

    virtual bool execute(int in, int out)
    {
        int stat_loc;

        int argc = 0;
        char **argv = this->convert_to_cstr(&argc);

        if (strcmp(argv[0], "exit") == 0)
        {
            exit(0);
        }

        if (strcmp(argv[0], "cd") == 0)
        {
            if (chdir(argv[1]) < 0) //cd not supposed to always returns true
            {
                perror(argv[1]);
                return false;
            }
            return true;
        }

        //Add test command here
        //check for test command
        //to_upper??
        //ignore last bracket in tokenizer
        if (strcmp(argv[0], "test") == 0 || strcmp(argv[0], "[") == 0)
        {
            if (test_command(argc, argv))
            {
                cout << "(True)\n";
                return true;
            }
            else
            {
                cout << "(False)\n";
                return false;
            }
        }

        pid_t child_pid = fork();

        if (child_pid < 0)
        {
            perror("fork failed");
            exit(1);
        }

        if (child_pid == 0)
        {
            if (dup2(in, 0) < 0)
            {
                cout << "pipe error";
            }

            if (dup2(out, 1) < 0)
            {
                cout << "pipe error";
            }

            if (execvp(argv[0], argv) < 0)
            {
                perror(argv[0]);
                exit(1);
                return false;
            }
        }
        else
        {
            waitpid(child_pid, &stat_loc, WUNTRACED);
        }

        return !WEXITSTATUS(stat_loc); //unsure about this
    }

private:
    vector<Token> command;

    //for testing
    virtual void print()
    {
        for (int i = 0; i < command.size(); i++)
        {
            cout << command[i].getVal() << '\n';
        }
    }

    virtual void append(string s)
    {
        command.push_back(Token(s));
    }

    //Converts vector of tokens into char**
    char **convert_to_cstr(int *a)
    {
        char **argv = new char *[command.size() + 1];

        for (int i = 0; i < command.size(); i++)
        {
            argv[i] = new char[command[i].getVal().size() + 1];
            strcpy(argv[i], command[i].getVal().c_str());
        }
        argv[command.size()] = NULL;
        *a = command.size() + 1;
        return argv;
    }

    virtual string get_val()
    {
        return command.at(0).getVal();
    }
};
#endif