/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** fonction to detect precedence
*/

#include "parser.h"

static int is_precence1(token_type_t type)
{
	for (int i = 0; i < NB_P1; ++i) {
		if (type == PRECEDENCE_1[i])
			return (1);
	}
	return (0);
}

static int is_precence2(token_type_t type)
{
	for (int i = 0; i < NB_P2; ++i) {
		if (type == PRECEDENCE_2[i])
			return (1);
	}
	return (0);
}

static int is_precence3(token_type_t type)
{
	for (int i = 0; i < NB_P3; ++i) {
		if (type == PRECEDENCE_3[i])
			return (1);
	}
	return (0);
}

static int is_precence4(token_type_t type)
{
	for (int i = 0; i < NB_P4; ++i) {
		if (type == PRECEDENCE_4[i])
			return (1);
	}
	return (0);
}

int get_precedence(token_type_t type)
{
	if (is_precence1(type))
		return (1);
	if (is_precence2(type))
		return (2);
	if (is_precence3(type))
		return (3);
	if (is_precence4(type))
		return (4);
	return (100);
}
