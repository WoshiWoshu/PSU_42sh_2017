/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** token test functions
*/

#include "parser.h"

int is_redir(token_type_t type)
{
	if (type == REDIR_RIGHT_DOUBLE
		|| type == REDIR_LEFT_DOUBLE
		|| type == REDIR_RIGHT
		|| type == REDIR_LEFT)
		return (1);
	return (0);
}

int is_pipe_or(token_type_t type)
{
	if (type == PIPE || type == OR)
		return (1);
	return (0);
}

int is_post_arg_and_not_null(token_t **tokens)
{
	if ((*tokens) != NULL
		&& ((*tokens)->type == CMD_ARG
			|| (*tokens)->type == REDIR_ARG
			|| is_redir((*tokens)->type)))
		return (1);
	return (0);
}
