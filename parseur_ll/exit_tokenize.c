/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** exit_tokenize
*/

#include <stdlib.h>
#include "parser.h"

void exit_tokenize(token_t *tokens)
{
	free_list(tokens);
	exit(84);
}
