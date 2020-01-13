/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** display_binary_tree
*/

#include <stdio.h>
#include "parser.h"

static void recursive_display(binary_tree_t *bintree, int spaces)
{
	if (bintree == NULL)
		return;
	spaces += 6;
	recursive_display(bintree->right, spaces);
	printf("\n");
	for (int i = 6; i < spaces; i++)
		printf(" ");
	printf("%s\n", bintree->content[0]);
	recursive_display(bintree->left, spaces);
}

void display_binary_tree(binary_tree_t *bintree)
{
	recursive_display(bintree, 0);
}
