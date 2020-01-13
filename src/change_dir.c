/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** change directory
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "shell.h"

int to_home_directory(char **env)
{
	int i = 0;
	int j = 0;
	char *home;

	while (env[i] != NULL && strncmp(env[i], "HOME=", 4) != 0)
		i++;
	if (env[i] == NULL)
		return (84);
	home = malloc(sizeof(char) * strlen(env[i] - 4));
	if (home == NULL)
		return (0);
	while (env[i][j + 5] != '\0') {
		home[j] = env[i][j + 5];
		j++;
	}
	home[j] = '\0';
	chdir(home);
	free(home);
	return (0);
}

int change_to_specific_dir(char *path, int *var, char *old, char *tmp)
{
	if (chdir(path) == -1) {
		write(2, path, strlen(path));
		write(2, ": Not a directory.\n", 19);
		return (1);
	} else {
		*var = 1;
	}
	strcpy(old, tmp);
	return (0);
}

int change_dir(char *path, char **env)
{
	static char old[4096];
	char tmp[4096];
	static int var = 0;
	int ret = 0;

	if (path == NULL || strcmp(path, "~") == 0) {
		getcwd(old, sizeof(old));
		ret = to_home_directory(env);
		var = 1;
	} else if (strcmp(path, "-") == 0) {
		if (var == 1)
			getcwd(tmp, sizeof(tmp));
		chdir(old);
		strcpy(old, tmp);
		var = 1;
	} else {
		getcwd(tmp, sizeof(tmp));
		return (change_to_specific_dir(path, &var, old, tmp));
	}
	return (ret);
}
