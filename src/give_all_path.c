/*
** EPITECH PROJECT, 2018
** give path
** File description:
** give path
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

static int find_path_env(char **env)
{
	int i = 0;

	while (env[i] != NULL && strncmp(env[i], "PATH=", 5) != 0) {
		i++;
	}
	if (env[i] == NULL)
		return (-1);
	return (i);
}

static int separ_path(char *envp)
{
	int ret = 1;

	for (int i = 5; envp[i] != '\0'; i++) {
		if (envp[i] == ':')
			ret++;
	}
	return (ret);
}

static char *count_char_arg(char *str, int *i)
{
	int tmp = *i;
	char *dest;
	int j = 0;

	while (str[tmp] != ':' && str[tmp] != '\0')
		tmp++;
	dest = malloc(sizeof(char) * ((tmp - *i) + 2));
	if (dest == NULL)
		exit(84);
	while (str[*i] != ':' && str[*i] != '\0') {
		dest[j] = str[*i];
		j++;
		*i = *i + 1;
	}
	dest[j] = '\0';
	return (dest);
}

char **give_all_path(char **env)
{
	int p = find_path_env(env);
	char **tab;
	int j = 1;

	if (p == -1)
		tab = malloc(sizeof(char) * 2);
	else
		tab = malloc(sizeof(char *) * (separ_path(env[p]) + 2));
	if (tab == NULL)
		exit(84);
	tab[0] = malloc(sizeof(char) * 2);
	tab[0][0] = '\0';
	for (int i = 5; p != -1 && env[p][i - 1] != '\0' \
&& env[p][i] != '\0'; i++) {
		tab[j] = count_char_arg(env[p], &i);
		j++;
	}
	tab[j] = NULL;
	return (tab);
}
