/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 09:05:55 by subaru            #+#    #+#             */
/*   Updated: 2023/09/23 21:56:43 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

#include <stdlib.h>

static t_player	get_start_pos(const t_map map)
{
	size_t	x;
	size_t	y;
	char	c;

	y = 0;
	while (y < MAP_H)
	{
		x = 0;
		while (x < MAP_W && map[y][x])
		{
			c = map[y][x];
			if (c == 'W')
				return ((t_player){vec(x + .5, y + .5), vec(-1, 0)});
			else if (c == 'N')
				return ((t_player){vec(x + .5, y + .5), vec(0, -1)});
			else if (c == 'E')
				return ((t_player){vec(x + .5, y + .5), vec(+1, 0)});
			else if (c == 'S')
				return ((t_player){vec(x + .5, y + .5), vec(0, +1)});
			x++;
		}
		y++;
	}
	or_exit(NULL, "missing start position");
	return ((t_player){});
}

static bool	floodfill(const t_map map, t_map filled, int x, int y)
{
	bool	is_surrounded;

	if (!(0 <= x && x < MAP_W && 0 <= y && y < MAP_H))
		return (false);
	if (filled[y][x] || map[y][x] == MAP_WALL)
		return (true);
	filled[y][x] = true;
	is_surrounded = (floodfill(map, filled, x - 1, y)
			&& floodfill(map, filled, x + 1, y)
			&& floodfill(map, filled, x, y - 1)
			&& floodfill(map, filled, x, y + 1));
	return (is_surrounded);
}

bool	is_map_surrounded(const t_map map)
{
	const t_player	start = get_start_pos(map);
	bool			is_surrounded;

	is_surrounded = floodfill(map, (t_map){}, start.pos.x, start.pos.y);
	return (is_surrounded);
}

bool	is_valid_map(const t_map map)
{
	size_t	x;
	size_t	y;
	size_t	configured;

	configured = 0;
	y = 0;
	while (y < MAP_H)
	{
		x = 0;
		while (x < MAP_W && map[y][x])
		{
			if (!ft_strchr("01 NSEW", map[y][x]))
				or_exit(NULL, "invalid character in map");
			if (ft_strchr("NSEW", map[y][x]) && configured++)
				or_exit(NULL, "duplicate start pos");
			x++;
		}
		y++;
	}
	if (!configured)
		or_exit(NULL, "missing start pos");
	if (!is_map_surrounded(map))
		or_exit(NULL, "map not surrounded by wall");
	return (true);
}

bool	parse_map(t_ctx *ctx, int fd)
{
	size_t	y;
	char	*s;

	y = 0;
	while (1)
	{
		s = get_next_line(fd);
		if (!s)
			break ;
		if (ft_strlcpy(ctx->map[y], s, MAP_W) >= MAP_W)
			or_exit(NULL, "map too wide");
		if (++y >= MAP_H)
			or_exit(NULL, "map too long");
		free(s);
	}
	if (!is_valid_map(ctx->map))
		or_exit(NULL, "map invalid");
	ctx->player = get_start_pos(ctx->map);
	ctx->map[(int)ctx->player.pos.y][(int)ctx->player.pos.x] = MAP_EMPTY;
	return (true);
}
