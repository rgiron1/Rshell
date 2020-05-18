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

TEST(Intigration_test, Output_cmpr)
{
    string in = "echo c || hello";
    Tokenizer t;
    Component *b = t.string_to_tree(in);
    testing::internal::CaptureStdout();
    b->execute(0, 1);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("c\n", output);
}

TEST(Intigration_test, Output_cmpr2)
{
    string in = "echo c; echo uWu";
    Tokenizer t;
    Component *b = t.string_to_tree(in);
    testing::internal::CaptureStdout();
    b->execute(0, 1);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("c\nuWu\n", output);
}

TEST(Intigration_test, Output_cmpr3)
{
    string in = "echo c; echo hello && echo a || echo world; echo hi";
    Tokenizer t;
    Component *b = t.string_to_tree(in);
    testing::internal::CaptureStdout();
    b->execute(0, 1);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("c\nhello\na\nhi\n", output);
}

TEST(Intigration_test, output_cmpr4)
{
    string in = "echo does rshell exsist? && test -f rshell ";
    Tokenizer t;
    Component *b = t.string_to_tree(in);
    testing::internal::CaptureStdout();
    b->execute(0, 1);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("does rshell exsist?\n(True)\n", output);
}

TEST(Intigration_test, output_cmpr5)
{
    string in = "[ -d header ] && echo symbolic works";
    Tokenizer t;
    Component *b = t.string_to_tree(in);
    testing::internal::CaptureStdout();
    b->execute(0, 1);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("(True)\nsymbolic works\n", output);
}

TEST(Intigration_test, output_cmpr6)
{
    string in = "echo hello && (test -f rshell && (echo does this work || echo maybe not))";
    Tokenizer t;
    Component *b = t.string_to_tree(in);
    testing::internal::CaptureStdout();
    b->execute(0, 1);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("hello\n(True)\ndoes this work\n", output);
}

TEST(Intigration_test, output_redirection_test)
{
    string in = "echo new file will be made && (echo read me > intTest1.txt) && (echo read this >> intTest2.txt) && test -e intTest1.txt && test -e intTest2.txt";
    Tokenizer t;
    Component *b = t.string_to_tree(in);
    testing::internal::CaptureStdout();
    b->execute(0, 1);
    string output = testing::internal::GetCapturedStdout();
    ifstream myfile;
    myfile.open("intTest1.txt");
    string output2 = "";
    string temp;
    while (getline(myfile, temp))
    {
        output2 += temp;
    }
    myfile.close();
    ifstream myfile2;
    myfile2.open("intTest2.txt");
    string output3 = "";
    string temp2;
    while (getline(myfile2, temp2))
    {
        output3 += temp2;
    }
    myfile2.close();
    EXPECT_EQ("new file will be made\n(True)\n(True)\n", output);
    EXPECT_EQ("read me", output2);
    EXPECT_EQ("read this", output3);
}

TEST(Intigration_test, output_redirection_tests)
{
    string in = "echo the names file will be read && (cat < names.txt)";
    Tokenizer t;
    Component *b = t.string_to_tree(in);
    testing::internal::CaptureStdout();
    bool out = b->execute(0, 1);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("the names file will be read\nJason Shweiri, 862155711, jshwe001@ucr.edu\nRyan Giron, 862128210, rgiro004@ucr.edu\n", output);
}

TEST(assignment_4_tests, pipe_operator_test)
{
    string in = "echo did this work? && (echo pipe this | cat) && echo success!";
    Tokenizer t;
    Component *b = t.string_to_tree(in);
    testing::internal::CaptureStdout();
    bool out = b->execute(0, 1);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("did this work?\npipe this\nsuccess!\n", output);
}