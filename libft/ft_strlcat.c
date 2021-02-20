/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara <snara@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:10:27 by snara             #+#    #+#             */
/*   Updated: 2020/11/05 19:08:13 by snara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < size && dst[i])
		i++;
	while (i + j < size)
	{
		dst[i + j] = src[j];
		if (src[j] == '\0' || i + j + 1 == size)
		{
			dst[i + j] = '\0';
			break ;
		}
		j++;
	}
	while (src[j])
		j++;
	return (size_t)(i + j);
}
