/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara <snara@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 18:19:40 by snara             #+#    #+#             */
/*   Updated: 2020/11/18 17:10:29 by snara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (0 < n--)
		p[n] = '\0';
}

/*
**#include <stdio.h>
**int main(){char s[15]=" -2147483648";ft_bzero(s);
**while(*s<15)printf("%d",s[s[0]++]);return 0;}
*/
