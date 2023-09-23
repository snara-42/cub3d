/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:32:40 by subaru            #+#    #+#             */
/*   Updated: 2023/09/23 22:32:41 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "vec.h"
#include <stdio.h>

int	map_at_i(const t_map map, t_ivec pos)
{
	if (ivec_in(pos, ivec(MAP_W, MAP_H)))
		return (map[pos.y][pos.x]);
	return (-1);
}

int	map_at(const t_map map, t_vec pos)
{
	return (map_at_i(map, ivec(pos.x, pos.y)));
}

t_vec	try_move(const t_map map, t_vec pos, t_vec dir)
{
	if (map_at(map, vec_add(pos, vec(dir.x, 0))) == MAP_EMPTY)
		pos = vec_add(pos, vec(dir.x, 0));
	if (map_at(map, vec_add(pos, vec(0, dir.y))) == MAP_EMPTY)
		pos = vec_add(pos, vec(0, dir.y));
	return (pos);
}
