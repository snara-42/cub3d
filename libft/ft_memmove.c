/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara <snara@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:30:40 by snara             #+#    #+#             */
/*   Updated: 2020/11/18 14:48:29 by snara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s = (unsigned char *)src;

	d = (unsigned char *)dst;
	if (dst < src)
	{
		i = 0;
		while (i++ < n)
			d[i - 1] = s[i - 1];
	}
	else if (src < dst)
	{
		i = n;
		while (0 < i--)
			d[i] = s[i];
	}
	return (dst);
}

/*
**#include <stdio.h>
**int main(){char s[20]="move!";printf("%s",ft_memmove(s-2,s,5));return 0;}
*/
