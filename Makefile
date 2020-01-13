##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile for 42sh parser
##

SRC	=	parseur_ll/display_tokenlist.c 		\
		parseur_ll/add_token.c 			\
		parseur_ll/init_token.c 		\
		parseur_ll/tokenize.c 			\
		parseur_ll/quotes_handling.c		\
		parseur_ll/exit_tokenize.c		\
		parseur_ll/identify_tokens.c		\
		parseur_ll/grammar.c			\
		parseur_ll/grammar_checks.c		\
		parseur_ll/check_ambiguous_redir.c	\
		parseur_ll/lexer.c 			\
		parseur_ll/bintree_add_node.c 		\
		parseur_ll/create_tree.c 		\
		parseur_ll/display_binary_tree.c	\
		parseur_ll/pre_parsing.c		\
		parseur_ll/free_token.c 		\
		parseur_ll/move_content_to_cmd_arg.c 	\
		parseur_ll/get_precedence.c		\
		parseur_ll/goto_precedence.c		\
		parseur_ll/binary_tree_op.c		\
		parseur_ll/parseur.c			\
		src/main.c				\
                src/built_in.c                  	\
                src/check_old_command.c         	\
                src/give_all_path.c             	\
                src/change_dir.c                	\
                src/env_manipulation.c          	\
                src/execute_function.c          	\
                src/separ_instruct.c            	\
                src/arg_until_str.c             	\
                src/execute_line.c              	\
		src/clean_non_quoted_backslash.c	\
                basic/my_str_is_alpha_num.c

OBJ	=	$(addsuffix .o, $(basename $(SRC)))

NAME	=	42sh

CC	=	gcc

CPPFLAGS	=	-Wall -Wextra -I ./include/ -g3

all:	$(NAME)

$(NAME):	$(OBJ)
		@$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) $(LDLIBS)
		@echo -e "\033[32m\n==== \033[92mCOMPLETED\033[32m ====\033[0m"

clean:
		@rm -rf $(OBJ)
		@echo -en "\033[32m[OK]\033[0m"
		@echo -e "\033[91m [CLEANING]\033[0m"

fclean:	clean
		@rm -rf $(NAME)
		@echo -en "\033[32m[OK]\033[0m"
		@echo -e "\033[91m [FCLEANING]\033[0m"

re:	fclean all

%.o:	%.c
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -c -o $@ $< && echo -e "\e[32m[OK]\033[0m\e[1m\e[32m" $< "\033[0m" || echo -e "BATARD" $<

.PHONY: all clean fclean re %.o
