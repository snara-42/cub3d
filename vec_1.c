/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 09:02:58 by subaru            #+#    #+#             */
/*   Updated: 2023/09/23 09:06:09 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"
#include <stdbool.h>

t_ivec	ivec(int x, int y)
{
	return ((t_ivec){x, y});
}

bool	in_range(int n, int min, int max)
{
	return (min <= n && n < max);
}

bool	ivec_in(t_ivec v, t_ivec size)
{
	return (0 <= v.x && v.x < size.x && 0 <= v.y && v.y < size.y);
}

t_vec	vec(double x, double y)
{
	return ((t_vec){x, y});
}

t_vec	vec_add(t_vec a, t_vec b)
{
	return (vec(a.x + b.x, a.y + b.y));
}
