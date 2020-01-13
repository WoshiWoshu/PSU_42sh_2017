/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** built in
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "shell.h"

static int print_all_env(char **envp)
{
	for (int i = 0; envp[i] != NULL; i++)
		puts(envp[i]);
	return (2);
}

static char **setenv_function(char *const arg[], char **envp, int *ret)
{
	int i = 0;

	if (array_size(arg) > 4) {
		write(2, "setenv: Too many arguments\n", 27);
	} else if (array_size(arg) != 2) {
		if (my_str_isalphanum(arg[1]) == 0) {
			write(2, "setenv: Variable name must contain \
alphanumeric characters.\n", 60);
			return (envp);
		}
		for (i = 0; envp[i] != NULL && strncmp(envp[i], arg[1], \
strlen(arg[1])) != 0; ++i);
		if (envp[i] != NULL)
			envp[i] = change_env(envp[i], arg, strlen(arg[1]));
		else
			envp = add_env(envp, arg, strlen(arg[1]));
	} else
		*ret = print_all_env(envp);
	return (envp);
}

static char **unsetenv_function(char *const arg[], char **envp)
{
	int i = 0;
	int len = 0;

	if (arg[1] == NULL) {
		write(2, "unsetenv: Too few arguments.\n", 29);
		return (envp);
	}
	for (int j = 1; arg[j] != NULL; j++) {
		len = strlen(arg[j]);
		while (envp[i] != NULL && strncmp(envp[i], arg[j], len) != 0)
			i++;
		if (envp[i] != NULL && my_str_isalphanum(arg[j]) == 1)
			envp = remoove_env(envp, i);
	}
	return (envp);
}

int built_in_function(char *const arg[], char ***env)
{
	int ret = 1;

	if (strcmp(arg[0], "exit") == 0) {
		write(1, "exit\n", 5);
		exit(0);
	} else if (strcmp(arg[0], "cd") == 0) {
		return (1);
	} else if (strcmp(arg[0], "env") == 0) {
		print_all_env(*env);
		return (2);
	}
	if (strcmp(arg[0], "setenv") == 0) {
		*env = setenv_function(arg, *env, &ret);
		return (ret);
	} else if (strcmp(arg[0], "unsetenv") == 0) {
		*env = unsetenv_function(arg, *env);
		return (1);
	}
	return (0);
}
