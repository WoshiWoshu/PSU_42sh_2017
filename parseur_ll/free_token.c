/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** pre_parsing
*/

#include <stdlib.h>
#include <string.h>
#include "parser.h"

static void free_token_last(token_t **tokens)
{
	token_t *tmp = *tokens;

	tmp = (*tokens)->previous;
	free((*tokens)->content);
	free((*tokens));
	*tokens = tmp;
	(*tokens)->next = NULL;
}

static void free_token_first(token_t **tokens)
{
	token_t *tmp = *tokens;

	tmp = (*tokens)->next;
	free((*tokens)->content);
	free((*tokens));
	*tokens = tmp;
	(*tokens)->previous = NULL;
}

void free_token(token_t **tokens)
{
	token_t *tmp = *tokens;

	if ((*tokens)->previous == NULL && (*tokens)->previous == NULL) {
		free((*tokens)->content);
		free(*tokens);
		*tokens = NULL;
		return;
	}
	if ((*tokens)->previous == NULL) {
		return (free_token_first(tokens));
	}
	if ((*tokens)->next == NULL) {
		return (free_token_last(tokens));
	}
	(*tokens)->previous->next = (*tokens)->next;
	(*tokens)->next->previous = (*tokens)->previous;
	tmp = (*tokens)->next;
	free((*tokens)->content);
	free((*tokens));
	*tokens = tmp;
}

void free_list(token_t *list)
{
	token_t *tmp = list;

	while (tmp != NULL) {
		free(tmp->content);
		tmp = list->next;
		free(list);
		list = tmp;
	}
}
