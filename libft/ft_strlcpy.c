/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara <snara@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 09:57:32 by snara             #+#    #+#             */
/*   Updated: 2020/11/13 12:52:53 by snara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	n;

	if (src == NULL)
		return (0);
	n = 0;
	while (0 < size && dst != NULL)
	{
		dst[n] = src[n];
		if (n + 1 == size || src[n] == '\0')
		{
			dst[n] = '\0';
			break ;
		}
		n++;
	}
	while (src[n])
		n++;
	return (n);
}
