/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** arg_until_str
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "shell.h"

int recover_std(int pipefd[2], binary_tree_t *tree, bool check, char ***env)
{
	int save_stdin;
	int ret = 0;

	save_stdin = dup(0);
	close(pipefd[1]);
	dup2(pipefd[0], 0);
	close(pipefd[0]);
	if (!check)
		ret = execute_line(tree->right, env);
	else
		ret = execute_line(tree->left, env);
	dup2(save_stdin, 0);
	close(save_stdin);
	return (ret);
}

void write_output(char *end)
{
	size_t size = 0;
	int n = 0;
	char *buffer = NULL;

	do {
		write(1, "? ", 2);
		n = getline(&buffer, &size, stdin);
		write(2, buffer, strlen(buffer));
		if (n != -1 && buffer != NULL)
			buffer[n - 1] = '\0';
	} while (buffer != NULL && n != -1 && strcmp(buffer, end));
	exit(0);
}

int tmp_arg(binary_tree_t *tree, char ***env)
{
	int pipefd[2];
	int pid;
	int ret = 0;

	if (pipe(pipefd) == -1)
		return (84);
	pid = fork();
	if (pid == 0) {
		close(pipefd[0]);
		dup2(pipefd[1], 2);
		close(pipefd[1]);
		write_output(tree->right->content[0]);
	} else {
		wait(0);
		ret = recover_std(pipefd, tree, 1, env);
	}
	return (ret);
}
