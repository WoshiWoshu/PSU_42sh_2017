/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** moves binarytree ptr to the a node with an inferior or equal precedence.
*/

#include <stdlib.h>
#include "parser.h"

//eventually put it directly in create_tree.c
void goto_precedence_n(binary_tree_t **bintree, int n)
{
	if (*bintree == NULL)
		return;
	while ((*bintree)->parent != NULL
		&& get_precedence((*bintree)->parent->type) >= n) {
		(*bintree) = (*bintree)->parent;
	}
}
