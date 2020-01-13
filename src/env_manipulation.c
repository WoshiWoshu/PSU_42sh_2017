/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** environement manipulation
*/

#include <stdlib.h>
#include <string.h>
#include "shell.h"

int array_size(char *const array[])
{
	int size = 0;

	while (array[size] != NULL)
		size++;
	return (size + 1);
}

char *change_env(char *env_var, char *const arg[], int len)
{
	int size = 0;
	char *dest;

	if (arg[2] != NULL)
		size = strlen(arg[2]);
	dest = malloc(sizeof(char) * (len + size + 2));
	if (dest == NULL)
		exit(84);
	strncpy(dest, env_var, len);
	dest[len] = '=';
	dest[len + 1] = '\0';
	if (size != 0)
		strcat(dest, arg[2]);
	return (dest);
}

char **add_env(char **envp, char *const arg[], int len)
{
	int size = array_size(envp) + 1;
	char **dest = malloc(sizeof(char *) * size);
	int i = 0;

	while (envp[i] != NULL) {
		dest[i] = strdup(envp[i]);
		i++;
	}
	size = 0;
	if (arg[2] != NULL)
		size = strlen(arg[2]);
	dest[i] = malloc(sizeof(char) * (len + size + 2));
	strncpy(dest[i], arg[1], len);
	dest[i][len] = '=';
	dest[i][len + 1] = '\0';
	if (size != 0)
		strcat(dest[i], arg[2]);
	dest[i + 1] = NULL;
	return (dest);
}

char **remoove_env(char **envp, int place)
{
	int size = array_size(envp) - 1;
	char **dest = malloc(sizeof(char *) * size);
	int i = 0;
	int j = 0;

	while (envp[i] != NULL) {
		if (i != place) {
			dest[j] = strdup(envp[i]);
			j++;
		}
		i++;
	}
	dest[j] = NULL;
	return (dest);
}

char **give_array(char **array)
{
	int size = array_size(array);
	char **dest = malloc(sizeof(char *) * size);
	int i = 0;

	while (array[i] != NULL) {
		dest[i] = strdup(array[i]);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}
