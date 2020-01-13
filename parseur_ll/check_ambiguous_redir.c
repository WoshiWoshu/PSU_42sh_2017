/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** grammar check
*/

#include "parser.h"

static int is_same_redir_type(token_type_t type1, token_type_t type2)
{
	if (type1 == REDIR_RIGHT || type1 == REDIR_RIGHT_DOUBLE) {
		if (type2 == REDIR_RIGHT || type2 == REDIR_RIGHT_DOUBLE) {
			dprintf(2, AMBIGUOUS_OUTPUT);
			return (84);
		}
	}
	else if ((type1 == REDIR_LEFT || type1 == REDIR_LEFT_DOUBLE)) {
		if (type2 == REDIR_LEFT || type2 == REDIR_LEFT_DOUBLE) {
			dprintf(2, AMBIGUOUS_INPUT);
			return (84);
		}
	}
	return (0);
}

int check_ambiguous_redir(token_t *tokens)
{
	token_type_t type = tokens->type;

	tokens = tokens->next;
	while (tokens != NULL && (tokens->type == CMD_ARG
		|| is_redir(tokens->type) || tokens->type == REDIR_ARG)) {
		if (is_same_redir_type(type, tokens->type)){
			return (84);
		}
		tokens = tokens->next;
	}
	return (0);
}
