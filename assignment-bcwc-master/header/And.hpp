#ifndef __AND_HPP__
#define __AND_HPP__

#include "Connector.hpp"

class And : public Connector {
   public:
    And() : Connector() {
    }

    And(Component* l, Component* r) : Connector(l, r) {}
    virtual bool execute(int in, int out) {
        if (left == nullptr || left->execute(in, out)) {
            return right->execute(in, out);
        }
        return false;
    }

    virtual bool is_and() {
        return true;
    }

    virtual void print() {
        cout << "&&\n";
    }
};
#endif
