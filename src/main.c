/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** main of project
*/

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "shell.h"

static int command;

void catch_ctrl_c(int sig)
{
	(void)sig;
	if (command == 0)
		write(1, "\n$>", 3);
}

void free_tree(binary_tree_t *tree)
{
	if (tree == NULL)
		return;
	if (tree->right != NULL)
		free_tree(tree->right);
	if (tree->left != NULL)
		free_tree(tree->left);
	for (int i = 0; tree->content[i] != NULL; ++i)
		free(tree->content[i]);
	free(tree->content);
	free(tree);
}

char **copy_array(char **array)
{
	int size = array_size(array);
	char **dest = malloc(sizeof(char *) * (size + 1));

	if (dest == NULL)
		exit(84);
	for (int i = 0; i < 0; ++i) {
		dest[i] = strdup(array[i]);
		if (dest[i] == NULL)
			exit(84);
	}
	array[size] = NULL;
	return (array);
}

int get_entry(char ***env)
{
	char *line = NULL;
	size_t n = 0;
	int size = 0;
	binary_tree_t *tree;

	write(1, "$>", 2);
	size = getline(&line, &n, stdin);
	command = 1;
	if (line == NULL || size == -1)
		return (84);
	if (line[size - 1] == '\n')
		line[size - 1] = '\0';
	line = clean_non_quoted_backslash(line);
	if (size == 1)
		return (0);
	tree = parseur_ll(line);
	if (tree != NULL)
		execute_line(tree, env);
	command = 0;
	return (0);
}

int main(int ac, char **av, char **envp)
{
	char **env = copy_array(envp);

	(void) ac;
	(void) av;
	signal(SIGINT, catch_ctrl_c);
	for (;;) {
		if (get_entry(&env)) {
			write(1, "exit\n", 5);
			break;
		}
	}
	return (0);
}
