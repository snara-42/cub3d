/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 09:04:01 by subaru            #+#    #+#             */
/*   Updated: 2023/09/25 03:20:18 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

#include <X11/X.h>
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

static int	init_mlx(t_mlx *mlx)
{
	t_img *const	img = &mlx->img;

	mlx->mlx = or_exit(mlx_init(), __func__);
	mlx->win = or_exit(mlx_new_window(
				mlx->mlx, SCREEN_W, SCREEN_H, "cub3d"), __func__);
	img->size = ivec(SCREEN_W, SCREEN_H);
	img->ptr = or_exit(mlx_new_image(
				mlx->mlx, img->size.x, img->size.y), __func__);
	img->addr = mlx_get_data_addr(
			img->ptr, &img->bpp, &img->size_line, &img->endian);
	return (0);
}

static int	hook_mlx(t_ctx *ctx)
{
	const t_mlx	*mlx = &ctx->mlx;

	mlx_do_key_autorepeaton(mlx->mlx);
	mlx_hook(mlx->win, DestroyNotify, StructureNotifyMask, &f_exit, ctx);
	mlx_key_hook(mlx->win, &f_key_hook, ctx);
	mlx_loop_hook(mlx->mlx, &f_draw, ctx);
	return (0);
}

int	main(int ac, char *av[])
{
	static t_ctx	ctx = {};

	if (ac != 2)
		or_exit(NULL, "usage: ./cub3d cubfile");
	init_mlx(&ctx.mlx);
	parse_file(&ctx, av[1]);
	hook_mlx(&ctx);
	mlx_loop(ctx.mlx.mlx);
}

#if 0

__attribute__((destructor))
void	end(void)
{
	system("leaks -q a.out");
}

#endif
