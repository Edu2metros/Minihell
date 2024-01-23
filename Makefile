MINISHELL_NAME = minishell
CC = cc
FLAGS = -g3
INCLUDES = -I ./include/

SRC_DIR = src
OBJ_DIR = objs

MINISHELL_SRC = main.c utils.c tokenizer.c					
MINISHELL_OBJ = $(addprefix $(OBJ_DIR)/, $(MINISHELL_SRC:%.c=%.o))

all: libft $(MINISHELL_NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR) libft
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(MINISHELL_NAME): $(MINISHELL_OBJ)
	@$(CC) $(FLAGS) $(MINISHELL_OBJ) ./include/libft/libft.a -lreadline -o $(MINISHELL_NAME)

libft:
	@make -C ./include/libft

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C ./include/libft

fclean: clean
	@rm -f $(MINISHELL_NAME)
	@make fclean -C ./include/libft
	@echo "$(MINISHELL_NAME) removed."

re: fclean all

.PHONY: all clean fclean re libft
