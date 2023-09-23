/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara <snara@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:27:13 by snara             #+#    #+#             */
/*   Updated: 2023/09/23 09:03:55 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <errno.h>

#ifndef FD_SIZE
# define FD_SIZE	256
#endif // FD_SIZE
#ifndef BUFFER_SIZE
# define BUFFER_SIZE	1024
#endif // BUFFER_SIZE

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (i + 1 < dstsize && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize != 0)
		dst[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}

static char	*ft_strj(char *s1, char const *s2, char c)
{
	char	*d;
	size_t	i;
	size_t	j;

	i = 0;
	while (s1 && s1[i])
		i++;
	j = 0;
	while (s2 && s2[j] && s2[j] != c)
		j++;
	d = (char *)malloc(sizeof(char) * (i + j + 2));
	if (d)
	{
		s1 && ft_strlcpy(d, s1, i + 1);
		ft_strlcpy(&d[i], s2, j + 1);
	}
	free(s1);
	return (d);
}

static char	*ft_strcmove(char *s, const char c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s[i] && s[i] != c)
		i++;
	if (i >= n || !s[i] || s[i] != c)
	{
		s[0] = '\0';
		return (NULL);
	}
	i += 1;
	ft_strlcpy(s, &s[i], n);
	return (s);
}

char	*get_next_line(int fd)
{
	ssize_t		r;
	char		*line;
	static char	buf[BUFFER_SIZE + 1u] = {};

	r = 1;
	line = NULL;
	if (read(fd, buf, 0) < 0)
		return (NULL);
	while (1)
	{
		line = ft_strj(line, buf, '\n');
		if (!line || r == 0 || ft_strcmove(buf, '\n', BUFFER_SIZE + 1))
			return (line);
		r = read(fd, buf, BUFFER_SIZE);
		if (r < 0 || (r == 0 && !line[0]))
			break ;
		buf[r] = '\0';
	}
	free(line);
	return (NULL);
}
