# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leina <leina@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/08 23:39:27 by massavie          #+#    #+#              #
#    Updated: 2023/02/22 22:06:53 by leina            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = lbft -lreadline

CC = gcc -g3 -Wall -Wextra -Werror

HEADER = minishell.h

OBJ_DIR = obj

OBJ_BUILTIN_IN = builtins/builtin_cd	\
				builtins/builtin_echo	\
				builtins/builtin_env	\
				builtins/builtin_exit	\
				builtins/builtin_export	\
				builtins/builtin_unset	\

OBJ_FILES = command	\
				multiexec	\
				redirection	\
				syntax	\
				varenv	\
				quotes	\
				signal	\
				builtins	\
				useful	\
				execution	\

OBJ_DIR_FILES = $(addprefix $(OBJ_DIR)/,$(OBJ_FILES))
OBJ_BUILTIN_FILES = $(addprefix $(OBJ_DIR)/,$(OBJ_BUILTIN_IN))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

SRC = 	builtins/builtin_cd/builtin_cd.c	\
	builtins/builtin_cd/builtin_cd1.c	\
	builtins/builtin_cd/cd_case.c	\
	builtins/builtin_cd/get_pwd.c	\
	builtins/builtin_echo/builtin_echo.c	\
	builtins/builtin_env/builtin_env.c	\
	builtins/builtin_env/diff_env.c	\
	builtins/builtin_env/get_env.c	\
	builtins/builtin_env/liste.c	\
	builtins/builtin_exit/builtin_exit.c \
	builtins/builtin_exit/atoi_exit.c \
	builtins/builtin_exit/qte_exit.c \
	builtins/builtin_exit/diff_exit.c \
	builtins/builtin_pwd.c	\
	builtins/check_builtins.c	\
	builtins/builtin_export/diff_export.c	\
	builtins/builtin_export/add_export.c	\
	builtins/builtin_export/suppr_export.c	\
	builtins/builtin_export/findocc.c	\
	builtins/builtin_export/builtin_export.c	\
	builtins/builtin_export/car_export.c	\
	builtins/builtin_unset/builtin_unset.c	\
	builtins/builtin_unset/suppocc.c	\
	builtins/builtin_unset/suppoccexp.c	\
	command/command.c	\
	command/def_buf_arg.c	\
	command/useful_cmd.c	\
	command/args.c	\
	command/special_cmd.c	\
	useful/count.c 	\
	useful/cut.c 	\
	useful/equal.c 	\
	useful/error.c 	\
	useful/free.c 	\
	useful/string.c 	\
	execution/execution.c \
	execution/useful_exec.c \
	execution/path.c \
	main.c			\
	multiexec/mainpi.c	\
	multiexec/muexec.c	\
	multiexec/mu_exec_last.c	\
	multiexec/mu_mi_exec.c	\
	redirection/content_heredoc.c \
	redirection/heredoc.c \
	redirection/init_redir.c \
	redirection/redirection.c \
	redirection/useful_redir.c \
	syntax/syntax.c \
	syntax/utils_syntax.c \
	syntax/token.c \
	varenv/varenv.c \
	varenv/car_var.c \
	varenv/useful_var.c \
	varenv/which_doll.c \
	varenv/space_var.c \
	quotes/quotes.c \
	quotes/quote_valid.c \
	quotes/useful_quotes.c \
	quotes/var_and_quotes.c \
	signal/signal.c \
	init.c


$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@printf "\033[0;33mGenerating Minishell objects... %-10.10s\r" $@
	${CC} -c $< -o $@

$(NAME) : $(OBJ_DIR) $(OBJ)
	@make -C $(LIBFT)
	$(CC) -o $(NAME) $(OBJ) -L$(LIBFT) -lft

$(OBJ_DIR):		;
	@printf "creating obj dir"
	@mkdir -p $@
	@mkdir -p $(OBJ_DIR_FILES)
	@mkdir -p $(OBJ_BUILTIN_FILES)

all: $(NAME)

clean:
	@echo "\033[0;31m\nMinishell objects..."
	@rm -f $(OBJ)
	@rm -rvf $(OBJ_DIR)
	@make -C $(LIBFT) clean
	@echo "\033[0m"

fclean:
	@echo "\033[0;31m\nDeleting objects..."
	@rm -f $(OBJ)
	@rm -rvf $(OBJ_DIR)
	@echo "\nDeleting executable..."
	@rm -f $(NAME)
	@make -C $(LIBFT) fclean
	@echo "\033[0m"

re: fclean all

.PHONY: clean fclean re
