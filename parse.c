/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 09:04:01 by subaru            #+#    #+#             */
/*   Updated: 2023/09/25 03:20:18 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

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

void	print_ctx(const t_ctx *ctx)
{
	const t_player	p = ctx->player;
	const t_img		*img;
	size_t			i;

	i = -1;
	while (++i < 4)
	{
		img = &ctx->mlx.texture[i];
		printf("texture [%p](%u*%u)\n", img->addr, img->size.x, img->size.y);
	}
	printf("C=%#06x F=%#06x\n", ctx->color[0], ctx->color[1]);
	printf("player = (%f,%f),(%f,%f)\n", p.pos.x, p.pos.y, p.dir.x, p.dir.y);
	i = -1;
	while (++i < MAP_H)
		printf("%s%s", ctx->map[i], &"\n"[!ctx->map[i][0]]);
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
