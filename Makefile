# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/02 14:02:28 by jaqribei          #+#    #+#              #
#    Updated: 2024/02/21 22:40:55 by jaqribei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#******************************************************************************#
#								COMPILATION									   #
#******************************************************************************#

CC			= cc
FLAGS		= -g3

#******************************************************************************#
#									FILES									   #
#******************************************************************************#

# src = main.c utils.c heredoc.c

# src += $(addprefix tokenizer/, token_identifiers.c \
								token_identifiers_utils.c \
								tokenizer_utils.c \
								tokenizer.c)

# src += $(addprefix bultins/, cd.c \
								echo.c \
								env.c \
								exit.c \
								export.c \
								pwd.c \
								unset)

MINISHELL_NAME = minishell
INCLUDES = -I ./include/

OBJ_DIR = objs
TOKEN_DIR = tokenizer

SRC_DIR = src
TOKEN_SRC = token_identifiers.c token_identifiers_utils.c tokenizer.c tokenizer_utils.c

MINISHELL_SRC = main.c utils.c errors.c test_built.c cmd.c redirections/heredoc.c redirections/redirect.c

SRC_OBJ = $(addprefix $(OBJ_DIR)/, $(MINISHELL_SRC:%.c=%.o))
TOKEN_OBJ = $(addprefix $(OBJ_DIR)/$(TOKEN_DIR)/, $(TOKEN_SRC:%.c=%.o))

MINISHELL_OBJ = $(SRC_OBJ) $(TOKEN_OBJ)

all: libft $(MINISHELL_NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/$(TOKEN_DIR)/%.o: $(SRC_DIR)/$(TOKEN_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(MINISHELL_NAME): $(MINISHELL_OBJ)
	@$(CC) $(FLAGS) $(MINISHELL_OBJ) ./include/libft/libft.a -lreadline -o $(MINISHELL_NAME)

libft:
	@make -C ./include/libft

valgrind: all
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=supression.sup ./$(MINISHELL_NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C ./include/libft

fclean: clean
	@rm -f $(MINISHELL_NAME)
	@make fclean -C ./include/libft
	@echo "\033[36m[✓] \033[1m\033[1m$(MINISHELL_NAME) removed\033[0m"

re: fclean all

.PHONY: all clean fclean re libft