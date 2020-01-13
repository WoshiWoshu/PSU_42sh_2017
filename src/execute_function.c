/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** execute command
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

void write_status_info(int status)
{
	if (WIFSIGNALED(status)) {
		if (WTERMSIG(status) == 11)
			write(2, "Segmentation fault", 18);
		else if (WTERMSIG(status) == 6)
			write(2, "Abort", 5);
		else if (WTERMSIG(status) == 8)
			write(2, "Floating exception", 18);
		if (WCOREDUMP(status))
			write(2, " (core dumped)", 14);
		if (WTERMSIG(status) != 9)
			write(2, "\n", 1);
	}
}

static int check_access(char *str, char *path)
{
	int size = strlen(str) + strlen(path) + 2;
	char *fil = malloc(sizeof(char) * size);
	int i = 0;
	int ret = 0;

	if (fil == NULL)
		return (-1);
	for (int j = 0; path[j] != '\0'; j++)
		fil[i++] = path[j];
	if (i != 0)
		fil[i++] = '/';
	for (int j = 0; str[j] != '\0'; j++)
		fil[i++] = str[j];
	fil[i] = '\0';
	ret = access(fil, F_OK);
	if (ret != -1 && access(fil, X_OK) == -1) {
		write(2, fil, strlen(fil));
		write(2, ": Permission denied.\n", 21);
	} free(fil);
	return (ret);
}

static void execute_command(char *arg[], char *path, char **env)
{
	int size = strlen(arg[0]) + strlen(path) + 2;
	char *fil = malloc(sizeof(char) * size);
	int i = 0;

	if (fil == NULL)
		exit(84);
	for (int j = 0; path[j] != '\0'; j++)
		fil[i++] = path[j];
	if (i != 0)
		fil[i++] = '/';
	for (int j = 0; arg[0][j] != '\0'; j++)
		fil[i++] = arg[0][j];
	fil[i] = '\0';
	if (execve(fil, arg, env) == -1)
		execve(arg[0], arg, env);
	write(2, fil, strlen(fil));
	if (errno == 8)
		write(2, ": Exec format error. Wrong Architecture.\n", 41);
	else
		write(2, ": Permission denied.\n", 21);
	kill((int) getpid(), SIGKILL);
}

static int do_command(char *arg[], char *path, char **env)
{
	pid_t pid;
	int status = 0;

	pid = fork();
	if (pid == 0)
		execute_command(arg, path, env);
	else
		wait(&status);
	write_status_info(status);
	return (status);
}

int check_built_function(char *arg[], char ***env)
{
	int i = 0;
	char **path = give_all_path(*env);
	int ret = 0;

	if (strcmp(arg[0], "cd") == 0)
		ret = change_dir(arg[1], *env);
	if (built_in_function(arg, env) == 0) {
		while (path[i] != NULL \
&& check_access(arg[0], path[i]) == -1)
			i++;
		if (path[i] == NULL) {
			write(2, arg[0], strlen(arg[0]));
			write(2, ": Command not found.\n", 21);
			ret = 1;
		} else
			ret = do_command(arg, path[i], *env);
	}
	for (int i = 0; path[i] != NULL; i++)
		free(path[i]);
	free(path);
	return (ret);
}
