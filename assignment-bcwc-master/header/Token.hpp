#ifndef __TOKEN_HPP__
#define __TOKEN_HPP__

#include <string>
using namespace std;

class Token {
   public:
    Token(string s) {
        value = s;
    }

    Token(char s) {
        value = s;
    }

    virtual string getVal() {
        return value;
    }

   protected:
    string value;
};
#endif
