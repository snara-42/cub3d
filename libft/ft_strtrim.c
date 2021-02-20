/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara <snara@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 21:45:14 by snara             #+#    #+#             */
/*   Updated: 2020/11/19 15:15:45 by snara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isset(char c, char const *set)
{
	while (*set)
	{
		if (c == *set++ || c == '\0')
			return (1);
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*d;
	size_t	i;

	if (s1 == NULL)
		return (NULL);
	i = 0;
	while (*s1 && isset(*s1, set))
		s1++;
	while (s1[i])
		i++;
	while (0 < i && isset(s1[i - 1], set))
		i--;
	if ((d = (char *)malloc(sizeof(char) * (i + 1))) == NULL)
		return (NULL);
	d[i] = '\0';
	while (0 < i--)
		d[i] = s1[i];
	return (d);
}
