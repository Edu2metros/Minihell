# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/02 14:02:28 by jaqribei          #+#    #+#              #
#    Updated: 2024/02/29 16:04:41 by eddos-sa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#******************************************************************************#
#								COMPILATION									   #
#******************************************************************************#

CC			= cc
FLAGS		= -Wall -Wextra -Werror -g3

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

src += main.c utils.c errors.c free.c

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
								unset.c \
								builtin.c)

src += $(addprefix redirects/, heredoc.c)
 								# redirect_hand_files.c \
 								# redirect_in.c \
 								# redirect_out.c \
								# redirect.c)
								
src += $(addprefix cmd/, cmd.c \
						 cmd2.c)

src += $(addprefix print/, print.c)

SRC_OBJ = $(addprefix $(OBJ_DIR)/, $(src:%.c=%.o))

all: libft $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(SRC_OBJ)
	@$(CC) $(FLAGS) $(SRC_OBJ) ./include/libft/libft.a -lreadline -o $(NAME)

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