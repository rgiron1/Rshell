# CS 100 Programming Project
## Winter 2019
## Jason Shweiri 862155711
## Ryan Giron 862128210
# Introduction: 
The first thing we do is make an instance of the Rshell class, and then call it's run command, which outputs $ and takes input from the user. It then passes it to an instance of the Tokenizer class where it splits the input up into a vector of tokens, it then determines if the each token is a command or a connector, which are both derived from the Component class. Each connector holds a right and a left Component node and runs execute() from its base, recursively calling execute on its branches if it runs into a child of the connector class, such as And, Or, Semi, Par, >>, >, <, or |. When execute() is called on an instance of the Command classs, it uses the syscalls fork(), waitpid(), and execvp() to determine if a command is valid, and run it which will return a bool. 

[22](https://github.com/cs100/assignment-bcwc/issues/22)
[21](https://github.com/cs100/assignment-bcwc/issues/21)
[20](https://github.com/cs100/assignment-bcwc/issues/20)
[9](https://github.com/cs100/assignment-bcwc/issues/19)
[18](https://github.com/cs100/assignment-bcwc/issues/18)
[17](https://github.com/cs100/assignment-bcwc/issues/17)
[16](https://github.com/cs100/assignment-bcwc/issues/16)
[15](https://github.com/cs100/assignment-bcwc/issues/15)
[14](https://github.com/cs100/assignment-bcwc/issues/14)
[13](https://github.com/cs100/assignment-bcwc/issues/13)
[12](https://github.com/cs100/assignment-bcwc/issues/12)
[11](https://github.com/cs100/assignment-bcwc/issues/11)
[10](https://github.com/cs100/assignment-bcwc/issues/10)
[9](https://github.com/cs100/assignment-bcwc/issues/9)
[8](https://github.com/cs100/assignment-bcwc/issues/8)
[7](https://github.com/cs100/assignment-bcwc/issues/7)
[6](https://github.com/cs100/assignment-bcwc/issues/6)
[5](https://github.com/cs100/assignment-bcwc/issues/5)
[4](https://github.com/cs100/assignment-bcwc/issues/4)
[3](https://github.com/cs100/assignment-bcwc/issues/3)
[2](https://github.com/cs100/assignment-bcwc/issues/2)
[1](https://github.com/cs100/assignment-bcwc/issues/1)

![UML](https://github.com/cs100/assignment-bcwc/blob/master/images/100%20UML(1).png?raw=true)

# Class Description:
Executor class: Has the execute function.

Tokenizer Class: Take user input as a string and returns Component pointer. First it turns split_into_tokens which returns a vector of tokens. Then that vector goes into combine_into_cmds_and_cntrs and returns a vector of component pointers. After that it goes into infx_to_postfix which changes the order of the commands and connectors, then is placed into postfix_to_tree and returns a Component pointer.

RShell Class: It has a member function that runs the command line as an infinite loop until exited. It is essentially in charge of deligating work. 

Component Class: Base to our command, connector, and par class.

Token Class: Making a Token out of a string 

Connector_token Class: "&&", ";" and "||". Used to link commands togther using logic. Base for AND, OR, and SEMI

Command_Token Class: Holds a vector of tokens and uses the "test" command using is_file and is_dir functions. It also runs execute for diffrent commands

Par Class: Returns trues and falses for the logic in Tokenizer

InputRedirect Class: Reads input from a file into the command line

OutputRedirect2 Class: Takes the output of a command and puts it into a file, and won't overwrite the file, but will add to the file everytime the command is ran

OutputRedirect Class: Takes the output of a command and puts it into a file, and will overwrite the file everytime it is ran

Piping Class: Takes the output of a command or program and pipes it into another command or program

