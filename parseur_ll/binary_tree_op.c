/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** operations other than add nodes on binary trees
*/

#include <stdlib.h>
#include "parser.h"

binary_tree_t *get_root(binary_tree_t *bintree)
{
	while (bintree->parent != NULL)
		bintree = bintree->parent;
	return (bintree);
}

void goto_root(binary_tree_t **bintree)
{
	while ((*bintree)->parent != NULL)
		*bintree = (*bintree)->parent;
}

void destroy_tree(binary_tree_t *binary_tree)
{
	if (binary_tree == NULL)
		return;
	destroy_tree(binary_tree->right);
	destroy_tree(binary_tree->left);
	for (int i = 0; binary_tree->content[i]; ++i) {
		free(binary_tree->content[i]);
	}
	free(binary_tree->content);
	free(binary_tree);
}
