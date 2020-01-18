# PSU_42sh_2017
First year project in C based on PSU_minishell_2017.
It consist of being an advanced Unix Shell handling several commands such as cd, echo, cat, wc, grep, setenv, unsetenv...
In addition, it can also handle redirections(‘<’,‘>’,‘<<’and‘>>’), pipes(‘|’), separators (‘;’,‘&&;’,‘||’) and $PATH environment.
The redirections, pipes and separators are built using a Ternary tree.

USAGE :

    Make

    ./42sh

EXEMPLE :

    $> echo "My name is" > test.txt && echo "Yoshi\n" >> test.txt && cat test.txt ; ls
