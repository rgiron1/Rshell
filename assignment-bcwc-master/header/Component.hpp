#ifndef __COMPONENT_HPP__
#define __COMPONENT_HPP__

#include <iostream>
#include "fcntl.h"
#include "stdio.h"
#include "unistd.h"
using namespace std;

class Component
{
public:
    virtual bool execute(int in, int out) = 0;
    virtual bool is_and()
    {
        return false;
    }
    virtual bool is_or()
    {
        return false;
    }
    virtual bool is_semi()
    {
        return false;
    }
    virtual bool is_connector()
    {
        return false;
    }
    virtual bool is_command()
    {
        return false;
    }
    virtual bool islpar()
    {
        return false;
    }
    virtual bool isrpar()
    {
        return false;
    }
    virtual int get_priority()
    {
        return 0;
    }
    virtual bool is_input_redirect()
    {
        return false;
    }
    virtual bool is_output_redirect()
    {
        return false;
    }
    virtual bool is_output_redirect2()
    {
        return false;
    }
    virtual bool is_pipe()
    {
        return false;
    }
    virtual string get_val()
    {
        return "";
    }

    virtual void append(string s)
    {
    }

    // for testing
    virtual void print()
    {
        return;
    }
};
#endif
