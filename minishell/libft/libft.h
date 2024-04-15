/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 12:49:00 by fhassoun          #+#    #+#             */
/*   Updated: 2023/08/02 09:35:50 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdarg.h>
# include <stddef.h>
# include <limits.h>
// # include "ft_gnl.h"
// # include "ft_printf.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
size_t		ft_strlen(const char *str);
size_t		ft_strlcpy(char *dest, char *src, size_t n);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
void		*ft_memset(void *s, int c, size_t n);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_substr(char const *s, unsigned int start, size_t len);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(int nb, int fd);
void		ft_putendl_fd(char *s, int fd);
long int	ft_atoi(const char *str);
char		*ft_itoa(int n);
void		ft_bzero(void *s, size_t n);
char		**ft_split(const char *str, char c);
char		*ft_strdup(const char *src);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isprint(int c);
int			ft_isascii(int c);
int			ft_tolower(int c);
int			ft_toupper(int c);
void		*ft_calloc(size_t nmemb, size_t size);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t n);
void		*ft_memchr(const void *str, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
char		*ft_strtrim(char const *s1, char const *set);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **head, t_list *newnode);
int			ft_lstsize(t_list *node);
t_list		*ft_lstlast(t_list *node);
void		ft_lstadd_back(t_list **head, t_list *newnode);
void		ft_lstdelone(t_list *node, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *node, void (*f)(void *));
t_list		*ft_lstmap(t_list *node, void *(*f)(void *), void (*del)(void *));
int			ft_isspace(int c);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strisspace(char *str);
//ft_printf 
int			ft_printf(const char *str, ...);
int			var_find(const char var, va_list lst);
int			print_char(char c);
int			print_str(char *str);
int			print_perc(char c);
int			print_nbr(int n);
int			print_hex(unsigned int value, char var);
int			print_ptr(unsigned long long value, char var);
int			print_ull(unsigned int value, char var);
char		*ft_swap(char *buf, int i, char var);
//ft_gnl
char		*get_next_line(int fd);
char		*ft_gnl_strdup(char *src);
char		*ft_gnl_strjoin(char *s1, char *s2);
#endif
