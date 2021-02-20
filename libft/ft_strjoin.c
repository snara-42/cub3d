/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara <snara@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 21:43:35 by snara             #+#    #+#             */
/*   Updated: 2020/11/18 11:24:29 by snara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*d;
	size_t	i;
	size_t	j;

	i = 0;
	while (s1 && s1[i])
		i++;
	j = 0;
	while (s2 && s2[j])
		j++;
	if ((d = (char *)malloc(sizeof(char) * (i + j + 1))) == NULL)
		return (NULL);
	d[i + j] = '\0';
	while (s2 && 0 < j--)
		d[i + j] = s2[j];
	while (s1 && 0 < i--)
		d[i] = s1[i];
	return (d);
}
