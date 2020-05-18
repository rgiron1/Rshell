#ifndef __CONNECTOR_HPP__
#define __CONNECTOR_HPP__

#include "Component.hpp"
using namespace std;

class Connector : public Component {
   public:
    Connector() {
        left = nullptr;
        right = nullptr;
    }

    Connector(Component *l, Component *r) {
        left = l;
        right = r;
    }

    Connector(Component *l) {
        left = l;
    }

    void set_right(Component *r) {
        right = r;
    }

    void set_left(Component *l) {
        left = l;
    }

    virtual bool is_connector() {
        return true;
    }

    virtual int get_priority() {
        return 1;
    }

    virtual bool execute(int in, int out) = 0;

   protected:
    Component *left;
    Component *right;
};
#endif
