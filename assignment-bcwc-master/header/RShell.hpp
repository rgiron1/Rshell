#ifndef __RSHELL_HPP__
#define __RSHELL_HPP__

#include "Executer.hpp"
#include "Tokenizer.hpp"

class RShell {
   public:
    string get_input() {
        string inputString;
        if (!getline(cin, inputString)) {
            cout << "err";
            return "#";
        }
        return inputString;
    }
    void run() {
        while (1) {
            cout << "$";
            string in = get_input();

            string temp = "";
            temp += in[0];
            temp += in[1];

            if (in == "" || in[0] == '#' || temp == "&&" || temp == "||") {   // move into tokenizer and check for length of command / connectors
                continue;
            }
            Tokenizer t;

            Component *b = t.string_to_tree(in);
            //  Component *b = t.postfix_to_tree(t.infix_to_postfix(t.combine_into_cmds_and_cntrs(t.split_into_tokens(in))));
            b->execute(0, 1);
        }
    }

   private:
    //Tokenizer, Executer,
};

#endif
