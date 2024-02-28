# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/02 14:02:28 by jaqribei          #+#    #+#              #
#    Updated: 2024/02/28 15:46:56 by jaqribei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#******************************************************************************#
#								COMPILATION									   #
#******************************************************************************#

CC			= cc
FLAGS		= -g3

#******************************************************************************#
#									PATH									   #
#******************************************************************************#

INCLUDES 		:= -I ./include/
OBJ_DIR			:= obj/
SRC_DIR			:= src/

#******************************************************************************#
#									FILES									   #
#******************************************************************************#

NAME = minishell

src += main.c utils.c cmd.c errors.c test_built.c

src += $(addprefix tokenizer/, token_identifiers.c \
								token_identifiers_utils.c \
								tokenizer_utils.c \
								tokenizer.c)

 src += $(addprefix builtins/, cd.c \
								echo.c \
								env.c \
								exit.c \
								export.c \
								pwd.c \
								unset.c)

 src += $(addprefix redirects/, heredoc.c)
 								# redirect_hand_files.c \
 								# redirect_in.c \
 								# redirect_out.c \
								# redirect.c)
								

SRC_OBJ = $(addprefix $(OBJ_DIR)/, $(src:%.c=%.o))

MINISHELL_SRC = main.c utils.c errors.c cmd.c redirections/heredoc.c builtins/echo.c

all: libft $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(MINI_OBJ)
	@$(CC) $(FLAGS) $(MINI_OBJ) ./include/libft/libft.a -lreadline -o $(NAME)

#******************************************************************************#
#									TARGETS									   #
#******************************************************************************#

libft:
	@make -C ./include/libft

valgrind: all
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=supression.sup ./$(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C ./include/libft

fclean: clean
	@rm -f $(NAME)
	@make fclean -C ./include/libft
	@echo "\033[36m[✓] \033[1m\033[1m$(NAME) removed\033[0m"

re: fclean all

.PHONY: all clean fclean re libft