/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara <snara@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 21:48:48 by snara             #+#    #+#             */
/*   Updated: 2020/12/23 16:45:39 by snara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_fd(char c, int fd)
{
	unsigned char	u[3];
	int				r;

	if ((unsigned char)c <= 0x7f)
	{
		u[0] = c;
		r = write(fd, u, 1);
	}
	else
	{
		u[0] = 0xc0 | (((unsigned char)c >> 6) & 0x1f);
		u[1] = 0x80 | ((unsigned char)c & 0x3f);
		r = write(fd, u, 2);
	}
	return (r);
}

int	ft_putchar_n(char c, int n, int fd)
{
	int	r;

	r = 0;
	while (0 < n--)
		r += write(fd, &c, 1);
	return (r);
}

/*
**int main(){ft_putchar_fd('\t',1);return(0);}
*/
