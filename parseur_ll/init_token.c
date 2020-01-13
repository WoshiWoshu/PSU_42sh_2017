/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** tokenize
*/

#include <stdlib.h>
#include <string.h>
#include "parser.h"

static int return_if_op(char *cmd)
{
	for (int i = 0; i < OP_COUNT; ++i) {
		if (strncmp(STR_TOKEN_OP[i], cmd,
				strlen(STR_TOKEN_OP[i])) == 0)
			return (i);
	}
	return (-1);
}

int init_token_value_sub(token_t *tokens)
{
	if (tokens->previous != NULL
				&& (tokens->previous->type == REDIR_LEFT
				|| tokens->previous->type == REDIR_RIGHT
				|| tokens->previous->type == REDIR_RIGHT_DOUBLE
				|| tokens->previous->type == REDIR_LEFT_DOUBLE))
				return (REDIR_ARG);
			else if (tokens->previous == NULL
				|| (tokens->previous->type != CMD
				&& tokens->previous->type != CMD_ARG
				&& tokens->previous->type != REDIR_ARG))
				return (CMD);
			else
				return (CMD_ARG);
}

int init_token_value(token_t *tokens)
{
	int op_val = 0;

	while (tokens != NULL) {
		op_val = return_if_op(tokens->content);
		if (op_val != -1)
			tokens->type = op_val;
		else {
			tokens->type = init_token_value_sub(tokens);
		}
		tokens = tokens->next;
	}
	return (0);
}