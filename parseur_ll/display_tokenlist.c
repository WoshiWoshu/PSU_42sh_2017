/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** displaying token linked list
*/

#include <stdlib.h>
#include <stdio.h>
#include "parser.h"

void display_without_token_type(token_t *list)
{
	while (list != NULL) {
		printf("content = %s\n", list->content);
		list = list->next;
	}
}

void display_with_token_type(token_t *list)
{
	while (list != NULL) {
		printf("content = %s ", list->content);
		printf("token = %d\n", list->type);
		list = list->next;
	}
}
