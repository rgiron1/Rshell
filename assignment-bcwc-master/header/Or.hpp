#ifndef __OR_HPP__
#define __OR_HPP__
#include "Connector.hpp"

class Or : public Connector
{
public:
    Or() : Connector()
    {
    }

    Or(Component *l, Component *r) : Connector(l, r) {}
    virtual bool execute(int in, int out)
    {
        if (left == nullptr || !(left->execute(in, out)))
        {
            return right->execute(in, out);
        }
        return true; //IS THIS CORRECT?
    }

    virtual void print()
    {
        cout << "||\n";
    }

    virtual bool is_or()
    {
        return true;
    }
};
#endif
