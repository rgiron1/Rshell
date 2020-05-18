#ifndef __TOKENIZER_HPP__
#define __TOKENIZER_HPP__

#include <stack>
#include <string>
#include <vector>
#include "And.hpp"
#include "Command.hpp"
#include "Component.hpp"
#include "InputRedirect.hpp"
#include "Or.hpp"
#include "OutputRedirect.hpp"
#include "OutputRedirect2.hpp"
#include "Par.hpp"
#include "Piping.hpp"
#include "Semi.hpp"
using namespace std;

class Tokenizer
{
public:
    Component *string_to_tree(string input)
    {
        return postfix_to_tree(infix_to_postfix(combine_into_cmds_and_cntrs(split_into_tokens(input))));
    }

    Component *postfix_to_tree(vector<Component *> *postfix)
    {
        stack<Component *> st;
        Component *t, *t1, *t2;
        Connector *c;

        //Make commands somewhere from vector of tokens

        // Traverse through every character of
        // input expression
        for (int i = 0; i < postfix->size(); i++)
        {
            // If operand, simply push into stack
            if (!(postfix->at(i)->is_connector()))
            {
                t = postfix->at(i);
                st.push(t);
            }
            else // operator
            {
                if (postfix->at(i)->is_and())
                {
                    c = new And();
                }
                else if (postfix->at(i)->is_or())
                {
                    c = new Or();
                }
                else if (postfix->at(i)->is_semi())
                {
                    c = new Semi();
                }
                else if (postfix->at(i)->is_input_redirect())
                {
                    c = new InputRedirect();
                }
                else if (postfix->at(i)->is_output_redirect())
                {
                    c = new OutputRedirect();
                }
                else if (postfix->at(i)->is_output_redirect2())
                {
                    c = new OutputRedirect2();
                }
                else if (postfix->at(i)->is_pipe())
                {
                    c = new Piping();
                }

                // Pop two top nodes
                if (st.size() == 0)
                {
                    t1 = nullptr;
                }
                else
                {
                    t1 = st.top();
                    st.pop();
                }

                if (st.size() == 0)
                {
                    t2 = nullptr;
                }
                else
                {
                    t2 = st.top();
                    st.pop();
                }

                //  make them children
                c->set_right(t1);
                c->set_left(t2);

                // Add this subexpression to stack
                st.push(c);
            }
        }

        //  only element will be root of expression
        // tree
        t = st.top();
        st.pop();

        return t;
    }

    vector<Component *> *infix_to_postfix(vector<Component *> *infix)
    {
        vector<Component *> *postfix = new vector<Component *>;

        infix->insert(infix->begin(), new Par(true));
        infix->push_back(new Par(false));

        stack<Component *> op_stack;

        for (int i = 0; i < infix->size(); i++)
        {
            // If the scanned character is an
            // operand, add it to output.              //operand is command
            if (infix->at(i)->is_command())
            {
                postfix->push_back(infix->at(i));
            }
            // If the scanned character is an
            // ‘(‘, push it to the stack.
            else if (infix->at(i)->islpar())
            {
                op_stack.push(infix->at(i));
            }

            // If the scanned character is an
            // ‘)’, pop and output from the stack
            // until an ‘(‘ is encountered.
            else if (infix->at(i)->isrpar())
            {
                while ((op_stack.size() > 0) && !(op_stack.top()->islpar()))
                {
                    postfix->push_back(op_stack.top());
                    op_stack.pop();
                }

                // Remove '(' from the stack
                op_stack.pop();
            }

            // Operator found
            else
            {
                if (op_stack.size() > 0)
                {
                    if (op_stack.top()->is_connector())
                    {
                        while (infix->at(i)->get_priority() <= op_stack.top()->get_priority())
                        {
                            postfix->push_back(op_stack.top());
                            op_stack.pop();
                        }
                        // Push current Operator on stack
                        op_stack.push(infix->at(i));
                    }
                }
            }
        }
        return postfix;
    }

