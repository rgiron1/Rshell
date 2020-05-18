#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Tokenizer
{
public:
    void group_tokens_by_command(vector<string> *a, vector<vector<string>> *b)
    {
        vector<string> temp2;
        for (int i = 0; i < a->size(); i++)
        {

            if ((*a)[i] != "&&" && (*a)[i] != "||" && (*a)[i] != ";")
            {
                temp2.push_back((*a)[i]);
            }
            else
            {
                b->push_back(temp2);
                temp2.clear();
            }

            if (i == a->size() - 1)
            {
                b->push_back(temp2);
                temp2.clear();
            }
        }
    }

    void split_into_tokens(string s, vector<string> *a)
    {
        string temp;
        for (int i = 0; i < s.size(); i++)
        {

            if (s[i] != ' ')
            {
                if (s[i] == '#')
                {
                    return;
                }

                // Quotes
                if (s[i] == '\"')
                {
                    do
                    {
                        temp += s[i];
                        i++;
                    } while (s[i] != '\"');
                    temp += s[i];
                    i++;
                    a->push_back(temp);
                }

                temp += s[i];
            }
            else
            {
                a->push_back(temp);
                temp = "";
            }
        }
    }
};

class Component
{
public:
    bool virtual execute() = 0;
};

class Command : public Component
{
public:
    Command(string s)
    {
        val = s;
    }
    bool execute()
    {
        cout << val;
    }

private:
    string val;
};

class Connector : public Component
{
public:
    Connector(Component *lhs, Component *rhs)
    {
        l = lhs;
        r = rhs;
    }
    bool execute()
    {
        cout << l->execute() << " && " << r->execute();
    }

private:
    Component *l;
    Component *r;
};

int main()
{

    Tokenizer t;

    string s = "cd Prototype && ls -a || echo \"more && s#it \" #ignore all this";
    vector<string> a;

    t.split_into_tokens(s, &a);

    for (int i = 0; i < a.size(); i++)
    {
        cout << i << ": " << a[i] << "\n";
    }

    cout << "\n\n";

    //group by command
    vector<vector<string>> b;

    t.group_tokens_by_command(&a, &b);

    for (int i = 0; i < b.size(); i++)
    {
        cout << i << ": ";
        for (int j = 0; j < b[i].size(); j++)
        {
            cout << b[i][j] << " ";
        }
        cout << '\n';
    }

    return 0;
}