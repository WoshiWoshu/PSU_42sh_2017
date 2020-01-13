/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** separ instruct
*/

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include "shell.h"

int error_open(char *file, int error)
{
	write(2, file, strlen(file));
	if (error == 13)
		write(2, ": Permission denied.\n", 20);
	else if (error == 2)
		write(2, ": No such file or directory.\n", 29);
	return (84);
}

int pipe_function(binary_tree_t *tree, char ***env)
{
	int pipefd[2];
	int pid;
	int ret = 0;

	if (pipe(pipefd) == -1)
		return (0);
	pid = fork();
	if (pid == 0) {
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		exit(execute_line(tree->left, env));
	} else {
		ret = recover_std(pipefd, tree, 0, env);
		wait(0);
	}
	return (ret);
}

int in_file(binary_tree_t *tree, char ***env)
{
	int fd = -1;
	int ret = 0;
	int save_stdout;

	if (tree->right == NULL) {
		write(2, "Missing name for redirect.\n", 27);
		return (84);
	}
	fd = open(tree->right->content[0], O_WRONLY | O_CREAT |
	O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (fd == -1)
		return (error_open(tree->right->content[0], errno));
	save_stdout = dup(1);
	dup2(fd, 1);
	close(fd);
	ret = execute_line(tree->left, env);
	dup2(save_stdout, 1);
	close(save_stdout);
	return (ret);
}

int at_end_of_file(binary_tree_t *tree, char ***env)
{
	int fd = -1;
	int ret = 0;
	int save_stdout;

	if (tree->right == NULL) {
		write(2, "Missing name for redirect.\n", 27);
		return (84);
	}
	fd = open(tree->right->content[0], O_WRONLY | O_CREAT |
	O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (fd == -1)
		return (error_open(tree->right->content[0], errno));
	save_stdout = dup(1);
	dup2(fd, 1);
	close(fd);
	ret = execute_line(tree->left, env);
	dup2(save_stdout, 1);
	close(save_stdout);
	return (ret);
}

int in_arg(binary_tree_t *tree, char ***env)
{
	int fd = -1;
	int ret = 0;
	int save_stdout;

	errno = 0;
	if (tree->right == NULL) {
		write(2, "Missing name for redirect.\n", 27);
		return (84);
	}
	fd = open(tree->right->content[0], O_RDONLY);
	if (fd == -1)
		return (error_open(tree->right->content[0], errno));
	save_stdout = dup(1);
	dup2(fd, 0);
	close(fd);
	ret = execute_line(tree->left, env);
	dup2(save_stdout, 1);
	close(save_stdout);
	return (ret);
}
