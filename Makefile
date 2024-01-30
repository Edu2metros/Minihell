MINISHELL_NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror -g3
INCLUDES = -I ./include/

OBJ_DIR = objs
TOKEN_DIR = tokenizer

SRC_DIR = src
TOKEN_SRC = token_identifiers.c token_identifiers_utils.c tokenizer.c tokenizer_utils2.c

MINISHELL_SRC = main.c utils.c
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

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C ./include/libft

fclean: clean
	@rm -f $(MINISHELL_NAME)
	@make fclean -C ./include/libft
	@echo "\033[32m[✓] \033[1m\033[1m$(MINISHELL_NAME) removed\033[0m"

re: fclean all

.PHONY: all clean fclean re libft
