/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** lexer and grammar check
*/

#include <stdlib.h>
#include "parser.h"

int lexer(char *cmd, token_t **tokens)
{
	int grammar_error = 0;

	if (tokenize(cmd, tokens))
		return (1);
	if (tokens == NULL)
		return (0);
	grammar_error = verify_grammar(*tokens);
	while ((*tokens)->previous != NULL)
		(*tokens) = (*tokens)->previous;
	if (grammar_error) {
		free_list(*tokens);
		return (1);
	}
	return (0);
}
