/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** parser tree creation
*/

#include <stdlib.h>
#include <string.h>
#include "parser.h"

static void check_cmd_arg_malloc(char **cmd_arg)
{
	if (cmd_arg == NULL)
		exit(84);
}

void move_content(token_t **tokens)
{
	token_t *tmp = *tokens;
	while (*tokens != NULL) {
		if ((*tokens)->type != CMD) {
			(*tokens)->cmd_arg = malloc(sizeof(char *) * 2);
			check_cmd_arg_malloc((*tokens)->cmd_arg);
			(*tokens)->cmd_arg[0] = strdup((*tokens)->content);
			(*tokens)->cmd_arg[1] = NULL;
		}
		(*tokens) = (*tokens)->next;
	}
	*tokens = tmp;
}
