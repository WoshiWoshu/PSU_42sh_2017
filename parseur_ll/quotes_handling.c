/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** quotes handling (used in tokenize.c)
*/

#include <stdio.h>
#include "parser.h"

int handle_quotes(char *content, int *iter, char **cmd)
{
	char quote_type = **cmd;

	++(*cmd);
	while (**cmd != '\0' && **cmd != quote_type) {
		content[*iter] = **cmd;
		++(*iter);
		content[*iter] = '\0';
		++(*cmd);
	}
	if (**cmd != quote_type) {
		dprintf(2, UNMATCHED_CHAR, quote_type);
		return (1);
	} else
		++(*cmd);
	return (0);
}
