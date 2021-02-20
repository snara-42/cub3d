/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara <snara@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:35:54 by snara             #+#    #+#             */
/*   Updated: 2020/11/11 09:07:03 by snara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (0 < n--)
		*p++ = (unsigned char)c;
	return (s);
}

/*
**#include <stdio.h>
**int main(){char s[9]="fortytwo";
**printf("%s",ft_memset(s,'0',5));return 0;}
*/
