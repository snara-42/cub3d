/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara <snara@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 18:49:19 by snara             #+#    #+#             */
/*   Updated: 2020/11/11 09:00:09 by snara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s = (const unsigned char *)src;

	d = (unsigned char *)dst;
	while (0 < n--)
	{
		*d++ = *s;
		if (*s++ == (unsigned char)c)
			return ((void *)d);
	}
	return (NULL);
}

/*
**#include <stdio.h>
**int main(){char s[9]="fortytwo",d[9];
**printf("%s",ft_memccpy(d,s,'y',9));return 0;}
*/
