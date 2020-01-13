/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** grammar check
*/

#include "parser.h"

static int check_first(token_t *tokens)
{
	if (tokens->type != SEMICOL && tokens->type != CMD
		&& tokens->type != AND && is_redir(tokens->type) == 0) {
		dprintf(2, INVALID_NULL_CMD);
		return (1);
	}
	return (0);
}

static int check_current(token_t *tokens)
{
	if (tokens->type == SEMICOL) {
		if (tokens->next != NULL && check_first(tokens->next)) {
			dprintf(2, INVALID_NULL_CMD);
			return (1);
		}
		return (0);
	}
	if (is_redir(tokens->type) && check_redir(tokens))
		return (1);
	if (is_pipe_or(tokens->type)
		&& (tokens->next == NULL
			|| (tokens->next->type != CMD
				&& is_redir(tokens->next->type) == 0))) {
		dprintf(2, INVALID_NULL_CMD);
		return (1);
	}
	if (check_and(tokens))
		return (1);
	return (0);
}

int verify_grammar(token_t *tokens)
{
	if (check_first(tokens))
		return (1);
	while (tokens != NULL) {
		if (check_current(tokens))
			return (1);
		tokens = tokens->next;
	}
	return (0);
}
