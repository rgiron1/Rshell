#ifndef __PAR_HPP__
#define __PAR_HPP__
#include "Component.hpp"

class Par : public Component
{
public:
    Par(bool l)
    {
        isleft = l;
    }

    virtual bool islpar()
    {
        return isleft;
    }

    virtual bool isrpar()
    {
        return !isleft;
    }
    virtual bool execute(int in, int out)
    {
        return false;
    }

    virtual void print()
    {
        cout << "par";
    }

    virtual bool is_connector()
    {
        return true;
    }

private:
    bool isleft = false;
};

#endif
