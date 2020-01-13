/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** tokenize
*/

#include <stdlib.h>
#include <string.h>
#include "parser.h"

static int is_an_op(char *cmd)
{
	for (int i = 0; i < OP_COUNT; ++i) {
		if (strncmp(STR_TOKEN_OP[i], cmd,
				strlen(STR_TOKEN_OP[i])) == 0)
			return (1);
	}
	return (0);
}

//	this only works because operators are in an order such that multiple
//	character operators are firsts.
static void cpy_op(char *content, char **cmd)
{
	int size_op = 0;

	for (int i = 0; i < OP_COUNT; ++i) {
		size_op = strlen(STR_TOKEN_OP[i]);
		if (strncmp(STR_TOKEN_OP[i], *cmd, size_op) == 0)
			break;
	}
	strncpy(content, *cmd, size_op);
	content[size_op] = '\0';
	*cmd += size_op;
}

//	this may seem like a strange way of doing things
//	it is because it takes into consideration the possibility of quotes
//	without any blank separations.
static	int cpy_cmd(char *content, char **cmd)
{
	int iter = 0;

	while (**cmd != '\0' && is_an_op(*cmd) == 0
		&& **cmd != ' ' && **cmd != '\t') {
		if ((**cmd == '"' || **cmd == '\'')
			&& handle_quotes(content, &iter, cmd))
			return (1);
		content[iter++] = **cmd;
		content[iter] = '\0';
		++(*cmd);
	}
	return (0);
}

//	cpy op and cpy cmd are 2 different operations because operators and cmd
//	may not be separated with any blank.
static int get_token(char **cmd, token_t **tokens)
{
	char *content;

	if (**cmd == '\0')
		return (0);
	content = malloc(sizeof(char) * (strlen(*cmd) + 1));
	if (content == NULL)
		exit_tokenize(*tokens);
	while (**cmd == ' ' || **cmd == '\t')
		++(*cmd);
	if (**cmd == '\0') {
		free(content);
		return (0);
	}
	if (is_an_op(*cmd))
		cpy_op(content, cmd);
	else if (cpy_cmd(content, cmd))
		return (2);
	add_token(tokens, content);
	return (1);
}

int tokenize(char *cmd, token_t **tokens)
{
	int check_get_token = 1;

	while (check_get_token == 1)
		check_get_token = get_token(&cmd, tokens);
	if (check_get_token == 2)
		return (1);
	init_token_value(*tokens);
	return (0);
}
