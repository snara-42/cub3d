/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara <snara@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 21:46:28 by snara             #+#    #+#             */
/*   Updated: 2021/01/09 19:37:59 by snara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_unlen(unsigned int n, unsigned int b, unsigned int *e)
{
	int	i;

	if (b < 2)
		return (0);
	i = 1;
	while (e[0] <= (n / b))
	{
		e[0] *= b;
		i++;
	}
	return (i);
}

int		ft_nlen(int n, int b, int *e)
{
	int	i;

	if (b < 2)
		return (0);
	i = 1;
	while (n / b > 0)
	{
		n /= b;
		e[0] *= b;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	const int	b = 10;
	const char	digit[b] = "0123456789";
	char		*d;
	int			i;
	int			e;

	e = 1;
	if ((d = (char *)malloc(sizeof(char) * (ft_nlen(n, b, &e) + 1))) == NULL)
		return (NULL);
	if (n < (i = 0))
		d[i++] = '-';
	while (0 < e)
	{
		d[i++] = digit[(n < 0) ? -(n / e % b) : (n / e % b)];
		e /= b;
	}
	d[i] = '\0';
	return (d);
}

/*
**#include <stdio.h>
**int main(){int n=-2147483648;printf("%s",ft_itoa(n));return 0;}
*/
