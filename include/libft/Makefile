CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = libft.a
SRC = \
	ft_atoi.c\
	ft_bzero.c\
	ft_calloc.c\
	ft_isalnum.c\
	ft_isalpha.c\
	ft_isascii.c\
	ft_isdigit.c\
	ft_isprint.c\
	ft_itoa.c\
	ft_memchr.c\
	ft_memcmp.c\
	ft_memcpy.c\
	ft_memmove.c\
	ft_memset.c\
	ft_putchar_fd.c\
	ft_putendl_fd.c\
	ft_putnbr_fd.c\
	ft_putstr_fd.c\
	ft_split.c\
	ft_strchr.c\
	ft_strdup.c\
	ft_striteri.c\
	ft_strjoin.c\
	ft_strlcat.c\
	ft_strlcpy.c\
	ft_strlen.c\
	ft_strmapi.c\
	ft_strncmp.c\
	ft_strnstr.c\
	ft_strrchr.c\
	ft_strtrim.c\
	ft_substr.c\
	ft_tolower.c\
	ft_toupper.c\
	ft_atof.c\
	ft_isalldigit.c\
	ft_printf.c\
	putchar.c\
	puthex.c\
	putint.c\
	putptr.c\
	putstr.c\
	putunsigned.c\
	ft_atol.c\
	ft_isspace.c\
	ft_strcmp.c\
	quote.c\
	ft_ismetachar.c\
	ft_strjoin_char.c\
	
BONUS_SRC = \
	ft_lstnew_bonus.c\
	ft_lstadd_front_bonus.c\
	ft_lstsize_bonus.c\
	ft_lstlast_bonus.c\
	ft_lstadd_back_bonus.c\
	ft_lstdelone_bonus.c\
	ft_lstclear_bonus.c\
	ft_lstiter_bonus.c\

OBJ_DIR = objs
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))
BONUS_OBJ = $(addprefix $(OBJ_DIR)/, $(BONUS_SRC:%.c=%.o))

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	@ar rc $(NAME) $^

bonus: $(OBJ_DIR) $(BONUS_OBJ)
	@ar rc $(NAME) $(BONUS_OBJ)

$(OBJ_DIR)/%.o: %.c libft.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)
	@echo "\033[32m[✓] \031\033[1mLIBFT removed\033[1m\033[0m"

re: fclean all

.PHONY: all clean fclean re bonus
