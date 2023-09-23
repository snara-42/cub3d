/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 09:06:10 by subaru            #+#    #+#             */
/*   Updated: 2023/09/23 09:06:11 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"
#include <math.h>

t_vec	vec(double x, double y);

t_vec	vec_sub(t_vec a, t_vec b)
{
	return (vec(a.x - b.x, a.y - b.y));
}

t_vec	vec_mul(t_vec a, t_vec b)
{
	return (vec(a.x * b.x, a.y * b.y));
}

t_vec	vec_sca(t_vec a, double n)
{
	return (vec(a.x * n, a.y * n));
}

t_vec	vec_div(t_vec a, t_vec b)
{
	return (vec(a.x / b.x, a.y / b.y));
}

t_vec	vec_rot(t_vec v, double angle)
{
	return (vec(v.x * cos(angle) - v.y * sin(angle),
			v.x * sin(angle) + v.y * cos(angle)));
}
