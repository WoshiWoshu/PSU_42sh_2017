/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** temporary main for testing parser implementation
*/

#include <stdlib.h>
#include <string.h>
#include "parser.h"

static char **copy_content(char **content)
{
	int size = 0;
	char **copy;
	int str_len = 0;

	for (size = 0; content[size] != NULL; ++size);
	copy = malloc(sizeof(char *) * (size + 1));
	if (copy == NULL)
		exit(84);
	copy[size] = NULL;
	for (int i = 0; i < size; ++i) {
		str_len = strlen(content[i]);
		copy[i] = malloc(sizeof(char) * (str_len + 1));
		if (copy[i] == NULL)
			exit(84);
		strcpy(copy[i], content[i]);
	}
	return (copy);
}

binary_tree_t *create_bintree_node(char **content, token_type_t type)
{
	binary_tree_t *node = malloc(sizeof(binary_tree_t));

	if (node == NULL)
		exit(84);
	node->content = copy_content(content);
	node->type = type;
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void add_node_left(binary_tree_t **bintree, char **content, token_type_t type)
{
	binary_tree_t *new_left_node = create_bintree_node(content, type);

	new_left_node->parent = *bintree;
	(*bintree)->left = new_left_node;
	*bintree = (*bintree)->left;
}

void add_node_right(binary_tree_t **bintree, char **content, token_type_t type)
{
	binary_tree_t *new_right_node = create_bintree_node(content, type);

	new_right_node->parent = *bintree;
	(*bintree)->right = new_right_node;
	*bintree = (*bintree)->right;
}

//	/!\ The current node will be the left child.
void add_node_parent(binary_tree_t **bintree, char **content, token_type_t type)
{
	binary_tree_t *new_parent_node = create_bintree_node(content, type);

	if ((*bintree)->parent == NULL) {
		(*bintree)->parent = new_parent_node;
		new_parent_node->left = (*bintree);
	} else {
		if ((*bintree)->parent->right == (*bintree))
			(*bintree)->parent->right = new_parent_node;
		else
			(*bintree)->parent->left = new_parent_node;
		new_parent_node->left = (*bintree);
		new_parent_node->parent = (*bintree)->parent;
		(*bintree)->parent = new_parent_node;
	}
	*bintree = (*bintree)->parent;
}
