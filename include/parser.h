/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** parser header file
*/

#include <stdio.h>
#ifndef PARSER_H_
#define PARSER_H_

/*
 * ##########################################################
 * #                         GENERAL ENUM FOR PARSER        #
 * ##########################################################
 */

typedef enum token_type
{
	OR, PIPE, AND, SEMICOL,
	REDIR_RIGHT_DOUBLE, REDIR_LEFT_DOUBLE,
	REDIR_LEFT, REDIR_RIGHT, REDIR_ARG,
	CMD, CMD_ARG
} token_type_t;

/*
 * ##########################################################
 * #                         LEXER STRUCT AND CONST         #
 * ##########################################################
 */

static const char MISSING_REDIR_NAME[] = "Missing name for redirect.\n";
static const char INVALID_NULL_CMD[] = "Invalid null command.\n";
static const char AMBIGUOUS_OUTPUT[] = "Ambiguous output redirect.\n";
static const char AMBIGUOUS_INPUT[] = "Ambiguous input redirect.\n";
static const char UNMATCHED_CHAR[] = "Unmatched '%c'.\n";

//	Is considered an "operator" any of the following tokens.
#define OP_COUNT 8

static const char STR_TOKEN_OP[][OP_COUNT] = {
	"||", "|", "&&", ";", ">>", "<<", "<", ">"
};

typedef struct token_s
{
	char *content;
	char **cmd_arg;
	token_type_t type;
	struct token_s *previous;
	struct token_s *next;
} token_t;

/*
 * ##########################################################
 * #                         PARSER STRUCT AND CONST        #
 * ##########################################################
 */

#define NB_P1 1
#define NB_P2 2
#define NB_P3 1
#define NB_P4 4

static const token_type_t PRECEDENCE_1[NB_P1] = {SEMICOL};

static const token_type_t PRECEDENCE_2[NB_P2] = {AND, OR};

static const token_type_t PRECEDENCE_3[NB_P3] = {PIPE};

static const token_type_t PRECEDENCE_4[NB_P4] = {
	REDIR_RIGHT, REDIR_LEFT, REDIR_LEFT_DOUBLE, REDIR_RIGHT_DOUBLE
};

typedef struct binary_tree_s
{
	char **content;
	token_type_t type;
	struct binary_tree_s *parent;
	struct binary_tree_s *left;
	struct binary_tree_s *right;
} binary_tree_t;

/*
 * ##########################################################
 * #                         FONCTION USED FOR LEXER        #
 * ##########################################################
 */

int add_token(token_t **list, char *content);
void free_list(token_t *list);
int init_token_value(token_t *tokens);
void display_without_token_type(token_t *list);
void display_with_token_type(token_t *list);
int tokenize(char *cmd, token_t **tokens);
int handle_quotes(char *content, int *iter, char **cmd);
void exit_tokenize(token_t *tokens);
int lexer(char *cmd, token_t **tokens);
int is_redir(token_type_t type);
int is_pipe_or(token_type_t type);
int verify_grammar(token_t *tokens);
int check_and(token_t *tokens);
int check_redir(token_t *tokens);
int pre_parsing(token_t **tokens);
int is_post_arg_and_not_null(token_t **tokens);
void free_token(token_t **tokens);
int check_ambiguous_redir(token_t *tokens);

/*
 * ##########################################################
 * #              BINARY_TREE FOCNTION AND PARSING          #
 * ##########################################################
 */

int pre_parsing(token_t **tokens);
binary_tree_t *create_bintree_node(char **content, token_type_t type);
void add_node_left(binary_tree_t **bintree, char **content, token_type_t type);
void add_node_right(binary_tree_t **bintree, char **content, token_type_t type);
void add_node_parent(binary_tree_t **bintree,
			char **content, token_type_t type);
void goto_root(binary_tree_t **bintree);
binary_tree_t *get_root(binary_tree_t *bintree);
void destroy_tree(binary_tree_t *binary_tree);
int get_precedence(token_type_t type);
binary_tree_t *create_bintree_node(char **content, token_type_t type);
void move_content(token_t **tokens);
void goto_precedence_n(binary_tree_t **bintree, int n);
binary_tree_t *create_tree(token_t *tokens);
void move_content(token_t **tokens);
void display_binary_tree(binary_tree_t *bintree);

#endif
