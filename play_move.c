/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:32:40 by subaru            #+#    #+#             */
/*   Updated: 2023/09/25 00:36:02 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "vec.h"
#include <stdio.h>

#define MRG_W 0.125
#define MRG_L 1.125

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

#if 0

t_vec	try_move(const t_map map, t_vec pos, t_vec dir)
{
	if (map_at(map, vec_add(pos, vec(dir.x, 0))) == MAP_EMPTY)
		pos = vec_add(pos, vec(dir.x, 0));
	if (map_at(map, vec_add(pos, vec(0, dir.y))) == MAP_EMPTY)
		pos = vec_add(pos, vec(0, dir.y));
	return (pos);
}

#else

t_vec	try_move(const t_map map, t_vec pos, t_vec dir)
{
	if ((map_at(map, vec_add(pos, vec(dir.x * MRG_L, MRG_W))) == MAP_EMPTY)
		&& (map_at(map, vec_add(pos, vec(dir.x * MRG_L, -MRG_W))) == MAP_EMPTY))
		pos = vec_add(pos, vec(dir.x, 0));
	if ((map_at(map, vec_add(pos, vec(MRG_W, dir.y * MRG_L))) == MAP_EMPTY)
		&& (map_at(map, vec_add(pos, vec(-MRG_W, dir.y * MRG_L))) == MAP_EMPTY))
		pos = vec_add(pos, vec(0, dir.y));
	return (pos);
}

#endif
