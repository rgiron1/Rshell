#ifndef __SEMI_HPP__
#define __SEMI_HPP__
#include "Connector.hpp"

class Semi : public Connector
{
public:
    Semi() : Connector()
    {
    }

    Semi(Component *l, Component *r) : Connector(l, r) {}
    virtual bool execute(int in, int out)
    {
        if (left == nullptr || left->execute(in, out))
        {
            right->execute(in, out);
        }
        return true; //change this!
    }

    virtual bool is_semi()
    {
        return true;
    }
};
#endif
