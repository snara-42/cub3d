#include <stddef.h>

char	*str_skip(const char *s, char c);
char	*ft_strchr(const char *s, char c);
int		ft_strncmp(const char *s, const char *t, size_t n);
int		ft_strrcmp(const char *s, const char *t, size_t n);

char	*str_skip(const char *s, char c)
{
	while (*s == c)
		s++;
	return ((char *)s);
}

char	*ft_strchr(const char *s, char c)
{
	while (*s && *s != c)
		s++;
	if (*s == c)
		return ((char *)s);
	return (NULL);
}

int		ft_strncmp(const char *s, const char *t, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s[i] && t[i] && s[i] == t[i])
		i++;
	if (i >= n)
		return (0);
	return (t[i] - s[i]);
}

int		ft_strrcmp(const char *s, const char *t, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	m;

	i = 0;
	while (s[i])
		i++;
	j = 0;
	while (t[j])
		j++;
	m = 0;
	while (m < n && m < i && m < j && s[i - m] == t[j - m])
		m++;
	if (m >= n)
		return (0);
	return (t[j - m] - s[i - m]);
}

