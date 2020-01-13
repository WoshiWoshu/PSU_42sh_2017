/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** execute_line
*/

#include <stdio.h>
#include "shell.h"

int execute_line(binary_tree_t *tree, char ***env)
{
	int ret = 0;
	int (*direction[]) (binary_tree_t *tree, char ***env) = {
		false_old_command,
		pipe_function,
		true_old_command,
		separ_instruct,
		at_end_of_file,
		tmp_arg,
		in_arg,
		in_file
	};

	if (tree->type == CMD)
		ret = check_built_function(tree->content, env);
	else
		ret = direction[tree->type](tree, env);
	return (ret);
}
