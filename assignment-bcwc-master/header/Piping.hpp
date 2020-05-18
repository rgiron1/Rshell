#ifndef __PIPING_HPP__
#define __PIPING_HPP__
#include "Connector.hpp"

class Piping : public Connector
{
public:
    Piping() : Connector() {}
    Piping(Component *l, Component *r) : Connector(l, r) {}
    virtual bool is_pipe()
    {
        return true;
    }
    virtual bool execute(int in, int out)
    {
        int fds[2];
        if (pipe(fds) < 0)
        {
            cout << "error";
            return false;
        }

        if (!left->execute(in, fds[1]))
        {
            return false;
        }

        close(fds[1]);

        if (!left->execute(fds[0], out))
        {
            return false;
        }

        close(fds[0]);

        return true;
    }
    virtual int get_priority()
    {
        return 2;
    }
    virtual string get_val()
    {
        return "|";
    }
};

#endif