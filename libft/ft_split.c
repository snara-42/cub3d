/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara <snara@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 21:45:56 by snara             #+#    #+#             */
/*   Updated: 2020/11/19 13:28:01 by snara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*wdup(char const *s, const char c)
{
	char	*d;
	int		i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	if (i == 0 || (d = (char *)malloc(sizeof(char) * (i + 1))) == NULL)
		return (NULL);
	i = 0;
	while (s[i] != c && s[i])
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}

static int	wc(char const *s, const char c)
{
	int	i;
	int	w;

	i = 0;
	w = 0;
	while (s[i++])
		if ((s[i - 1] != c) && (s[i] == '\0' || s[i] == c))
			w++;
	return (w);
}

char		**ft_split(char const *s, char c)
{
	char	**d;
	int		w;

	if (!s || !(d = (char **)malloc(sizeof(char*) * (wc(s, c) + 1))))
		return (NULL);
	w = 0;
	while (*s)
	{
		if ((w == 0 || s[-1] == c) && *s != c)
		{
			if (!(d[w++] = wdup(s, c)))
			{
				while (0 < w--)
				{
					free(d[w]);
					d[w] = NULL;
				}
				free(d);
				return (d = NULL);
			}
		}
		s++;
	}
	d[w] = NULL;
	return (d);
}

/*
**#include <stdio.h>
**int main(){char**d=ft_split("",0);for(;;){printf("%s",*d);if(!*d++)return 0;}}
*/
