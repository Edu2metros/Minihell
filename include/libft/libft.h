/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:09:27 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/19 20:47:57 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void				ft_bzero(void *s, size_t n);
void				ft_putnbr_fd(int n, int fd);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				*ft_calloc(size_t nitems, size_t size);
void				*ft_memset(void *s, int bytes, size_t memory);
void				*ft_memchr(const void *ptr, int value, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));

char				*ft_itoa(int n);
char				*ft_strdup(const char *str);
char				*ft_strchr(const char *s, int c);
char				**ft_split(char const *s, char c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_isalpha(int letter);
int					ft_isdigit(int number);
int					ft_isalnum(int digit);
int					ft_isascii(int ascii);
int					ft_isprint(int print);
int					ft_atoi(const char *str);
int					ft_memcmp(const void *ptr1, const void *ptr2, size_t n);
int					ft_strncmp(const char *str1, const char *str2, size_t n);

size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *s);
size_t				ft_strlcpy(char *dst, const char *src, size_t n);

void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
int					ft_lstsize(t_list *lst);

// ADICIONAL FUNCTIONS (made by me)

char				*ft_strjoin_char(char *s, char c);
int					meta_char(char c);
int					my_isspace(char c);
int					check_quote(char *input);
int					ft_strcmp(char *s1, char *s2);
int					ft_isalldigit(const char *str);
long int			ft_atol(const char *str);
long double			ft_atof(char *str);
int					is_excession(char c);
void				close_fd(void);
int					file_exist(char *file_name);
int					file_is_readable(char *file_name);
int					file_is_writable(char *file_name);
int					file_is_executable(char *file_name);

// PRINTF FUNCTIONS

int					ft_putnbr(int nbr);
int					ft_putptr(void *ptr);
int					ft_unsint(unsigned int nbr);
int					ft_printf(const char *str, ...);
int					format(const char *str, va_list ap);
int					ft_puthex(unsigned int nbr, char x);
size_t				ft_putchar(char c);
size_t				ft_putstr(char *str);

int					ft_printf_fd(int fd, const char *str, ...);
int					format_fd(const char *str, va_list ap, int fd);
size_t				putchar_fd(char c, int fd);
size_t				putstr_fd(char *str, int fd);
size_t				putnbr_fd(int nbr, int fd);
size_t				ft_putptr_fd(void *ptr, int fd);
int					ft_puthex_fd(unsigned int nbr, char x, int fd);
size_t				ft_unsint_fd(unsigned int nbr, int fd);

#endif