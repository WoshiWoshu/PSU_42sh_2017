# PSU_42sh_2017
First year project in C based on PSU_minishell_2017. It consist of being an advanced Unix Shell handling several commands such as cd, echo, cat, wc, grep, setenv, unsetenv etc...
It can also handle redirections(‘<’,‘>’,‘<<’and‘>>’), pipes(‘|’), separators (‘;’,‘&&;’,‘||’) and $PATH environment.
The redirections, pipes, separators are built using a Ternary tree.

USAGE :

1) Make

2) ./42sh

3) > echo "My name is" > test.txt && echo "Yoshi\n" >> test.txt && cat test.txt ; ls
