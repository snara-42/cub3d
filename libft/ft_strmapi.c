/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara <snara@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 21:47:28 by snara             #+#    #+#             */
/*   Updated: 2020/11/13 12:57:41 by snara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*d;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	if ((d = (char *)malloc(sizeof(char) * (i + 1))) == NULL)
		return (NULL);
	d[i] = '\0';
	i = 0;
	while (s[i])
	{
		d[i] = f(i, s[i]);
		i++;
	}
	return (d);
}
