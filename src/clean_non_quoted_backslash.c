/*
** EPITECH PROJECT, 2018
** clean_non_quoted_backslash.c
** File description:
** Handle non-quoted backslashes in a command
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>

static const char	BACKSLASH_G = '\\';
static const char	NEW_LINE_G = '\n';
static const char	DOUBLE_QUOTE_G = '\"';

static char	*ask_for_new_command(void)
{
	char	*cmd = calloc(pow(10, 6), sizeof(char));
	int	last_char_idx = 0;
	size_t	n = pow(10, 6);

	if (cmd == NULL)
		return (NULL);
	if (write(STDOUT_FILENO, "? ", 2) == -1)
		return (NULL);
	getline(&cmd, &n, stdin);
	if (cmd == NULL)
		return (strdup("\0"));
	else if (cmd[0] == '\0')
		return (cmd);
	last_char_idx = strlen(cmd) - 1;
	if (cmd[last_char_idx] == NEW_LINE_G)
		memmove(&cmd[last_char_idx],
			&cmd[last_char_idx + 1],
			strlen(cmd) - last_char_idx);
	return (cmd);
}

static char	*handle_backslash_as_last_character_of_str(char *str, int i)
{
	char	*command = NULL;

	memmove(&str[i], &str[i + 1], strlen(str) - i);
	command = ask_for_new_command();
	if (command == NULL)
		return (NULL);
	str = realloc(str, strlen(str) + strlen(command) + 1);
	if (str == NULL) {
		fprintf(stderr, "Malloc ERR\n");
		return (NULL);
	}
	str = strcat(str, command);
	free(command);
	return (str);
}

static bool	is_inside_quote(char *str, int character_index)
{
	bool	inside_quote = false;

	for (int i = 0; str[i] != '\0'; ++i) {
		if (str[i] == DOUBLE_QUOTE_G && inside_quote)
			inside_quote = false;
		else if (str[i] == DOUBLE_QUOTE_G)
			inside_quote = true;
		if (i == character_index && inside_quote)
			return (true);
	}
	return (false);
}

/*
** Argument is the user's command
** Returns NULL when errors occur
*/
char	*clean_non_quoted_backslash(char *str)
{
	for (int i = 0; str[i] != '\0'; ++i) {
		if (str[i] == BACKSLASH_G && str[i + 1] != '\0'
		&& !is_inside_quote(str, i)) {
			memmove(&str[i], &str[i + 1], strlen(str) - i);
			i = 0;
		}
		else if (str[i] == BACKSLASH_G && str[i + 1] == '\0'
		&& !is_inside_quote(str, i)) {
			str = handle_backslash_as_last_character_of_str(str, i);
			i = 0;
		}
		if (str == NULL)
			return (NULL);
	}
	return (str);
}
