/*
** EPITECH PROJECT, 2018
** PSU_42sh_2017
** File description:
** shell.h
*/

#ifndef SHELL
#define SHELL

#include "parser.h"
#include <stdbool.h>

typedef struct list_t
{
	char *line;
	struct list_t *next;
	struct list_t *previous;
} list_t;

typedef struct alias_t
{
	char *line;
	char *command;
	struct alias_t *next;
} alias_t;

int pipe_function(binary_tree_t *tree, char ***env);
int in_file(binary_tree_t *tree, char ***env);
int at_end_of_file(binary_tree_t *tree, char ***env);
int in_arg(binary_tree_t *tree, char ***env);
int tmp_arg(binary_tree_t *tree, char ***env);
int true_old_command(binary_tree_t *tree, char ***env);
int false_old_command(binary_tree_t *tree, char ***env);
int separ_instruct(binary_tree_t *tree, char ***env);
int recover_std(int pipefd[2], binary_tree_t *tree, bool check, char ***env);

int change_dir(char *path, char **env);
int built_in_function(char *const arg[], char ***env);

int check_built_function(char *arg[], char ***env);

int execute_line(binary_tree_t *tree, char ***env);
int array_size(char *const array[]);

char **give_all_path(char **env);
char *change_env(char *env_var, char *const arg[], int len);
char **add_env(char **envp, char *const arg[], int len);
char **remoove_env(char **envp, int place);

char	*clean_non_quoted_backslash(char *str);

int	my_str_isalphanum(char const *str);

binary_tree_t *parseur_ll(char *str);

#endif //SHELL
