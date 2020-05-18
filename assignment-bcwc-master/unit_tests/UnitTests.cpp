#include "../header/And.hpp"
#include "../header/Command.hpp"
#include "../header/Component.hpp"
#include "../header/Connector.hpp"
#include "../header/Executer.hpp"
#include "../header/Or.hpp"
#include "../header/RShell.hpp"
#include "../header/Semi.hpp"
#include "../header/Token.hpp"
#include "../header/Tokenizer.hpp"
#include <fstream>
#include "gtest/gtest.h"

TEST(Tokenizer, Split_into_tokens)
{
    string in = "ls -a";
    Tokenizer t;
    vector<Token> *test;
    test = t.split_into_tokens(in);
    vector<Token> expout;
    expout.push_back(Token("ls"));
    expout.push_back(Token("-a"));
    bool same = (expout[0].getVal() == test->at(0).getVal() && expout[1].getVal() == test->at(1).getVal());
    EXPECT_EQ(1, same);
}

TEST(Token, Token_func)
{
    string in = "ls";
    Tokenizer t;
    vector<Token> *test;
    test = t.split_into_tokens(in);
    string tok = test->at(0).getVal();
    EXPECT_EQ("ls", tok);
}

TEST(Composite_execute_test, And_execute_test_inti)
{
    string in = "ls -a && echo a";
    Tokenizer t;
    vector<Token> *test;
    test = t.split_into_tokens(in);
    Component *b = t.string_to_tree(in);
    testing::internal::CaptureStdout();
    bool out = b->execute(0, 1);
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(1, out);
}

TEST(Composite_execute_test, Or_execute_test_inti)
{
    string in = "ls -a || echo a";
    Tokenizer t;
    vector<Token> *test;
    test = t.split_into_tokens(in);
    Component *b = t.string_to_tree(in);
    testing::internal::CaptureStdout();
    bool out = b->execute(0, 1);
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(1, out);
}

TEST(assignment_3_tests, test_command_no_flag)
{
    string in = "test rshell";
    Tokenizer t;
    vector<Token> *test;
    Component *b = t.string_to_tree(in);
    testing::internal::CaptureStdout();
    bool out = b->execute(0, 1);
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ("(True)\n", output);
}

TEST(assignment_3_tests, test_command_e)
{
    string in = "test -e rshell";
    Tokenizer t;
    vector<Token> *test;
    Component *b = t.string_to_tree(in);
    testing::internal::CaptureStdout();
    bool out = b->execute(0, 1);
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ("(True)\n", output);
}

TEST(assignment_3_tests, test_command_f)
{
    string in = "test rshell";
    Tokenizer t;
    vector<Token> *test;
    Component *b = t.string_to_tree(in);
    testing::internal::CaptureStdout();
    bool out = b->execute(0, 1);
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ("(True)\n", output);
}

TEST(assignment_3_tests, test_command_d)
{
    string in = "test -d header";
    Tokenizer t;
    vector<Token> *test;
    Component *b = t.string_to_tree(in);
    testing::internal::CaptureStdout();
    bool out = b->execute(0, 1);
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ("(True)\n", output);
}

TEST(assignment_3_tests, test_command_e_fail)
{
    string in = "test -e random";
    Tokenizer t;
    vector<Token> *test;
    Component *b = t.string_to_tree(in);
    testing::internal::CaptureStderr();
    testing::internal::CaptureStdout();
    bool out = b->execute(0, 1);
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ("(False)\n", output);
}

TEST(assignment_3_tests, test_command_f_fail)
{
    string in = "test -f src";
    Tokenizer t;
    vector<Token> *test;
    Component *b = t.string_to_tree(in);
    testing::internal::CaptureStdout();
    bool out = b->execute(0, 1);
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ("(False)\n", output);
}
TEST(assignment_3_tests, test_command_d_fail)
{
    string in = "test -d rshell";
    Tokenizer t;
    vector<Token> *test;
    Component *b = t.string_to_tree(in);
    testing::internal::CaptureStdout();
    bool out = b->execute(0, 1);
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ("(False)\n", output);
}

