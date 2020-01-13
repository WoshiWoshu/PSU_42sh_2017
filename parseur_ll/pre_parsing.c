/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** pre_parsing
*/

#include <stdlib.h>
#include <string.h>
#include "parser.h"

static int get_size(token_t *tokens)
{
	int size = 0;

	tokens = tokens->next;
	while (tokens != NULL
		&& (tokens->type == CMD_ARG
			|| tokens->type == REDIR_ARG
			|| is_redir(tokens->type))) {
		if (tokens->type == CMD_ARG)
			size++;
	tokens= tokens->next;
	}
	return (size);
}

static int get_arg(token_t **tokens)
{
	token_t *tmp = *tokens;
	int count = 0;
	int size = get_size(*tokens) + 1;

	tmp->cmd_arg = malloc(sizeof(char *) * (size + 1));
	if (tmp->cmd_arg == NULL)
		return (84);
	tmp->cmd_arg[size] = NULL;
	tmp->cmd_arg[count++] = strdup((*tokens)->content);
	(*tokens) = (*tokens)->next;
	while (count != size && is_post_arg_and_not_null(tokens)) {
		if ((*tokens)->type == CMD_ARG) {
			tmp->cmd_arg[count++] = strdup((*tokens)->content);
			free_token(tokens);
		} else
			*tokens = (*tokens)->next;
	}
	*tokens = tmp;
	return (0);
}

int pre_parsing(token_t **tokens)
{
	token_t *tmp = *tokens;

	while ((*tokens) != NULL) {
		if ((*tokens)->type == CMD) {
			get_arg(tokens);
		}
		*tokens = (*tokens)->next;
	}
	*tokens = tmp;
	return (0);
}
