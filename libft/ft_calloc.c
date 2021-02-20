/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara <snara@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 00:25:53 by snara             #+#    #+#             */
/*   Updated: 2020/11/19 15:03:30 by snara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*p;
	size_t	i;

	i = (count && size && size == count * size / count) ? count * size : 1;
	if ((p = (char*)malloc(i)) == NULL)
		return (NULL);
	while (0 < i--)
		p[i] = '\0';
	return ((void *)p);
}

/*
**#include <stdio.h>int main(){char*s1=ft_calloc(0,0),*s2=calloc(0,0);
**printf("%d%p\n%d%p", s1[0],s1,s2[0],s2);free(s1);free(s2);return 0;}
*/
