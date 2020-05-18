#ifndef __OUTPUTREDIRECT_HPP__
#define __OUTPUTREDIRECT_HPP__
#include "Connector.hpp"

class OutputRedirect : public Connector
{
public:
    OutputRedirect() : Connector() {}
    OutputRedirect(Component *l, Component *r) : Connector(l, r) {}
    virtual bool is_output_redirect()
    {
        return true;
    }
    virtual bool execute(int in, int out)
    {
        int new_out = open(right->get_val().c_str(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

        if (new_out < 0)
        {
            cout << "error\n";
            return false;
        }
        else
        {
            return left->execute(in, new_out);
        }
    }
    virtual int get_priority()
    {
        return 3;
    }
    virtual string get_val()
    {
        return ">";
    }
};

#endif