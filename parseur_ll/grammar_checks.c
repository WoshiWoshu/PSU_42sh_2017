/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** grammar checks
*/

#include <stdio.h>
#include "parser.h"

//	Returns 1 if no CMD_ARG found, 0 if found.
//	When it finds a CMD_ARG after the redirection,
//	it places it before the redirection as a CMD.
static int check_cmd_after_redir(token_t *tokens)
{
	token_t *tmp;

	if (tokens->next != NULL && tokens->next->next != NULL
		&& tokens->next->next->type == CMD_ARG) {
		tmp = tokens->next->next;
		if (tokens->next->next->next != NULL)
			tokens->next->next->next->previous = tokens->next;
		tokens->next->next = tokens->next->next->next;
		if (tokens->previous != NULL)
			tokens->previous->next = tmp;
		tmp->previous = tokens->previous;
		tmp->next = tokens;
		tokens->previous = tmp;
		tmp->type = CMD;
		return (0);
	}
	return (1);
}

int check_redir(token_t *tokens)
{
	if (tokens->next == NULL || tokens->next->type != REDIR_ARG) {
		dprintf(2, MISSING_REDIR_NAME);
		return (1);
	}
	if (check_ambiguous_redir(tokens))
		return (1);
	if ((tokens->previous == NULL
		|| (tokens->previous->type != CMD
			&& tokens->previous->type != CMD_ARG))
		&& check_cmd_after_redir(tokens)) {
		dprintf(2, INVALID_NULL_CMD);
		return (1);
	}
	return (0);
}

int check_and(token_t *tokens)
{
	if (tokens->type == AND) {
		if (tokens->previous != NULL
			&& (tokens->previous->type == CMD
				|| tokens->previous->type == CMD_ARG
				|| tokens->previous->type == REDIR_ARG)
			&& (tokens->next == NULL
				|| (tokens->next->type != CMD
				&& is_redir(tokens->next->type) == 0))) {
			dprintf(2, INVALID_NULL_CMD);
			return (1);
		}
	}
	return (0);
}
