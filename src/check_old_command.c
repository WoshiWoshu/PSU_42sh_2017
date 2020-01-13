/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** check old command
*/

#include <unistd.h>
#include "shell.h"

int separ_instruct(binary_tree_t *tree, char ***env)
{
	execute_line(tree->left, env);
	execute_line(tree->right, env);
	return (0);
}

int true_old_command(binary_tree_t *tree, char ***env)
{
	int ret = 1;

	if (tree->left == NULL)
		return (0);
	if (tree->right == NULL) {
		write(2, "Invalid null command.\n", 22);
		return (84);
	}
	if (!execute_line(tree->left, env))
		ret = execute_line(tree->right, env);
	return (ret);
}

int false_old_command(binary_tree_t *tree, char ***env)
{
	int ret = 0;

	if (execute_line(tree->left, env))
		ret = execute_line(tree->right, env);
	return (ret);
}
