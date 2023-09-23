/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sscanf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 01:42:29 by subaru            #+#    #+#             */
/*   Updated: 2023/09/23 09:05:28 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>

#include <stdio.h>

typedef unsigned int	t_uint;

int	ft_vsscanf(const char *s, const char *f, va_list ap)
{
	int		rv;
	char	*rs;

	rv = 0;
	while (*f && *s)
	{
		if (*f == '%')
		{
			if (*++f == '%' && *f != *s)
				break ;
			else if (*f == 'u')
			{
				rs = ft_strtou_base(s, va_arg(ap, t_uint *), "0123456789");
				rv += (rs != s);
				s = rs;
			}
			f++;
		}
		else if (*f++ != *s++)
			return (rv);
	}
	return (rv);
}

int	ft_sscanf(const char *s, const char *fmt, ...)
{
	va_list	ap;
	int		rv;

	va_start(ap, fmt);
	rv = ft_vsscanf(s, fmt, ap);
	va_end(ap);
	return (rv);
}
