/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** parser tree creation
*/

#include "parser.h"

static void add_precedence(binary_tree_t **tree, token_t *tokens,
				int precedence)
{
	goto_precedence_n(tree, precedence);
	add_node_parent(tree, tokens->cmd_arg, tokens->type);
}

static void add_instruct(binary_tree_t **tree, token_t *tokens)
{
	int precedence = get_precedence(tokens->type);

	if (tokens->type == CMD || tokens->type == REDIR_ARG) {

		if ((*tree)->left == NULL)
			add_node_left(tree, tokens->cmd_arg, tokens->type);
		else
			add_node_right(tree, tokens->cmd_arg, tokens->type);
		return;
	}
	add_precedence(tree, tokens, precedence);
}

binary_tree_t *create_tree(token_t *tokens)
{
	binary_tree_t *tree;

	tree = create_bintree_node(tokens->cmd_arg, tokens->type);
	tokens = tokens->next;
	while (tokens != NULL) {
		add_instruct(&tree, tokens);
		tokens = tokens->next;
	}
	free_list(tokens);
	goto_root(&tree);
	return (tree);
}
