/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara <snara@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:32:07 by snara             #+#    #+#             */
/*   Updated: 2020/12/28 14:43:00 by snara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# define ABS(x) (((x) < 0) ? (-(x)) : (x))

typedef unsigned long long	t_ull;
typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void				ft_pswap(char **a, char **b);
void				ft_nswap(void *a, void *b);
void				ft_bzero(void *s, size_t n);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_atoi(const char *str);
char				*ft_itoa(int n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(const char *s);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *s);
size_t				ft_strplen(const char *s);
size_t				ft_strnlen(const char *s, ssize_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *str, const char *find, size_t n);
char				*ft_strrchr(const char *s, int c);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
int					ft_nlen(int n, int b, int *e);
int					ft_unlen(unsigned int n, unsigned int b, unsigned int *e);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_putchar_fd(char c, int fd);
int					ft_putchar_n(char c, int n, int fd);
int					ft_putstr_fd(char *s, int fd);
int					ft_putstrcat_fd(char *s1, char *s2, int fd);
int					ft_putstr_n(char *s, int n, int fd);
int					ft_putendl_fd(char *s, int fd);
int					ft_putnbr_fd(long long n, int fd);
int					ft_putnbr_base(long long n, char *base, int fd);
int					ft_putnbr_baseu(t_ull n, char *base, int fd);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void*),
						void (*del)(void*));

#endif
