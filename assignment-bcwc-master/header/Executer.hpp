#ifndef __EXECUTER_HPP__
#define __EXECUTER_HPP__

#include "Connector.hpp"

class Executer {
   public:
    void setBase(Connector *b) {
        base = b;
    }

    bool execute(int in, int out) {
        return base->execute(in, out);
    }

   private:
    Connector *base;
};

#endif