TEST(assignment_3_tests, test_par)
{
    string in = "echo hi && (echo l || echo w;)";
    Tokenizer t;
    vector<Token> *test;
    Component *b = t.string_to_tree(in);
    testing::internal::CaptureStdout();
    bool out = b->execute(0, 1);
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ("hi\nl\n", output);
}

TEST(assignment_3_tests, test_par_in_par)
{
    string in = "echo hi && (echo l || (echo w && echo d))";
    Tokenizer t;
    vector<Token> *test;
    Component *b = t.string_to_tree(in);
    testing::internal::CaptureStdout();
    bool out = b->execute(0, 1);
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ("hi\nl\n", output);
}

TEST(assignment_4_tests, single_create_new_file_)
{
    string in = "echo make a new file > newFile.txt";
    Tokenizer t;
    Component *b = t.string_to_tree(in);
    bool out = b->execute(0, 1);
    string in1 = "test -e newFile.txt && echo newFile.txt exists";
    Tokenizer t1;
    Component *b1 = t1.string_to_tree(in1);
    testing::internal::CaptureStdout();
    bool out1 = b1->execute(0, 1);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("(True)\nnewFile.txt exists\n", output);
}

TEST(assignment_4_tests, double_create_new_file_)
{
    string in = "echo make a new file >> newFile1.txt";
    Tokenizer t;
    Component *b = t.string_to_tree(in);
    bool out = b->execute(0, 1);
    string in1 = "test -e newFile1.txt && echo newFile1.txt exists";
    Tokenizer t1;
    Component *b1 = t1.string_to_tree(in1);
    testing::internal::CaptureStdout();
    bool out1 = b1->execute(0, 1);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("(True)\nnewFile1.txt exists\n", output);
}

TEST(assignment_4_tests, read_from_nonexisit_file)
{
    string in = "cat < thisFileDoesntExist.txt";
    Tokenizer t;
    vector<Token> *test;
    Component *b = t.string_to_tree(in);
    testing::internal::CaptureStdout();
    bool out = b->execute(0, 1);
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ("error\n", output);
}

TEST(assignment_4_tests, output_redirect)
{
    string in = "cat < names.txt";
    Tokenizer t;
    vector<Token> *test;
    Component *b = t.string_to_tree(in);
    testing::internal::CaptureStdout();
    bool out = b->execute(0, 1);
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ("Jason Shweiri, 862155711, jshwe001@ucr.edu\nRyan Giron, 862128210, rgiro004@ucr.edu\n", output);
}

TEST(assignment_4_tests, single_input_redirect)
{
    string in = "echo read me > ReadTest.txt";
    Tokenizer t;
    Component *b = t.string_to_tree(in);
    bool out = b->execute(0, 1);
    ifstream myfile;
    myfile.open("ReadTest.txt");
    string output = "";
    string temp;
    while (getline(myfile, temp))
    {
        output += temp;
    }
    myfile.close();

    EXPECT_EQ("read me", output);
}

// TEST(assignment_4_tests, double_input_redirect)
// {
//     string in = "echo read me > ReadTestjustatest.txt";
//     Tokenizer t;
//     Component *b = t.string_to_tree(in);
//     bool out = b->execute(0, 1);
//     ifstream myfile;
//     myfile.open("ReadTestjustatest.txt");
//     string output = "";
//     string temp;
//     while (getline(myfile, temp))
//     {
//         output += temp;
//     }
//     myfile.close();

//     EXPECT_EQ("read me", output);
// }
TEST(assignment_4_tests, double_input_redirect)
{
    string in = "echo read me >> ReadTestjustatest1.txt";
    Tokenizer t;
    Component *b = t.string_to_tree(in);
    bool out = b->execute(0, 1);
    ifstream myfile;
    myfile.open("ReadTestjustatest1.txt");
    string output = "";
    string temp;
    while (getline(myfile, temp))
    {
        output += temp;
    }
    myfile.close();

    EXPECT_EQ("read me", output);
}

TEST(assignment_4_tests, pipping_redirect)
{
    string in = "echo pipe this | cat";
    Tokenizer t;
    Component *b = t.string_to_tree(in);
    testing::internal::CaptureStdout();
    bool out = b->execute(0, 1);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("pipe this\n", output);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
