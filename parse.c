/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 09:04:01 by subaru            #+#    #+#             */
/*   Updated: 2023/09/28 20:46:51 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

#include <math.h>
#include <mlx.h>

#include <stdint.h>
#include <stddef.h>
#include <limits.h>
#include <stdbool.h>

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define C_CLR "\x1b[0m"
#define C_FC "\x1b[36m"

void	print_map(const t_ctx *ctx)
{
	const t_player	p = ctx->player;
	size_t			x;
	size_t			y;

	printf("p=pos(%f,%f),dir(%f,%f)\n", p.pos.x, p.pos.y, p.dir.x, p.dir.y);
	y = 0;
	while (y < MAP_H)
	{
		x = 0;
		while (x < MAP_W && ctx->map[y][x])
		{
			if (x == (size_t)p.pos.x && y == (size_t)p.pos.y)
				printf(C_FC"%c"C_CLR, "<^>v<^>"
				[lround((atan2(p.dir.y, p.dir.x) + M_PI) / M_PI_2)]);
			else
				printf("%c", ctx->map[y][x]);
			x++;
		}
		printf("%.*s", (x > 0), "\n");
		y++;
	}
}

void	print_ctx(const t_ctx *ctx)
{
	const t_img		*img;
	size_t			i;

	i = -1;
	while (++i < 4)
	{
		img = &ctx->mlx.texture[i];
		printf("texture [%p](%u*%u)\n", img->addr, img->size.x, img->size.y);
	}
	printf("C=%#06x F=%#06x\n", ctx->color[0], ctx->color[1]);
	print_map(ctx);
}

int	parse_file(t_ctx *ctx, const char *path)
{
	int	fd;

	if (!!ft_strrcmp(path, ".cub", 4))
		or_exit(NULL, "file extension must be '.cub'");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		or_exit(NULL, "could not open file");
	*ctx = (t_ctx){.mlx = ctx->mlx, .color = {COLOR_DFL, COLOR_DFL}};
	parse_config(ctx, fd);
	parse_map(ctx, fd);
	close(fd);
	print_ctx(ctx);
	return (0);
}
