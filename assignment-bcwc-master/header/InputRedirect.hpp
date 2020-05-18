#ifndef __INPUTREDIRECT_HPP__
#define __INPUTREDIRECT_HPP__
#include "Connector.hpp"

class InputRedirect : public Connector
{
public:
    InputRedirect() : Connector() {}
    InputRedirect(Component *l, Component *r) : Connector(l, r) {}
    virtual bool is_input_redirect()
    {
        return true;
    }

    virtual bool execute(int in, int out)
    {
        int new_in = open(right->get_val().c_str(), O_RDONLY | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        if (new_in < 0)
        {
            cout << "error\n";
            return false;
        }
        else
        {
            return left->execute(new_in, out);
        }
    }
    virtual int get_priority()
    {
        return 3;
    }

    virtual string get_val()
    {
        return "<";
    }
};
#endif