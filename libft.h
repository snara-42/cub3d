#ifndef LIBFT_H
# define LIBFT_H

# include <stdint.h>
# include <stddef.h>
# include <limits.h>
# include <stdbool.h>

char	*str_skip(const char *s, char c);
char	*ft_strchr(const char *s, char c);
int		ft_strncmp(const char *s, const char *t, size_t n);
int		ft_strrcmp(const char *s, const char *t, size_t n);

char	*get_next_line(int fd);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_sscanf(const char *s, const char *fmt, ...);

void	*or_exit(void *p, const char *msg);

#endif
