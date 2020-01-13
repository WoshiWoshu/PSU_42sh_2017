/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** temporary main for testing parser implementation
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

binary_tree_t *parseur_ll(char *str)
{
	token_t *tokens = NULL;
	binary_tree_t *tree = NULL;

	if (lexer(str, &tokens))
		return (NULL);
	pre_parsing(&tokens);
	move_content(&tokens);
	tree = create_tree(tokens);
	free_list(tokens);
	free(str);
	return (tree);
}
