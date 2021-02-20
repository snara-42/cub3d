/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara <snara@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:09:54 by snara             #+#    #+#             */
/*   Updated: 2020/11/13 14:31:53 by snara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	ft_atoi(const char *str)
{
	unsigned int	n;
	int				s;

	while (*str == ' ' || ('\t' <= *str && *str <= '\r'))
		str++;
	s = (*str == '-') ? -1 : 1;
	if (*str == '-' || *str == '+')
		str++;
	n = 0;
	while ('0' <= *str && *str <= '9')
	{
		n = n * 10 + (*str++ - '0');
		if ((unsigned int)(INT_MAX + (s == 1 ? 0 : 1)) < n)
			return (s == 1 ? -1 : 0);
	}
	return ((int)(n * s));
}

/*
**#include <stdio.h>
**int main(void){char*s ="\t\n\v\f\r -9223372036854775808";
**printf("%d %d\n",atoi(s),ft_atoi(s));return(0);}
*/
