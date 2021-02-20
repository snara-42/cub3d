/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara <snara@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 18:26:56 by snara             #+#    #+#             */
/*   Updated: 2020/11/18 23:15:23 by snara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const unsigned char	*s = (const unsigned char *)src;
	unsigned char		*d;

	d = (unsigned char *)dst;
	if (dst == src)
		return (dst);
	while (0 < n--)
		d[n] = s[n];
	return (dst);
}

/*
**#include <stdio.h>
**int main(){char *s,*d;printf("%s",ft_memcpy(d,s,9));return 0;}
*/