    vector<Component *> *combine_into_cmds_and_cntrs(vector<Token> *a)
    {
        vector<Token> command;
        vector<Component *> *connectors = new vector<Component *>;

        for (int i = 0; i < a->size(); i++)
        {
            if ((*a)[i].getVal() == "&&")
            {
                if (command.size() > 0)
                    connectors->push_back(new Command(command));
                command.clear();
                connectors->push_back(new And());
            }
            else if ((*a)[i].getVal() == "||")
            {
                if (command.size() > 0)
                    connectors->push_back(new Command(command));
                command.clear();
                connectors->push_back(new Or());
            }
            else if ((*a)[i].getVal() == ";")
            {
                if (command.size() > 0)
                    connectors->push_back(new Command(command));
                command.clear();
                connectors->push_back(new Semi());
            }
            else if ((*a)[i].getVal() == ")")
            {
                if (command.size() > 0)
                    connectors->push_back(new Command(command));
                command.clear();
                connectors->push_back(new Par(false));
            }
            else if ((*a)[i].getVal() == "(")
            {
                if (command.size() > 0)
                    connectors->push_back(new Command(command));
                command.clear();
                connectors->push_back(new Par(true));
            }
            else if ((*a)[i].getVal() == "<")
            {
                if (command.size() > 0)
                    connectors->push_back(new Command(command));
                command.clear();
                connectors->push_back(new InputRedirect());
            }
            else if ((*a)[i].getVal() == "|")
            {
                if (command.size() > 0)
                    connectors->push_back(new Command(command));
                command.clear();
                connectors->push_back(new Piping());
            }
            else if ((*a)[i].getVal() == ">>")
            {
                if (command.size() > 0)
                    connectors->push_back(new Command(command));
                command.clear();
                connectors->push_back(new OutputRedirect2()); //add class output redirect 2
            }
            else if ((*a)[i].getVal() == ">")
            {
                if (command.size() > 0)
                    connectors->push_back(new Command(command));
                command.clear();
                connectors->push_back(new OutputRedirect());
            }
            else
            {
                command.push_back((*a)[i]);
                if (i == a->size() - 1)
                {
                    connectors->push_back(new Command(command));
                    command.clear();
                }
            }
        }
        return connectors;
    }

    //Converts string into vector of Tokens
    vector<Token> *split_into_tokens(string s)
    {
        vector<Token> *tokens = new vector<Token>;
        string temp;

        //for every character in the input string
        for (int i = 0; i < s.size(); i++)
        {
            //If not a space
            if (s[i] != ' ')
            {
                //then if we find a # add the current token to the vector and stop
                if (s[i] == '#')
                {
                    tokens->push_back(Token(temp));
                    return tokens;

                    //Then if we find a ; ( or )
                    //add the current token as well as the ; ( or )
                } //check for >>
                else if (s[i] == ';' || s[i] == '(' || s[i] == ')' || s[i] == '[' || s[i] == ']' || s[i] == '<' || s[i] == '>' || (s[i] == '|'))
                {
                    // cout << s[i + 1];
                    if (s[i + 1] == '|')
                    {
                        temp += "||";
                        i += 1;
                        continue;
                    }

                    if (s[i + 1] == '>')
                    {
                        temp += ">>";
                        i += 1;
                        continue;
                    }

                    if (temp != "")
                    {
                        tokens->push_back(Token(temp));
                    }
                    tokens->push_back(Token(s[i]));
                    temp = "";
                    continue;

                    //Then if we find a quote
                }
                else if (s[i] == '\"')
                {
                    i++;
                    //Add everything until next quote to current token
                    while (s[i] != '\"')
                    {
                        temp += s[i];
                        i++;
                    }
                    //  Then add that token to the vector
                    i++;
                    tokens->push_back(Token(temp));
                }

                temp += s[i];

                if (i == s.size() - 1)
                {
                    if (temp != "")
                    {
                        tokens->push_back(Token(temp));
                    }
                }

                // If there is a space add the current token to the vector
            }
            else
            {
                if (temp != "")
                {
                    tokens->push_back(Token(temp));
                    temp = "";
                }
            }
        }
        return tokens;
    }
};
#endif
