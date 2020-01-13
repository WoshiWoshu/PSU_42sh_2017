/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** add fonction fort linked list
*/

#include <stdlib.h>
#include "parser.h"

int add_token(token_t **list, char *content)
{
	token_t *tmp = *list;
	token_t *new_node = malloc(sizeof(token_t));

	if (new_node == NULL)
		return (84);
	new_node->content = content;
	new_node->next = NULL;
	if (*list == NULL) {
		new_node->previous = NULL;
		*list = new_node;
		return (0);
	}
	while ((*list)->next != NULL)
		(*list) = (*list)->next;
	(*list)->next = new_node;
	new_node->previous = (*list);
	(*list) = tmp;
	return (0);
}
